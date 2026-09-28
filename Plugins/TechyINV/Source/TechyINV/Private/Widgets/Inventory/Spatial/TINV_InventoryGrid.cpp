// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/Spatial/TINV_InventoryGrid.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "InventoryManagement/Components/TINV_InventoryComponent.h"
#include "InventoryManagement/Utils/TINV_InventoryStatics.h"
#include "ItemData/TINV_ItemDataTable.h"
#include "Items/TINV_InventoryItem.h"
#include "Items/Components/TINV_ItemComponent.h"
#include "Notifications/CUI_NotificationManager.h"
#include "Widgets/Inventory/TINV_SlottedItem.h"
#include "Widgets/Inventory/GridSlots/TINV_GridSlot.h"
#include "Widgets/Inventory/HoverItem/TINV_HoverItem.h"
#include "Widgets/Inventory/Icons/TINV_GlintedIcon.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Utils/TINV_WidgetUtils.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryGrid.cpp_Functions
void UTINV_InventoryGrid::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ConstructGrid();
	InventoryComponent = UTINV_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	InventoryComponent->OnItemAdded.AddDynamic(this, &ThisClass::AddItem);
	InventoryComponent->OnStackChange.AddDynamic(this, &ThisClass::AddStacks);
}

void UTINV_InventoryGrid::OnGridSlotClicked(int32 GridIndex, const FPointerEvent& MouseEvent)
{
	if (!GridSlots.IsValidIndex(GridIndex)) return;
	
	if (bIsDragging)
	{
		if (IsRightClick(MouseEvent)) CancelDrag();
		return;
	}

	UTINV_GridSlot* GridSlot = GridSlots[GridIndex];

	if (!IsValid(HoverItem))
	{
		if (!IsSlotEmpty(GridSlot))
		{
			UTINV_InventoryItem* Item = GridSlot->GetInventoryItem().Get();
			if (IsLeftClick(MouseEvent) || IsMiddleClick(MouseEvent)) PickUp(Item, GridIndex);
			else if (IsRightClick(MouseEvent)) IsStackable(Item) ? PickUpHalf(GridIndex) : PickUp(Item, GridIndex);
		}
	}
	else if (CanStartDrag(GridIndex, MouseEvent))
	{
		BeginDrag(GridIndex);
	}
	else
	{
		switch (GetDropAction(GridIndex))
		{
		case ETINV_DropAction::Place: PutDownOnIndex(GridIndex);    break;
		case ETINV_DropAction::Merge: MergeStacks(GridIndex);       break;
		case ETINV_DropAction::Swap:  SwapWithHoverItem(GridIndex); break;
		default: break;
		}
	}
	RefreshHighlight(GridIndex);
	RefreshCursor();
}

void UTINV_InventoryGrid::OnGridSlotDoubleClicked(int32 GridIndex, const FPointerEvent& MouseEvent)
{
	if (!GridSlots.IsValidIndex(GridIndex) || !IsLeftClick(MouseEvent) || bIsDragging) return;
	if (!IsValid(HoverItem))
	{
		UTINV_GridSlot* GridSlot = GridSlots[GridIndex];
		if (IsSlotEmpty(GridSlot)) return;
		PickUp(GridSlot->GetInventoryItem().Get(), GridIndex);
	}

	CollectMatchingStacks();
	RefreshHighlight(GridIndex);
	RefreshCursor();
}

void UTINV_InventoryGrid::OnGridSlotHovered(int32 GridIndex, const FPointerEvent& MouseEvent)
{
	HoveredIndex = GridIndex;

	if (bIsDragging)
	{
		if (!MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) CommitDrag();
		else AddDragPath(LastDragIndex, GridIndex);
	}
	RefreshHighlight(GridIndex);
}

void UTINV_InventoryGrid::OnGridSlotUnHovered(int32 GridIndex, const FPointerEvent& MouseEvent)
{
	if (HoveredIndex == GridIndex) HoveredIndex = INDEX_NONE;
	if (bIsDragging && DragIndices.Contains(GridIndex)) return;
	if (GridSlots.IsValidIndex(GridIndex)) GridSlots[GridIndex]->RestoreTexture();
}

FReply UTINV_InventoryGrid::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bIsDragging && IsLeftClick(InMouseEvent))
	{
		CommitDrag();
		return FReply::Handled();
	}
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

