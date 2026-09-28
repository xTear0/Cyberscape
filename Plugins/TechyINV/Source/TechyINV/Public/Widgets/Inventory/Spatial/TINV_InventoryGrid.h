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

	UFUNCTION()
	void AddItem(UTINV_InventoryItem* Item);
	void CancelDrag();

protected:
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
private:
	/* Data */
	UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory")
	TObjectPtr<UTINV_ItemDataTable> ItemDataTable;

	TWeakObjectPtr<UTINV_InventoryComponent> InventoryComponent;

	/* Room checks */
	FTINV_SlotAvailabilityResult HasRoomForItem(const UTINV_InventoryItem* Item);
	FTINV_SlotAvailabilityResult HasRoomForItem(const FTINV_ItemManifest& Manifest, const int32 StackAmount = 1);
	const FTINV_ItemDataDefinition* GetItemData(const FTINV_ItemManifest& ItemManifest) const;
	bool IsSlotEmpty(const UTINV_GridSlot* GridSlot) const;
	bool IsSameItem(const UTINV_GridSlot* GridSlot, const FGameplayTag& ItemID) const;
	bool IsStackable(const UTINV_InventoryItem* ItemToCheck) const;
	int32 GetRoomInSlot(const UTINV_GridSlot* GridSlot, const int32 MaxStackSize) const;
	void AddSlotAvailability(FTINV_SlotAvailabilityResult& Result, const UTINV_GridSlot* GridSlot,
		const int32 FillAmount, const bool bItemAtIndex, int32& AmountToFill) const;

	/* Placing items */
	void AddItemToIndices(const FTINV_SlotAvailabilityResult& Result, UTINV_InventoryItem* NewItem);
	void AddItemAtIndex(UTINV_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount);
	UTINV_SlottedItem* CreateSlottedItem(UTINV_InventoryItem* Item, int32 Index, bool bStackable, int32 StackAmount) const;
	void AddSlottedItemToCanvas(const int32 Index, UTINV_SlottedItem* SlottedItem) const;
	void UpdateGridSlots(UTINV_InventoryItem* NewItem, const int32 Index, bool bStackableItem, const int32 StackAmount);
	void RemoveItemFromGrid(UTINV_InventoryItem* InventoryItem, const int32 GridIndex);
	void SetSlotStackCount(int32 Index, int32 NewCount);
	int32 GetMaxStackSize(const UTINV_InventoryItem* Item) const;
	int32 TakeFromSlot(int32 Index, int32 Amount);

	/* Right-click to split */
	void PickUpHalf(int32 Index);

	/* Double-click to collect */
	void CollectMatchingStacks();
	TArray<int32> GetMatchingStackIndices(const FGameplayTag& ItemID) const;

	/* Left-click drag distribute */
	bool CanStartDrag(int32 Index, const FPointerEvent& MouseEvent) const;
	bool CanAddToDrag(int32 Index) const;
	void BeginDrag(int32 Index);
	void AddDragSlot(int32 Index);
	void AddDragPath(int32 FromIndex, int32 ToIndex);
	bool IsDragTarget(int32 Index) const;
	int32 GetDragAmount(int32 Index, int32 Share) const;
	UTINV_SlottedItem* GetDragDisplay(int32 Index) const;
	TMap<int32, int32> DragBaseCounts;
	
	/* Scroll-wheel collect and distribute */
	bool CanScrollPlace(int32 Index) const;
	bool CanScrollTake(int32 Index) const;
	void ScrollPlaceOne(int32 Index);
	void ScrollTakeOne(int32 Index);

	float ScrollAccumulator = 0.f;

	void UpdateDragPreview();
	void CommitDrag();
	void ClearDragState();

	bool bIsDragging = false;
	int32 DragSourceCount = 0;
	TArray<int32> DragIndices;

	UPROPERTY()
	TMap<int32, TObjectPtr<UTINV_SlottedItem>> DragPreviews;
	
	UFUNCTION()
	void AddStacks(const FTINV_SlotAvailabilityResult& Result);

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
	void AssignHoverItem(UTINV_InventoryItem* InventoryItem);
	void AssignHoverItem(UTINV_InventoryItem* InventoryItem, const int32 GridIndex, const int32 PreviousGridIndex);
	void ClearHoverItem();
	ETINV_DropAction GetDropAction(int32 Index) const;
	void RefreshHighlight(int32 Index);
	void PutDownOnIndex(int32 Index);
	void MergeStacks(int32 Index);
	void SwapWithHoverItem(int32 Index);
	void RefreshCursor() const;

	void ConstructGrid();
	void PostPickupNotification(const FTINV_SlotAvailabilityResult& Result, const FTINV_ItemManifest& Manifest) const;

	/* State */
	UPROPERTY()
	TArray<TObjectPtr<UTINV_GridSlot>> GridSlots;

	UPROPERTY()
	TMap<int32, TObjectPtr<UTINV_SlottedItem>> SlottedItems;

	UPROPERTY()
	TObjectPtr<UTINV_HoverItem> HoverItem;

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
