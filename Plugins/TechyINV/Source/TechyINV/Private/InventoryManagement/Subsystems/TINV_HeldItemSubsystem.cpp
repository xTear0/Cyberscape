// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "InventoryManagement/Subsystems/TINV_HeldItemSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Framework/Application/SlateApplication.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Items/TINV_InventoryItem.h"
#include "Widgets/Inventory/HoverItem/TINV_HoverItem.h"
#include "Widgets/Inventory/Icons/TINV_GlintedIcon.h"
#include "Widgets/Inventory/Spatial/TINV_InventoryGrid.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_HeldItemSubsystem.cpp_Functions
UTINV_HeldItemSubsystem* UTINV_HeldItemSubsystem::Get(const UUserWidget* Widget)
{
	const ULocalPlayer* LocalPlayer = IsValid(Widget) ? Widget->GetOwningLocalPlayer() : nullptr;
	return LocalPlayer ? LocalPlayer->GetSubsystem<UTINV_HeldItemSubsystem>() : nullptr;
}

void UTINV_HeldItemSubsystem::Deinitialize()
{
	HeldItem.Reset();
	SourceGrid.Reset();
	HoverItemWidget = nullptr;
	Super::Deinitialize();
}

void UTINV_HeldItemSubsystem::Hold(UTINV_InventoryItem* Item, const int32 StackCount,
	UTINV_InventoryGrid* InSourceGrid, const int32 InSourceIndex)
{
	if (!IsValid(Item))
	{
		ClearHeld();
		return;
	}

	HeldItem = Item;
	HeldCount = FMath::Max(0, StackCount);
	SourceGrid = InSourceGrid;
	SourceIndex = InSourceIndex;

	ShowWidget(InSourceGrid);
	OnHeldItemChanged.Broadcast();
}

void UTINV_HeldItemSubsystem::SetHeldCount(const int32 NewCount)
{
	if (!IsHolding()) return;

	HeldCount = FMath::Max(0, NewCount);
	if (IsValid(HoverItemWidget)) HoverItemWidget->UpdateStackCount(HeldCount);

	OnHeldItemChanged.Broadcast();
}

void UTINV_HeldItemSubsystem::ClearHeld()
{
	if (bIsDragging) EndDrag();
	const bool bWasHolding = IsHolding();

	HeldItem.Reset();
	HeldCount = 0;
	SourceGrid.Reset();
	SourceIndex = INDEX_NONE;

	HideWidget();
	if (bWasHolding) OnHeldItemChanged.Broadcast();
}

void UTINV_HeldItemSubsystem::RefreshCursor()
{
	if (IsHolding() && IsValid(HoverItemWidget))
	{
		if (const UTINV_InventoryGrid* Grid = SourceGrid.Get())
		{
			HoverItemWidget->SetDisplaySize(Grid->GetTileSize() * UWidgetLayoutLibrary::GetViewportScale(Grid));
		}
		HoverItemWidget->ForceLayoutPrepass();
	}

	if (!FSlateApplication::IsInitialized()) return;
	FSlateApplication& Slate = FSlateApplication::Get();
	Slate.QueryCursor();                      // Re-resolve which cursor widget to draw.
	Slate.SetCursorPos(Slate.GetCursorPos()); // Fake a move so hover and cursor both refresh.
}

APlayerController* UTINV_HeldItemSubsystem::GetPlayerController() const
{
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	return LocalPlayer ? LocalPlayer->GetPlayerController(LocalPlayer->GetWorld()) : nullptr;
}

UTINV_HoverItem* UTINV_HeldItemSubsystem::GetOrCreateWidget(const UTINV_InventoryGrid* VisualSource)
{
	if (IsValid(HoverItemWidget)) return HoverItemWidget;

	APlayerController* PC = GetPlayerController();
	if (!PC || !VisualSource || !VisualSource->GetHoverItemClass()) return nullptr;

	HoverItemWidget = CreateWidget<UTINV_HoverItem>(PC, VisualSource->GetHoverItemClass());
	return HoverItemWidget;
}