FReply UTINV_InventoryGrid::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	const float Delta = InMouseEvent.GetWheelDelta();
	const bool bScrollUp = Delta > 0.f;

	// Nothing to do here: let the scroll pass through to any parent (e.g. a ScrollBox).
	const bool bCanAct = !bIsDragging
		&& GridSlots.IsValidIndex(HoveredIndex)
		&& (bScrollUp ? CanScrollTake(HoveredIndex) : CanScrollPlace(HoveredIndex));
	if (!bCanAct)
	{
		ScrollAccumulator = 0.f;
		return Super::NativeOnMouseWheel(InGeometry, InMouseEvent);
	}

	// Changing direction starts fresh.
	if (FMath::Sign(ScrollAccumulator) != FMath::Sign(Delta)) ScrollAccumulator = 0.f;
	ScrollAccumulator += Delta;

	// One item per whole notch. Trackpads send fractions, so they add up first.
	while (ScrollAccumulator >= 1.f && CanScrollTake(HoveredIndex))
	{
		ScrollTakeOne(HoveredIndex);
		ScrollAccumulator -= 1.f;
	}
	while (ScrollAccumulator <= -1.f && CanScrollPlace(HoveredIndex))
	{
		ScrollPlaceOne(HoveredIndex);
		ScrollAccumulator += 1.f;
	}

	// Drop any leftover whole notches that couldn't be applied (slot filled up, hand emptied).
	ScrollAccumulator = FMath::Fmod(ScrollAccumulator, 1.f);

	RefreshHighlight(HoveredIndex);
	RefreshCursor();
	return FReply::Handled();
}

bool UTINV_InventoryGrid::CanScrollPlace(const int32 Index) const
{
	if (!IsValid(HoverItem)) return false;

	const UTINV_InventoryItem* HeldItem = HoverItem->GetInventoryItem();
	if (!IsStackable(HeldItem)) return IsSlotEmpty(GridSlots[Index]);

	if (HoverItem->GetStackCount() <= 0) return false;

	const UTINV_GridSlot* GridSlot = GridSlots[Index];
	if (IsSlotEmpty(GridSlot)) return true;

	return IsSameItem(GridSlot, HeldItem->GetItemManifest().GetItemID())
	   && GridSlot->GetStackCount() < GetMaxStackSize(HeldItem);
}

bool UTINV_InventoryGrid::CanScrollTake(const int32 Index) const
{
	const UTINV_GridSlot* GridSlot = GridSlots[Index];
	if (IsSlotEmpty(GridSlot)) return false;

	if (!IsValid(HoverItem)) return true; // Empty hand: pick up anything.

	// Holding something: only pull more of the same stackable item.
	const UTINV_InventoryItem* SlotItem = GridSlot->GetInventoryItem().Get();
	if (!IsStackable(SlotItem)) return false;

	return IsSameItem(GridSlot, HoverItem->GetInventoryItem()->GetItemManifest().GetItemID())
		&& HoverItem->GetStackCount() < GetMaxStackSize(SlotItem);
}

void UTINV_InventoryGrid::ScrollPlaceOne(const int32 Index)
{
	UTINV_InventoryItem* HeldItem = HoverItem->GetInventoryItem();

	if (!IsStackable(HeldItem))
	{
		PutDownOnIndex(Index);
		return;
	}

	if (IsSlotEmpty(GridSlots[Index]))
	{
		AddItemAtIndex(HeldItem, Index, true, 1);
		UpdateGridSlots(HeldItem, Index, true, 1);
	}
	else
	{
		SetSlotStackCount(Index, GridSlots[Index]->GetStackCount() + 1);
	}

	const int32 Remaining = HoverItem->GetStackCount() - 1;
	if (Remaining <= 0) ClearHoverItem();
	else HoverItem->UpdateStackCount(Remaining);
}

void UTINV_InventoryGrid::ScrollTakeOne(const int32 Index)
{
	UTINV_InventoryItem* SlotItem = GridSlots[Index]->GetInventoryItem().Get();

	// Non-stackables come up whole, exactly like a left-click pickup.
	if (!IsStackable(SlotItem))
	{
		PickUp(SlotItem, Index);
		return;
	}

	TakeFromSlot(Index, 1);

	if (!IsValid(HoverItem))
	{
		AssignHoverItem(SlotItem, Index, Index);
		HoverItem->UpdateStackCount(1);
	}
	else
	{
		HoverItem->UpdateStackCount(HoverItem->GetStackCount() + 1);
	}
}

int32 UTINV_InventoryGrid::GetMaxStackSize(const UTINV_InventoryItem* Item) const
{
	const FTINV_ItemDataDefinition* ItemData = GetItemData(Item->GetItemManifest());
	return ItemData ? FMath::Max(1, ItemData->MaxStackSize) : 1;
}

int32 UTINV_InventoryGrid::TakeFromSlot(const int32 Index, const int32 Amount)
{
	const int32 Available = GridSlots[Index]->GetStackCount();
	const int32 Taken = FMath::Min(Available, Amount);

	if (Taken >= Available) RemoveItemFromGrid(GridSlots[Index]->GetInventoryItem().Get(), Index);
	else SetSlotStackCount(Index, Available - Taken);

	return Taken;
}

