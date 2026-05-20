// Copyright xTear
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_EnumTypes.h"
#include "Inv_InventoryBase.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UInv_ItemComponent;
class UInv_InventoryItem;
class UInv_HoverItem;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_InventoryBase.h_Class
UCLASS()
class INVENTORY_API UInv_InventoryBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual FInv_SlotAvailabilityResult HasRoomForItem(UInv_ItemComponent* ItemComponent) const { return FInv_SlotAvailabilityResult(); }
	virtual void OnItemHovered(UInv_InventoryItem* Item) {}
	virtual void OnItemUnhovered() {}
	virtual bool HasHoverItem() const {return false;}
	virtual UInv_HoverItem* GetHoverItem() const {return nullptr;}
	virtual float GetTileSize() const {return 0;}
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/
