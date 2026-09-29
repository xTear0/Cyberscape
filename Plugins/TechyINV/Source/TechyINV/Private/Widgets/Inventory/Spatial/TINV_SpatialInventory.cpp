// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/Spatial/TINV_SpatialInventory.h"
#include "InventoryManagement/Components/TINV_InventoryComponent.h"
#include "InventoryManagement/Utils/TINV_InventoryStatics.h"
#include "ItemData/TINV_ItemDataTable.h"
#include "Items/TINV_InventoryItem.h"
#include "Items/Components/TINV_ItemComponent.h"
#include "Widgets/Inventory/Spatial/TINV_InventoryGrid.h"
#include "Components/PanelWidget.h"
#include "InventoryManagement/Subsystems/TINV_HeldItemSubsystem.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_SpatialInventory.cpp_Functions
void UTINV_SpatialInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (UTINV_InventoryComponent* InventoryComponent = UTINV_InventoryStatics::GetInventoryComponent(GetOwningPlayer()))
	{
		InventoryComponent->OnItemAdded.AddDynamic(this, &ThisClass::OnItemAdded);
		InventoryComponent->OnStackChange.AddDynamic(this, &ThisClass::OnStackChange);
		InventoryComponent->OnHotbarSwapRequested.AddDynamic(this, &ThisClass::OnHotbarSwapRequested);
	}
}

void UTINV_SpatialInventory::NativeConstruct()
{
	Super::NativeConstruct();

	// Invisible until we've measured where "docked" is, so it never flashes in the wrong place.
	bDockOffsetReady = false;
	InventoryHotbar->SetRenderOpacity(0.f);
}

FTINV_SlotAvailabilityResult UTINV_SpatialInventory::HasRoomForItem(UTINV_ItemComponent* ItemComponent) const
{
	const FTINV_ItemManifest& Manifest = ItemComponent->GetItemManifest();
	return UTINV_InventoryGrid::HasRoomAcrossGrids(GetGridsInPriorityOrder(), Manifest, Manifest.GetStackCount());
}

void UTINV_SpatialInventory::OnItemAdded(UTINV_InventoryItem* Item)
{
	if (!IsValid(Item)) return;

	FTINV_SlotAvailabilityResult Result = UTINV_InventoryGrid::HasRoomAcrossGrids(
		GetGridsInPriorityOrder(), Item->GetItemManifest(), Item->GetTotalStackCount());
	Result.Item = Item;

	// Moved from the grid's old AddItem.
	if (const UTINV_ItemDataTable* ItemDataTable = InventoryGrid->GetItemDataTable())
	{
		if (const FTINV_ItemWeaponDataDefinition* WeaponData = ItemDataTable->GetWeaponData(Item->GetItemManifest().GetItemID()))
		{
			// const int32 MaxAmmo = WeaponData->WeaponDefaults.WeaponBaseMaxAmmo;
			// ...
		}
	}

	InventoryGrid->PostPickupNotification(Result, Item->GetItemManifest()); // Once, not once per grid.
	ApplyToAllGrids(Result);
}

void UTINV_SpatialInventory::OnStackChange(const FTINV_SlotAvailabilityResult& Result)
{
	if (Result.Item.IsValid())
	{
		InventoryGrid->PostPickupNotification(Result, Result.Item->GetItemManifest());
	}
	ApplyToAllGrids(Result);
}

void UTINV_SpatialInventory::ApplyToAllGrids(const FTINV_SlotAvailabilityResult& Result) const
{
	InventoryGrid->ApplySlotAvailabilities(Result);
	InventoryHotbar->ApplySlotAvailabilities(Result);
}

FReply UTINV_SpatialInventory::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	InventoryGrid->DropHoverItem();
	return FReply::Handled();
}

FReply UTINV_SpatialInventory::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UTINV_HeldItemSubsystem* Held = UTINV_HeldItemSubsystem::Get(this);
	if (Held && Held->IsDragging() && InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Held->CommitDrag();
		return FReply::Handled();
	}
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UTINV_SpatialInventory::OnHotbarSwapRequested(const int32 HotbarIndex)
{
	const UTINV_HeldItemSubsystem* Held = UTINV_HeldItemSubsystem::Get(this);
	if (Held && Held->IsDragging()) return;
	if (!InventoryHotbar->IsValidSlot(HotbarIndex)) return;

	UTINV_InventoryGrid* HoveredGrid = GetHoveredGrid();
	if (!HoveredGrid) return;

	SwapSlots(HoveredGrid, HoveredGrid->GetHoveredIndex(), InventoryHotbar, HotbarIndex);
}

UTINV_InventoryGrid* UTINV_SpatialInventory::GetHoveredGrid() const
{
	if (InventoryGrid->IsValidSlot(InventoryGrid->GetHoveredIndex())) return InventoryGrid;
	if (InventoryHotbar->IsValidSlot(InventoryHotbar->GetHoveredIndex())) return InventoryHotbar;
	return nullptr;
}

