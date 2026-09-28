// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Widgets/Inventory/InventoryBase/TINV_InventoryBase.h"
#include "TINV_SpatialInventory.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTINV_InventoryGrid;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_SpatialInventory.h_Class
UCLASS()
class TECHYINV_API UTINV_SpatialInventory : public UTINV_InventoryBase
{
	GENERATED_BODY()

public:
	virtual FTINV_SlotAvailabilityResult HasRoomForItem(UTINV_ItemComponent* ItemComponent) const override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTINV_InventoryGrid> InventoryGrid;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTINV_InventoryGrid> InventoryHotbar;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