void UTINV_InventoryGrid::PickUpHalf(const int32 Index)
{
	UTINV_InventoryItem* Item = GridSlots[Index]->GetInventoryItem().Get();
	const int32 Half = FMath::DivideAndRoundUp(GridSlots[Index]->GetStackCount(), 2);

	const int32 Taken = TakeFromSlot(Index, Half);
	AssignHoverItem(Item, Index, Index);
	HoverItem->UpdateStackCount(Taken);
}

void UTINV_InventoryGrid::CollectMatchingStacks()
{
	UTINV_InventoryItem* HeldItem = HoverItem->GetInventoryItem();
	if (!IsStackable(HeldItem)) return;

	const int32 MaxStack = GetMaxStackSize(HeldItem);
	int32 HeldCount = HoverItem->GetStackCount();
	
	for (const int32 Index : GetMatchingStackIndices(HeldItem->GetItemManifest().GetItemID()))
	{
		if (HeldCount >= MaxStack) break;
		HeldCount += TakeFromSlot(Index, MaxStack - HeldCount);
	}
	HoverItem->UpdateStackCount(HeldCount);
}

TArray<int32> UTINV_InventoryGrid::GetMatchingStackIndices(const FGameplayTag& ItemID) const
{
	TArray<int32> Indices;
	for (const UTINV_GridSlot* GridSlot : GridSlots)
	{
		if (IsSameItem(GridSlot, ItemID)) Indices.Add(GridSlot->GetTileIndex());
	}

	Indices.Sort([this](const int32 A, const int32 B)
	{
		return GridSlots[A]->GetStackCount() < GridSlots[B]->GetStackCount();
	});
	return Indices;
}

bool UTINV_InventoryGrid::CanStartDrag(const int32 Index, const FPointerEvent& MouseEvent) const
{
	return IsLeftClick(MouseEvent)
		&& IsValid(HoverItem)
		&& IsStackable(HoverItem->GetInventoryItem())
		&& IsDragTarget(Index);
}

bool UTINV_InventoryGrid::CanAddToDrag(const int32 Index) const
{
	return bIsDragging
		&& GridSlots.IsValidIndex(Index)
		&& !DragIndices.Contains(Index)
		&& DragIndices.Num() < DragSourceCount
		&& IsDragTarget(Index);
}

void UTINV_InventoryGrid::BeginDrag(const int32 Index)
{
	bIsDragging = true;
	DragSourceCount = HoverItem->GetStackCount();
	DragIndices.Reset();

	AddDragSlot(Index);
	LastDragIndex = Index;
	UpdateDragPreview();
}

void UTINV_InventoryGrid::AddDragSlot(const int32 Index)
{
	DragIndices.Add(Index);
	DragBaseCounts.Add(Index, GridSlots[Index]->GetStackCount()); 

	if (IsSlotEmpty(GridSlots[Index]))
	{
		UTINV_SlottedItem* Preview = CreateSlottedItem(HoverItem->GetInventoryItem(), Index, true, 0);
		AddSlottedItemToCanvas(Index, Preview);
		DragPreviews.Add(Index, Preview);
	}

	GetDragDisplay(Index)->SetPreview(true);
	GridSlots[Index]->SetSelectedTexture();
}

void UTINV_InventoryGrid::AddDragPath(const int32 FromIndex, const int32 ToIndex)
{
	if (!GridSlots.IsValidIndex(FromIndex) || !GridSlots.IsValidIndex(ToIndex)) return;

	FIntPoint Current(FromIndex % Columns, FromIndex / Columns);
	const FIntPoint Target(ToIndex % Columns, ToIndex / Columns);
	
	const int32 DeltaX = FMath::Abs(Target.X - Current.X);
	const int32 DeltaY = -FMath::Abs(Target.Y - Current.Y);
	const int32 StepX = Current.X < Target.X ? 1 : -1;
	const int32 StepY = Current.Y < Target.Y ? 1 : -1;
	int32 Error = DeltaX + DeltaY;

	bool bAddedAny = false;
	while (true)
	{
		const int32 Index = Current.Y * Columns + Current.X;
		if (CanAddToDrag(Index))
		{
			AddDragSlot(Index);
			bAddedAny = true;
		}

		if (Current == Target) break;

		const int32 DoubledError = 2 * Error;
		if (DoubledError >= DeltaY) { Error += DeltaY; Current.X += StepX; }
		if (DoubledError <= DeltaX) { Error += DeltaX; Current.Y += StepY; }
	}

	LastDragIndex = ToIndex;
	if (bAddedAny) UpdateDragPreview();
}

