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
	FTINV_SlotAvailabilityResult HasRoomForItem(const FTINV_ItemManifest& Manifest);
	void AddItemToIndicies(const FTINV_SlotAvailabilityResult& Result, UTINV_InventoryItem* NewItem);
	
	
	void ConstructGrid();

	UPROPERTY()
	TArray<TObjectPtr<UTINV_GridSlot>> GridSlots;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TSubclassOf<UTINV_GridSlot> GridSlotClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	int32 Rows;
	
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	int32 Columns;
	
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	float TileSize;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
