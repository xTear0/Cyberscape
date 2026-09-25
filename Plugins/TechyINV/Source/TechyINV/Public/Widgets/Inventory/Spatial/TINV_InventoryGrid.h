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

private:
	UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory")
	TObjectPtr<UTINV_ItemDataTable> ItemDataTable;
	
	TWeakObjectPtr<UTINV_InventoryComponent> InventoryComponent;

	FTINV_SlotAvailabilityResult HasRoomForItem(const UTINV_InventoryItem* Item);
	void AddItemToIndicies(const FTINV_SlotAvailabilityResult& Result, UTINV_InventoryItem* NewItem);
	void AddItemAtIndex(UTINV_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount);
	void AddSlottedItemToCanvas(const int32 Index, UTINV_SlottedItem* SlottedItem) const;
	void UpdateGridSlots(UTINV_InventoryItem* NewItem, const int32 Index, bool bStackableItem, const int32 StackAmount);
	bool IsIndexClaimed(const TSet<int32>& CheckedIndicies, const int32 Index) const;
	FTINV_SlotAvailabilityResult HasRoomForItem(const FTINV_ItemManifest& Manifest, const int32 StackAmount = 1);
	const FTINV_ItemDataDefinition* GetItemData(const FTINV_ItemManifest& ItemManifest) const;
	bool IsSlotEmpty(const UTINV_GridSlot* GridSlot) const;
	bool IsSameItem(const UTINV_GridSlot* GridSlot, const FGameplayTag& ItemID) const;
	int32 GetRoomInSlot(const UTINV_GridSlot* GridSlot, const int32 MaxStackSize) const;
	void AddSlotAvailability(FTINV_SlotAvailabilityResult& Result, const UTINV_GridSlot* GridSlot,
		const int32 FillAmount, const bool bItemAtIndex, int32& AmountToFill) const;
	
	void ConstructGrid();

	UPROPERTY()
	TArray<TObjectPtr<UTINV_GridSlot>> GridSlots;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TSubclassOf<UTINV_GridSlot> GridSlotClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TSubclassOf<UTINV_SlottedItem> SlottedItemClass;

	UPROPERTY()
	TMap<int32, TObjectPtr<UTINV_SlottedItem>> SlottedItems;
	
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	int32 Rows;
	
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	int32 Columns;
	
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	float TileSize;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