void UTINV_InventoryGrid::UpdateDragPreview()
{
	const int32 Share = DragSourceCount / DragIndices.Num();
	int32 Placed = 0;

	for (const int32 Index : DragIndices)
	{
		const int32 Amount = GetDragAmount(Index, Share);
		GetDragDisplay(Index)->UpdateStackCount(DragBaseCounts[Index] + Amount);
		Placed += Amount;
	}
	HoverItem->UpdateStackCount(DragSourceCount - Placed);
}

void UTINV_InventoryGrid::CommitDrag()
{
	if (!bIsDragging) return;

	UTINV_InventoryItem* HeldItem = HoverItem->GetInventoryItem();
	const int32 Share = DragSourceCount / DragIndices.Num();

	// Work out every placement before the drag state is cleared.
	TArray<TPair<int32, int32>> Placements; // Index, amount added.
	int32 Placed = 0;
	for (const int32 Index : DragIndices)
	{
		const int32 Amount = GetDragAmount(Index, Share);
		Placements.Emplace(Index, Amount);
		Placed += Amount;
	}
	const int32 Leftover = DragSourceCount - Placed;

	ClearDragState(); // Existing stacks go back to their base counts first.

	for (const TPair<int32, int32>& Placement : Placements)
	{
		const int32 Index = Placement.Key;
		if (IsSlotEmpty(GridSlots[Index]))
		{
			AddItemAtIndex(HeldItem, Index, true, Placement.Value);
			UpdateGridSlots(HeldItem, Index, true, Placement.Value);
		}
		else
		{
			SetSlotStackCount(Index, GridSlots[Index]->GetStackCount() + Placement.Value);
		}
	}

	if (Leftover > 0) HoverItem->UpdateStackCount(Leftover);
	else ClearHoverItem();

	RefreshHighlight(HoveredIndex);
}

void UTINV_InventoryGrid::CancelDrag()
{
	if (!bIsDragging) return;
	HoverItem->UpdateStackCount(DragSourceCount);
	ClearDragState();
	RefreshHighlight(HoveredIndex);
}

void UTINV_InventoryGrid::ClearDragState()
{
	for (const int32 Index : DragIndices)
	{
		if (const TObjectPtr<UTINV_SlottedItem>* Preview = DragPreviews.Find(Index))
		{
			(*Preview)->RemoveFromParent(); // Temporary widget on an empty slot.
		}
		else if (UTINV_SlottedItem* Existing = SlottedItems.FindRef(Index))
		{
			Existing->SetPreview(false);    // Real stack: back to normal look and count.
			Existing->UpdateStackCount(DragBaseCounts.FindRef(Index));
		}
		GridSlots[Index]->RestoreTexture();
	}

	DragPreviews.Reset();
	DragBaseCounts.Reset();
	DragIndices.Reset();
	DragSourceCount = 0;
	bIsDragging = false;
	LastDragIndex = INDEX_NONE;
}

// Empty slot, or a non-full stack of the held item.
bool UTINV_InventoryGrid::IsDragTarget(const int32 Index) const
{
	const UTINV_GridSlot* GridSlot = GridSlots[Index];
	if (IsSlotEmpty(GridSlot)) return true;

	const UTINV_InventoryItem* HeldItem = HoverItem->GetInventoryItem();
	return IsSameItem(GridSlot, HeldItem->GetItemManifest().GetItemID())
		&& GridSlot->GetStackCount() < GetMaxStackSize(HeldItem);
}

// How much of the even share actually fits in this slot.
int32 UTINV_InventoryGrid::GetDragAmount(const int32 Index, const int32 Share) const
{
	const int32 Room = GetMaxStackSize(HoverItem->GetInventoryItem()) - DragBaseCounts.FindChecked(Index);
	return FMath::Min(Share, Room);
}

// The widget showing this slot's preview: a temporary one for empty slots, the real one otherwise.
UTINV_SlottedItem* UTINV_InventoryGrid::GetDragDisplay(const int32 Index) const
{
	if (const TObjectPtr<UTINV_SlottedItem>* Preview = DragPreviews.Find(Index)) return *Preview;
	return SlottedItems.FindRef(Index);
}

void UTINV_InventoryGrid::RefreshHighlight(const int32 Index)
{
	if (!GridSlots.IsValidIndex(Index)) return;
	UTINV_GridSlot* GridSlot = GridSlots[Index];

	switch (GetDropAction(Index))
	{
	case ETINV_DropAction::Place: GridSlot->SetSelectedTexture();   break;
	case ETINV_DropAction::Merge: GridSlot->SetSelectedTexture();   break;
	case ETINV_DropAction::Swap:  GridSlot->SetGrayedOutTexture();  break;
	case ETINV_DropAction::None: GridSlot->RestoreTexture(); break;
	}
}