void UTINV_HeldItemSubsystem::ShowWidget(const UTINV_InventoryGrid* VisualSource)
{
	UTINV_HoverItem* Widget = GetOrCreateWidget(VisualSource);
	APlayerController* PC = GetPlayerController();
	if (!Widget || !PC || !VisualSource) return;

	UTINV_InventoryItem* Item = HeldItem.Get();

	Widget->SetVisibility(ESlateVisibility::HitTestInvisible);
	Widget->SetInventoryItem(Item);
	Widget->UpdateStackCount(HeldCount);

	UTINV_GlintedIcon* GlintedIcon = Widget->GetGlintedIcon();
	GlintedIcon->SetItemDataTable(VisualSource->GetItemDataTable());
	GlintedIcon->SetFromInventoryItem(Item);

	Widget->SetDisplaySize(VisualSource->GetTileSize() * UWidgetLayoutLibrary::GetViewportScale(VisualSource));
	PC->SetMouseCursorWidget(EMouseCursor::Default, Widget);
}

void UTINV_HeldItemSubsystem::HideWidget()
{
	if (IsValid(HoverItemWidget))
	{
		// Emptied and collapsed as well, so it can never linger on the cursor.
		HoverItemWidget->SetInventoryItem(nullptr);
		HoverItemWidget->UpdateStackCount(0);
		HoverItemWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (APlayerController* PC = GetPlayerController())
	{
		PC->SetMouseCursorWidget(EMouseCursor::Default, nullptr);
	}
}

void UTINV_HeldItemSubsystem::BeginDrag()
{
	bIsDragging = true;
	DragSourceCount = HeldCount;
	DragTargets.Reset();
}

void UTINV_HeldItemSubsystem::AddDragTarget(UTINV_InventoryGrid* Grid, const int32 Index)
{
	DragTargets.Add({ Grid, Index });
}

int32 UTINV_HeldItemSubsystem::GetDragShare() const
{
	return DragTargets.IsEmpty() ? 0 : DragSourceCount / DragTargets.Num();
}

void UTINV_HeldItemSubsystem::UpdateDragPreview()
{
	if (!bIsDragging || DragTargets.IsEmpty()) return;

	const int32 Share = GetDragShare();
	int32 Placed = 0;
	for (const FDragTarget& Target : DragTargets)
	{
		if (UTINV_InventoryGrid* Grid = Target.Grid.Get())
		{
			Placed += Grid->PreviewDragSlot(Target.Index, Share);
		}
	}
	SetHeldCount(DragSourceCount - Placed);
}

void UTINV_HeldItemSubsystem::CommitDrag()
{
	if (!bIsDragging) return;

	UTINV_InventoryItem* Item = HeldItem.Get();
	const int32 Share = GetDragShare();

	// Work out every placement before the grids clear their previews.
	struct FPlacement { TWeakObjectPtr<UTINV_InventoryGrid> Grid; int32 Index; int32 Amount; };
	TArray<FPlacement> Placements;
	int32 Placed = 0;
	for (const FDragTarget& Target : DragTargets)
	{
		if (UTINV_InventoryGrid* Grid = Target.Grid.Get())
		{
			const int32 Amount = Grid->GetDragAmount(Target.Index, Share);
			Placements.Add({ Grid, Target.Index, Amount });
			Placed += Amount;
		}
	}
	const int32 Leftover = DragSourceCount - Placed;

	EndDrag(); // Existing stacks go back to their base counts first.

	for (const FPlacement& Placement : Placements)
	{
		if (UTINV_InventoryGrid* Grid = Placement.Grid.Get())
		{
			Grid->CommitDragSlot(Placement.Index, Item, Placement.Amount);
		}
	}

	if (Leftover > 0) SetHeldCount(Leftover);
	else ClearHeld();
}

void UTINV_HeldItemSubsystem::CancelDrag()
{
	if (!bIsDragging) return;
	const int32 Original = DragSourceCount;
	EndDrag();
	SetHeldCount(Original);
}

void UTINV_HeldItemSubsystem::EndDrag()
{
	TSet<UTINV_InventoryGrid*> Grids;
	for (const FDragTarget& Target : DragTargets)
	{
		if (UTINV_InventoryGrid* Grid = Target.Grid.Get()) Grids.Add(Grid);
	}

	bIsDragging = false;
	DragSourceCount = 0;
	DragTargets.Reset();

	for (UTINV_InventoryGrid* Grid : Grids) Grid->ClearDragState();
}
#pragma endregion
/*-------------------------------------------------------------------------*/