void UTINV_SpatialInventory::SwapSlots(UTINV_InventoryGrid* GridA, const int32 IndexA,
	UTINV_InventoryGrid* GridB, const int32 IndexB)
{
	if (GridA == GridB && IndexA == IndexB) return;

	// Read both sides before touching either.
	UTINV_InventoryItem* ItemA = GridA->GetSlotItem(IndexA);
	UTINV_InventoryItem* ItemB = GridB->GetSlotItem(IndexB);
	const int32 CountA = GridA->GetSlotCount(IndexA);
	const int32 CountB = GridB->GetSlotCount(IndexB);
	if (!ItemA && !ItemB) return;

	GridA->ClearSlot(IndexA);
	GridB->ClearSlot(IndexB);

	if (ItemB) GridA->SetSlotContents(IndexA, ItemB, CountB);
	if (ItemA) GridB->SetSlotContents(IndexB, ItemA, CountA);

	GridA->RefreshHighlight(IndexA);
	GridB->RefreshHighlight(IndexB);
}

void UTINV_SpatialInventory::SetMenuOpen(const bool bOpen, const bool bInstant)
{
	bMenuOpen = bOpen;

	if (!bOpen)
	{
		ReturnHeldItem();
		InventoryGrid->ResetHover();
		InventoryHotbar->ResetHover();
	}

	// Root stays on screen so the hotbar is always visible. While closed, nothing takes input.
	SetVisibility(bOpen ? ESlateVisibility::Visible : ESlateVisibility::SelfHitTestInvisible);
	InventoryHotbar->SetVisibility(bOpen ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::HitTestInvisible);

	if (bInstant) DockAlpha = bOpen ? 0.f : 1.f;

	BP_OnMenuOpenChanged(bOpen, bInstant);
}

void UTINV_SpatialInventory::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	float MeasuredOffset;
	if (TryComputeDockOffsetY(MeasuredOffset))
	{
		DockOffsetY = MeasuredOffset;
		if (!bDockOffsetReady)
		{
			bDockOffsetReady = true;
			InventoryHotbar->SetRenderOpacity(1.f);
		}
	}
	if (!bDockOffsetReady) return;

	const float Target = bMenuOpen ? 0.f : 1.f;
	DockAlpha = DockDuration > 0.f
		? FMath::FInterpConstantTo(DockAlpha, Target, InDeltaTime, 1.f / DockDuration)
		: Target;

	const float Eased = FMath::InterpEaseInOut(0.f, 1.f, DockAlpha, 2.f);
	const FVector2D NewTranslation(0.f, Eased * DockOffsetY);

	// Only touch the widget when it actually moves; settled frames do nothing.
	if (!InventoryHotbar->GetRenderTransform().Translation.Equals(NewTranslation, 0.01f))
	{
		InventoryHotbar->SetRenderTranslation(NewTranslation);
	}
}

bool UTINV_SpatialInventory::TryComputeDockOffsetY(float& OutOffsetY) const
{
	// The overlay around the hotbar. The hotbar moves inside it; the overlay itself never moves.
	const UWidget* HotbarFrame = InventoryHotbar->GetParent();
	if (!HotbarFrame) return false;

	const FGeometry& RootGeometry = GetCachedGeometry();
	const FGeometry& FrameGeometry = HotbarFrame->GetCachedGeometry();
	const FVector2D RootSize = RootGeometry.GetLocalSize();
	const FVector2D FrameSize = FrameGeometry.GetLocalSize();
	if (RootSize.IsNearlyZero() || FrameSize.IsNearlyZero()) return false; // Not laid out yet.

	// Both bottoms in absolute (screen) pixels.
	const float ScreenBottom = RootGeometry.LocalToAbsolute(FVector2D(0.f, RootSize.Y)).Y;
	const float FrameBottom = FrameGeometry.LocalToAbsolute(FVector2D(0.f, FrameSize.Y)).Y;

	// Screen pixels per local unit at the hotbar's depth, which includes DPI scale.
	const float PixelsPerUnit = FrameGeometry.GetAbsoluteSize().Y / FrameSize.Y;
	if (PixelsPerUnit <= 0.f) return false;

	OutOffsetY = (ScreenBottom - FrameBottom) / PixelsPerUnit - DockBottomMargin;
	return true;
}

void UTINV_SpatialInventory::ReturnHeldItem()
{
	UTINV_HeldItemSubsystem* Held = UTINV_HeldItemSubsystem::Get(this);
	if (!Held) return;

	Held->CancelDrag(); // Restores the full held count if a drag was in progress.

	UTINV_InventoryItem* Item = Held->GetHeldItem();
	if (!IsValid(Item)) return;
	const int32 Count = Held->GetHeldCount();

	// 1. Back to the exact slot it came from, if that slot is still free.
	UTINV_InventoryGrid* SourceGrid = Held->GetSourceGrid();
	const int32 SourceIndex = Held->GetSourceIndex();
	if (SourceGrid && SourceGrid->IsValidSlot(SourceIndex) && !SourceGrid->GetSlotItem(SourceIndex))
	{
		SourceGrid->SetSlotContents(SourceIndex, Item, Count);
		Held->ClearHeld();
		return;
	}

	// 2. Otherwise wherever it fits, using the same rules as a pickup.
	FTINV_SlotAvailabilityResult Result = UTINV_InventoryGrid::HasRoomAcrossGrids(
		GetGridsInPriorityOrder(), Item->GetItemManifest(), Count);
	Result.Item = Item;
	ApplyToAllGrids(Result);

	// 3. Anything that truly doesn't fit is dropped rather than lost.
	if (Result.Remainder > 0)
	{
		Held->SetHeldCount(Result.Remainder);
		InventoryGrid->DropHoverItem();
	}
	else
	{
		Held->ClearHeld();
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