void UTINV_InventoryGrid::MergeStacks(const int32 Index)
{
	const int32 MaxStack = GetItemData(HoverItem->GetInventoryItem()->GetItemManifest())->MaxStackSize;
	const int32 SlotCount = GridSlots[Index]->GetStackCount();
	const int32 HeldCount = HoverItem->GetStackCount();

	if (SlotCount >= MaxStack) // Slot full: swap counts.
	{
		SetSlotStackCount(Index, HeldCount);
		HoverItem->UpdateStackCount(SlotCount);
		return;
	}

	const int32 Moved = FMath::Min(MaxStack - SlotCount, HeldCount);
	SetSlotStackCount(Index, SlotCount + Moved);

	if (HeldCount - Moved <= 0) ClearHoverItem();
	else HoverItem->UpdateStackCount(HeldCount - Moved);
}

void UTINV_InventoryGrid::SwapWithHoverItem(const int32 Index)
{
	UTINV_InventoryItem* HeldItem = HoverItem->GetInventoryItem();
	const int32 HeldCount = HoverItem->GetStackCount();
	UTINV_InventoryItem* SlotItem = GridSlots[Index]->GetInventoryItem().Get();

	AssignHoverItem(SlotItem, Index, HoverItem->GetPreviousGridIndex());
	RemoveItemFromGrid(SlotItem, Index);

	const bool bStackable = IsStackable(HeldItem);
	AddItemAtIndex(HeldItem, Index, bStackable, HeldCount);
	UpdateGridSlots(HeldItem, Index, bStackable, HeldCount);
}

// The hover item is a software cursor, which Slate only re-evaluates on mouse movement.
// Call this after changing the hover item without the mouse moving (e.g. scrolling).
void UTINV_InventoryGrid::RefreshCursor() const
{
	if (IsValid(HoverItem))
	{
		HoverItem->SetDisplaySize(TileSize * UWidgetLayoutLibrary::GetViewportScale(this));
		HoverItem->ForceLayoutPrepass();
	}

	if (!FSlateApplication::IsInitialized()) return;
	FSlateApplication& Slate = FSlateApplication::Get();
	Slate.QueryCursor();                // Re-resolve which cursor widget to draw.
	Slate.SetCursorPos(Slate.GetCursorPos()); // Fake a move so hover and cursor both refresh.
}

auto UTINV_InventoryGrid::PutDownOnIndex(const int32 Index) -> void
{
	UTINV_InventoryItem* HeldItem = HoverItem->GetInventoryItem();
	const bool bStackable = IsStackable(HeldItem);
	AddItemAtIndex(HeldItem, Index, bStackable, HoverItem->GetStackCount());
	UpdateGridSlots(HeldItem, Index, bStackable, HoverItem->GetStackCount());
	ClearHoverItem();
}

void UTINV_InventoryGrid::SetSlotStackCount(const int32 Index, const int32 NewCount)
{
	GridSlots[Index]->SetStackCount(NewCount);
	SlottedItems.FindChecked(Index)->UpdateStackCount(NewCount);
}

ETINV_DropAction UTINV_InventoryGrid::GetDropAction(const int32 Index) const
{
	if (!IsValid(HoverItem) || !GridSlots.IsValidIndex(Index)) return ETINV_DropAction::None;

	const UTINV_GridSlot* GridSlot = GridSlots[Index];
	if (IsSlotEmpty(GridSlot)) return ETINV_DropAction::Place;

	const UTINV_InventoryItem* HeldItem = HoverItem->GetInventoryItem();
	if (IsStackable(HeldItem) && IsSameItem(GridSlot, HeldItem->GetItemManifest().GetItemID()))
	{
		return ETINV_DropAction::Merge;
	}
	return ETINV_DropAction::Swap;
}


FTINV_SlotAvailabilityResult UTINV_InventoryGrid::HasRoomForItem(const UTINV_ItemComponent* ItemComponent)
{
	const FTINV_ItemManifest Manifest = ItemComponent->GetItemManifest();
	return HasRoomForItem(Manifest, Manifest.GetStackCount());
}

FTINV_SlotAvailabilityResult UTINV_InventoryGrid::HasRoomForItem(const UTINV_InventoryItem* Item)
{
	return HasRoomForItem(Item->GetItemManifest(), Item->GetTotalStackCount());
}

