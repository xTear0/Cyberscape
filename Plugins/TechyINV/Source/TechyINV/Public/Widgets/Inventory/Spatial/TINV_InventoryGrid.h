// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TINV_InventoryGrid.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCanvasPanel;
class UTINV_GridSlot;
class UTINV_InventoryComponent;
class UTINV_InventoryItem;
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

	UFUNCTION()
	void AddItem(UTINV_InventoryItem* Item);

protected:

private:

	TWeakObjectPtr<UTINV_InventoryComponent> InventoryComponent;
	
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
