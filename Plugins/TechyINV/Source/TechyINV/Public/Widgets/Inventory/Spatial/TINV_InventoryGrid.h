// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/Manifest/TINV_ItemManifest.h"
#include "Types/TINV_StructTypes.h"
#include "TINV_InventoryGrid.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCanvasPanel;
class UTINV_GridSlot;
class UTINV_InventoryComponent;
class UTINV_InventoryItem;
class UTINV_ItemComponent;
class UTINV_ItemDataTable;
class UTINV_SlottedItem;
class UTINV_HoverItem;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryGrid.h_Class
UCLASS()
class TECHYINV_API UTINV_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	FTINV_SlotAvailabilityResult HasRoomForItem(const UTINV_ItemComponent* ItemComponent);
	
	void DropHoverItem(); // Was DropItem. For dropping what's held (e.g. clicking outside the grid).
	void CancelDrag();
	
	TSubclassOf<UTINV_HoverItem> GetHoverItemClass() const { return HoverItemClass; }
	UTINV_ItemDataTable* GetItemDataTable() const { return ItemDataTable; }
	float GetTileSize() const { return TileSize; }

	// Runs both room passes across Grids in priority order and returns one combined result.
	static FTINV_SlotAvailabilityResult HasRoomAcrossGrids(const TArray<const UTINV_InventoryGrid*>& Grids,
		const FTINV_ItemManifest& Manifest, int32 StackAmount);

	// Places only the entries of Result that belong to this grid.
	void ApplySlotAvailabilities(const FTINV_SlotAvailabilityResult& Result);

	void PostPickupNotification(const FTINV_SlotAvailabilityResult& Result, const FTINV_ItemManifest& Manifest) const;

	int32 PreviewDragSlot(int32 Index, int32 Share);   // Updates the preview; returns the amount that fits.
	int32 GetDragAmount(int32 Index, int32 Share) const;
	void CommitDragSlot(int32 Index, UTINV_InventoryItem* Item, int32 Amount);
	void ClearDragState();

	int32 GetHoveredIndex() const { return HoveredIndex; }
	bool IsValidSlot(int32 Index) const { return GridSlots.IsValidIndex(Index); }
	UTINV_InventoryItem* GetSlotItem(int32 Index) const;
	int32 GetSlotCount(int32 Index) const;
	void ClearSlot(int32 Index);
	void SetSlotContents(int32 Index, UTINV_InventoryItem* Item, int32 Count);
	void RefreshHighlight(int32 Index);
	void ResetHover();
	