FTINV_SlotAvailabilityResult UTINV_InventoryGrid::HasRoomForItem(const FTINV_ItemManifest& Manifest, const int32 StackAmount)
{
	FTINV_SlotAvailabilityResult Result;

	// Look up the item's data by its tag.
	const FTINV_ItemDataDefinition* ItemData = GetItemData(Manifest);
	if (!ItemData) return Result;

	const FGameplayTag ItemID = Manifest.GetItemID();

	// Determine if the item is stackable, and how much we need to place.
	Result.bStackable = ItemData->MaxStackSize > 1;
	const int32 MaxStackSize = Result.bStackable ? ItemData->MaxStackSize : 1;
	int32 AmountToFill = Result.bStackable ? FMath::Max(1, StackAmount) : 1;

	// Pass 1: check EVERY grid slot for a non-full stack of the same item and fill it first.
	if (Result.bStackable)
	{
		for (const UTINV_GridSlot* GridSlot : GridSlots)
		{
			if (AmountToFill <= 0) break;

			// Is this the same item?
			if (!IsSameItem(GridSlot, ItemID)) continue;

			// Is this stack already full?
			const int32 RoomInSlot = GetRoomInSlot(GridSlot, MaxStackSize);
			if (RoomInSlot <= 0) continue;

			// Fill as much of this stack as we can.
			AddSlotAvailability(Result, GridSlot, FMath::Min(RoomInSlot, AmountToFill), true, AmountToFill);
		}
	}

	// Pass 2: place the remainder into the first available empty slots.
	for (const UTINV_GridSlot* GridSlot : GridSlots)
	{
		if (AmountToFill <= 0) break;

		// Is this slot empty?
		if (!IsSlotEmpty(GridSlot)) continue;

		AddSlotAvailability(Result, GridSlot, FMath::Min(MaxStackSize, AmountToFill), false, AmountToFill);
	}

	// Whatever couldn't fit.
	Result.Remainder = AmountToFill;
	return Result;
}

bool UTINV_InventoryGrid::IsSlotEmpty(const UTINV_GridSlot* GridSlot) const
{
	return !GridSlot->GetInventoryItem().IsValid();
}

bool UTINV_InventoryGrid::IsSameItem(const UTINV_GridSlot* GridSlot, const FGameplayTag& ItemID) const
{
	const UTINV_InventoryItem* SlotItem = GridSlot->GetInventoryItem().Get();
	return IsValid(SlotItem) && SlotItem->GetItemManifest().GetItemID().MatchesTagExact(ItemID);
}

int32 UTINV_InventoryGrid::GetRoomInSlot(const UTINV_GridSlot* GridSlot, const int32 MaxStackSize) const
{
	return MaxStackSize - GridSlot->GetStackCount();
}

void UTINV_InventoryGrid::AddSlotAvailability(FTINV_SlotAvailabilityResult& Result, const UTINV_GridSlot* GridSlot,
	const int32 FillAmount, const bool bItemAtIndex, int32& AmountToFill) const
{
	Result.SlotAvailabilities.Emplace(FTINV_SlotAvailability{
		GridSlot->GetTileIndex(),
		Result.bStackable ? FillAmount : 0,
		bItemAtIndex
	});
	Result.TotalRoomToFill += FillAmount;
	AmountToFill -= FillAmount;
}

bool UTINV_InventoryGrid::IsRightClick(const FPointerEvent& MouseEvent) const
{
	return MouseEvent.GetEffectingButton() == EKeys::RightMouseButton;
}

bool UTINV_InventoryGrid::IsLeftClick(const FPointerEvent& MouseEvent) const
{
	return MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton;
}

bool UTINV_InventoryGrid::IsShiftClick(const FPointerEvent& MouseEvent) const
{
	return MouseEvent.IsShiftDown();
}

bool UTINV_InventoryGrid::IsMiddleClick(const FPointerEvent& MouseEvent) const
{
	return MouseEvent.GetEffectingButton() == EKeys::MiddleMouseButton;
}

void UTINV_InventoryGrid::AddItem(UTINV_InventoryItem* Item)
{
	check(ItemDataTable);
	const FTINV_SlotAvailabilityResult Result = HasRoomForItem(Item);

	PostPickupNotification(Result, Item->GetItemManifest());

	if (const FTINV_ItemWeaponDataDefinition* WeaponData = ItemDataTable->GetWeaponData(Item->GetItemManifest().GetItemID()))
	{
		int32 MaxAmmo = WeaponData->WeaponDefaults.WeaponBaseMaxAmmo;
		// ...
	}

	AddItemToIndices(Result, Item);
}

const FTINV_ItemDataDefinition* UTINV_InventoryGrid::GetItemData(const FTINV_ItemManifest& Manifest) const
{
	return ItemDataTable ? ItemDataTable->GetDataByTag(Manifest.GetItemID()) : nullptr;
}

