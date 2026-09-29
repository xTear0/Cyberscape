// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/TINV_StructTypes.h"
#include "TINV_InventoryBase.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTINV_ItemComponent;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryBase.h_Class
UCLASS

()
class TECHYINV_API UTINV_InventoryBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual FTINV_SlotAvailabilityResult HasRoomForItem(
		UTINV_ItemComponent* ItemComponent) const { return FTINV_SlotAvailabilityResult(); }

	// Default: show or hide the whole widget. Subclasses can keep parts visible.
	virtual void SetMenuOpen(bool bOpen, bool bInstant = false)
	{
		SetVisibility(bOpen ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
	
protected:

private:
};
#pragma endregion
/*-------------------------------------------------------------------------*/