protected:
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
private:
	
	/* Data */
	UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory")
	TObjectPtr<UTINV_ItemDataTable> ItemDataTable;

	TWeakObjectPtr<UTINV_InventoryComponent> InventoryComponent;

	/* Room checks */
	FTINV_SlotAvailabilityResult HasRoomForItem(const FTINV_ItemManifest& Manifest, const int32 StackAmount = 1);
	void FindRoomInExistingStacks(const FGameplayTag& ItemID, int32 MaxStackSize,
		FTINV_SlotAvailabilityResult& Result, int32& AmountToFill) const;
	void FindRoomInEmptySlots(int32 MaxStackSize,
		FTINV_SlotAvailabilityResult& Result, int32& AmountToFill) const;
	const FTINV_ItemDataDefinition* GetItemData(const FTINV_ItemManifest& ItemManifest) const;
	bool IsSlotEmpty(const UTINV_GridSlot* GridSlot) const;
	bool IsSameItem(const UTINV_GridSlot* GridSlot, const FGameplayTag& ItemID) const;
	bool IsStackable(const UTINV_InventoryItem* ItemToCheck) const;
	int32 GetRoomInSlot(const UTINV_GridSlot* GridSlot, const int32 MaxStackSize) const;
	void AddSlotAvailability(FTINV_SlotAvailabilityResult& Result, const UTINV_GridSlot* GridSlot,
		const int32 FillAmount, const bool bItemAtIndex, int32& AmountToFill) const;

	/* Placing items */
	void AddItemAtIndex(UTINV_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount);
	UTINV_SlottedItem* CreateSlottedItem(UTINV_InventoryItem* Item, int32 Index, bool bStackable, int32 StackAmount) const;
	void AddSlottedItemToCanvas(const int32 Index, UTINV_SlottedItem* SlottedItem) const;
	void UpdateGridSlots(UTINV_InventoryItem* NewItem, const int32 Index, bool bStackableItem, const int32 StackAmount);
	void RemoveItemFromGrid(UTINV_InventoryItem* InventoryItem, const int32 GridIndex);
	void SetSlotStackCount(int32 Index, int32 NewCount);
	int32 GetMaxStackSize(const UTINV_InventoryItem* Item) const;
	int32 TakeFromSlot(int32 Index, int32 Amount);

	/* Dropping items */
	UFUNCTION()
	void OnDropRequested(bool bDropAll);
	void DropFromSlot(int32 Index, bool bDropAll);
	void SendDrop(UTINV_InventoryItem* Item, int32 Amount) const;

	/* Right-click to split */
	void PickUpHalf(int32 Index);

	/* Double-click to collect */
	void CollectMatchingStacks();
	TArray<int32> GetMatchingStackIndices(const FGameplayTag& ItemID) const;
	
	/* Scroll-wheel collect and distribute */
	bool CanScrollPlace(int32 Index) const;
	bool CanScrollTake(int32 Index) const;
	void ScrollPlaceOne(int32 Index);
	void ScrollTakeOne(int32 Index);

	float ScrollAccumulator = 0.f;

	/* Grid slot input */
	UFUNCTION()
	void OnGridSlotClicked(int32 GridIndex, const FPointerEvent& MouseEvent);
	UFUNCTION()
	void OnGridSlotHovered(int32 GridIndex, const FPointerEvent& MouseEvent);
	UFUNCTION()
	void OnGridSlotUnHovered(int32 GridIndex, const FPointerEvent& MouseEvent);
	UFUNCTION()
	void OnGridSlotDoubleClicked(int32 GridIndex, const FPointerEvent& MouseEvent);

	bool IsRightClick(const FPointerEvent& MouseEvent) const;
	bool IsLeftClick(const FPointerEvent& MouseEvent) const;
	bool IsShiftClick(const FPointerEvent& MouseEvent) const;
	bool IsMiddleClick(const FPointerEvent& MouseEvent) const;

	/* Hover item */
	void PickUp(UTINV_InventoryItem* ClickedInventoryItem, const int32 GridIndex);
	void AssignHoverItem(UTINV_InventoryItem* InventoryItem, const int32 GridIndex, const int32 PreviousGridIndex);
	void ClearHoverItem();
	ETINV_DropAction GetDropAction(int32 Index) const;
	void PutDownOnIndex(int32 Index);
	void MergeStacks(int32 Index);
	void SwapWithHoverItem(int32 Index);
	void RefreshCursor() const;

	/* Held item: shared across every grid through UTINV_HeldItemSubsystem */
	class UTINV_HeldItemSubsystem* GetHeld() const;
	bool IsHolding() const;
	UTINV_InventoryItem* GetHeldItem() const;
	int32 GetHeldCount() const;
	void SetHeldCount(int32 NewCount);
	void OnHeldItemChanged();

	void ConstructGrid();

	/* State */
	UPROPERTY()
	TArray<TObjectPtr<UTINV_GridSlot>> GridSlots;

	/* Left-click drag distribute (session lives in UTINV_HeldItemSubsystem) */
	bool CanStartDrag(int32 Index, const FPointerEvent& MouseEvent) const;
	bool CanAddToDrag(int32 Index) const;
	void BeginDrag(int32 Index);
	void AddDragSlot(int32 Index);
	void AddDragPath(int32 FromIndex, int32 ToIndex);
	bool IsDragTarget(int32 Index) const;
	UTINV_SlottedItem* GetDragDisplay(int32 Index) const;
	bool IsDragging() const;

	// This grid's share of the drag visuals only.
	TArray<int32> DragIndices;
	TMap<int32, int32> DragBaseCounts;

	UPROPERTY()
	TMap<int32, TObjectPtr<UTINV_SlottedItem>> DragPreviews;
	
	UPROPERTY()
	TMap<int32, TObjectPtr<UTINV_SlottedItem>> SlottedItems;

	int32 HoveredIndex = INDEX_NONE;
	int32 LastDragIndex = INDEX_NONE;

	/* Config */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TSubclassOf<UTINV_GridSlot> GridSlotClass;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TSubclassOf<UTINV_SlottedItem> SlottedItemClass;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TSubclassOf<UTINV_HoverItem> HoverItemClass;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	int32 Rows;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	int32 Columns;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	float TileSize;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