void UTINV_InventoryGrid::AddItemToIndices(const FTINV_SlotAvailabilityResult& Result, UTINV_InventoryItem* NewItem)
{
	for (const auto& Availability : Result.SlotAvailabilities)
	{
		AddItemAtIndex(NewItem, Availability.Index, Result.bStackable, Availability.AmountToFill);
		UpdateGridSlots(NewItem, Availability.Index, Result.bStackable, Availability.AmountToFill);
	}
	
}

UTINV_SlottedItem* UTINV_InventoryGrid::CreateSlottedItem(UTINV_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount) const
{
	UTINV_SlottedItem* SlottedItem = CreateWidget<UTINV_SlottedItem>(GetOwningPlayer(), SlottedItemClass);
	SlottedItem->SetInventoryItem(Item);
	SlottedItem->SetGridIndex(Index);
	SlottedItem->SetIsStackable(bStackable);
	SlottedItem->UpdateStackCount(bStackable ? StackAmount : 0);
	SlottedItem->SetVisibility(ESlateVisibility::HitTestInvisible);
	
	UTINV_GlintedIcon* GlintedIcon = SlottedItem->GetGlintedIcon();
	GlintedIcon->SetItemDataTable(ItemDataTable);
	GlintedIcon->SetFromInventoryItem(Item);

	return SlottedItem;
}

void UTINV_InventoryGrid::PickUp(UTINV_InventoryItem* ClickedInventoryItem, const int32 GridIndex)
{
	AssignHoverItem(ClickedInventoryItem, GridIndex, GridIndex);
	RemoveItemFromGrid(ClickedInventoryItem, GridIndex);
}

void UTINV_InventoryGrid::AssignHoverItem(UTINV_InventoryItem* InventoryItem)
{
	if (!IsValid(HoverItem))
	{
		HoverItem = CreateWidget<UTINV_HoverItem>(GetOwningPlayer(), HoverItemClass);
	}

	HoverItem->SetInventoryItem(InventoryItem);
	/* TODO: There's a much smarter way to get this that im too lazy to do right now, but basically any item with a
	 * stack count of 0 isn't stackable.
	 */
	
	UTINV_GlintedIcon* GlintedIcon = HoverItem->GetGlintedIcon();
	GlintedIcon->SetItemDataTable(ItemDataTable);
	GlintedIcon->SetFromInventoryItem(InventoryItem);

	HoverItem->SetDisplaySize(TileSize * UWidgetLayoutLibrary::GetViewportScale(this));
	GetOwningPlayer()->SetMouseCursorWidget(EMouseCursor::Default, HoverItem);
}

void UTINV_InventoryGrid::AssignHoverItem(UTINV_InventoryItem* InventoryItem, const int32 GridIndex, const int32 PreviousGridIndex)
{
	AssignHoverItem(InventoryItem);

	HoverItem->SetPreviousGridIndex(PreviousGridIndex);
	HoverItem->UpdateStackCount(IsStackable(InventoryItem) ? GridSlots[GridIndex]->GetStackCount() : 0);
}

void UTINV_InventoryGrid::ClearHoverItem()
{
	if (!IsValid(HoverItem)) return;

	HoverItem->SetInventoryItem(nullptr);
	HoverItem->SetPreviousGridIndex(INDEX_NONE);
	HoverItem->UpdateStackCount(0);
	HoverItem->RemoveFromParent();
	HoverItem = nullptr;

	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->SetMouseCursorWidget(EMouseCursor::Default, nullptr);
	}
}

void UTINV_InventoryGrid::RemoveItemFromGrid(UTINV_InventoryItem* InventoryItem, const int32 GridIndex)
{
	// Resolve Grid Slots.
	GridSlots[GridIndex]->SetInventoryItem(nullptr);
	GridSlots[GridIndex]->SetUnoccupiedTexture();
	GridSlots[GridIndex]->SetStackCount(0);

	// Resolve SlottedItems.
	if (SlottedItems.Contains(GridIndex))
	{
		TObjectPtr<UTINV_SlottedItem> FoundSlottedItem;
		SlottedItems.RemoveAndCopyValue(GridIndex, FoundSlottedItem);
		FoundSlottedItem->RemoveFromParent();
	}
}


bool UTINV_InventoryGrid::IsStackable(const UTINV_InventoryItem* ItemToCheck) const
{
	return ItemDataTable->GetDataByTag(ItemToCheck->GetItemManifest().GetItemID())->MaxStackSize > 1 ? true : false;
}

void UTINV_InventoryGrid::AddItemAtIndex(UTINV_InventoryItem* Item, const int32 Index, const bool bStackable,
                                         const int32 StackAmount)
{
	UTINV_SlottedItem* SlottedItem = CreateSlottedItem(Item, Index, bStackable, StackAmount);
	AddSlottedItemToCanvas(Index, SlottedItem);
	SlottedItems.Add(Index, SlottedItem);
}

