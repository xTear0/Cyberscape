// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TINV_InventoryGrid.generated.h"
/*-------------------------------------------------------------------------*/


class UCanvasPanel;
/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTINV_GridSlot;
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


protected:

private:

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