void UTINV_InventoryGrid::AddSlottedItemToCanvas(const int32 Index, UTINV_SlottedItem* SlottedItem) const
{
	CanvasPanel->AddChildToCanvas(SlottedItem);
	UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(SlottedItem);
	const FVector2D Size(TileSize);
	CanvasSlot->SetSize(Size);
	const FVector2D DrawPos = UTINV_WidgetUtils::GetPositionFromIndex(Index, Columns) * TileSize;
	CanvasSlot->SetPosition(DrawPos);
}

void UTINV_InventoryGrid::UpdateGridSlots(UTINV_InventoryItem* NewItem, const int32 Index, bool bStackableItem, const int32 StackAmount)
{
	check(GridSlots.IsValidIndex(Index));

	GridSlots[Index]->SetStackCount(bStackableItem ? StackAmount : 0);
	
	UTINV_GridSlot* GridSlot = GridSlots[Index];
	
	ETINV_ItemTier ItemTier = ETINV_ItemTier::Scrap;
	
	if (const FTINV_ItemDataDefinition* ItemData = ItemDataTable->GetDataByTag(NewItem->GetItemManifest().GetItemID()))
	{
		ItemTier = ItemData->ItemTier;
	}

	GridSlot->SetInventoryItem(NewItem);
	GridSlot->SetOccupiedTexture(ItemTier);
}

void UTINV_InventoryGrid::ConstructGrid()
{
	GridSlots.Reserve(Rows * Columns);

	for (int32 j = 0; j < Rows; j++)
	{
		for (int32 i = 0; i < Columns; i++)
		{
			UTINV_GridSlot* GridSlot = CreateWidget<UTINV_GridSlot>(this, GridSlotClass);
			CanvasPanel->AddChild(GridSlot);

			const FIntPoint TilePosition = FIntPoint(i, j);
			
			GridSlot->SetTileIndex(UTINV_WidgetUtils::GetIndexFromPosition(TilePosition, Columns));

			UCanvasPanelSlot* GridCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridSlot);
			GridCPS->SetSize(FVector2D(TileSize));
			GridCPS->SetPosition(TilePosition * TileSize);

			GridSlots.Add(GridSlot);
			GridSlot->GridSlotClicked.AddDynamic(this, &ThisClass::OnGridSlotClicked);
			GridSlot->GridSlotHovered.AddDynamic(this, &ThisClass::OnGridSlotHovered);
			GridSlot->GridSlotUnHovered.AddDynamic(this, &ThisClass::OnGridSlotUnHovered);
			GridSlot->GridSlotDoubleClicked.AddDynamic(this, &ThisClass::OnGridSlotDoubleClicked);
		}
	}
}

void UTINV_InventoryGrid::AddStacks(const FTINV_SlotAvailabilityResult& Result)
{
	if (Result.Item.IsValid())
	{
		PostPickupNotification(Result, Result.Item->GetItemManifest());
	}
	
	for (const auto& Availability : Result.SlotAvailabilities)
	{
		if (Availability.bItemAtIndex)
		{
			const auto& GridSlot = GridSlots[Availability.Index];
			const auto& SlottedItem = SlottedItems.FindChecked(Availability.Index);
			SlottedItem->UpdateStackCount(GridSlot->GetStackCount() + Availability.AmountToFill);
			GridSlot->SetStackCount(GridSlot->GetStackCount() + Availability.AmountToFill);
		}
		else
		{
			AddItemAtIndex(Result.Item.Get(), Availability.Index, Result.bStackable, Availability.AmountToFill);
			UpdateGridSlots(Result.Item.Get(), Availability.Index, Result.bStackable, Availability.AmountToFill);
		}
	}
}

void UTINV_InventoryGrid::PostPickupNotification(const FTINV_SlotAvailabilityResult& Result, const FTINV_ItemManifest& Manifest) const
{
	const FTINV_ItemDataDefinition* ItemData = GetItemData(Manifest);
	if (!ItemData) return;

	const int32 AmountAdded = Result.TotalRoomToFill;

	if (AmountAdded > 0)
	{
		UCUI_NotificationManager::PostItem(this,
			ItemData->ItemName,
			true,
			ItemData->ItemIcon,
			UTINV_WidgetUtils::GetCUIItemTier(ItemData->ItemTier),
			-1.f,          
			AmountAdded,
			Manifest.GetItemID().GetTagName());
	}

	if (Result.Remainder > 0)
	{
		UCUI_NotificationManager::PostWarning(this,
			FText::Format(NSLOCTEXT("Cyberscape", "InventoryFull", "Inventory full: {0} x{1} left behind"),
				ItemData->ItemName, Result.Remainder),
			true);
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
