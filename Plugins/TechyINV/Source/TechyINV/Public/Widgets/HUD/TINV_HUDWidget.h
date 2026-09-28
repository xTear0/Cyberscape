// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Core/CUI_Widget.h"
#include "Types/TINV_StructTypes.h"
#include "TINV_HUDWidget.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_HUDWidget.h_Class
UCLASS()
class TECHYINV_API UTINV_HUDWidget : public UCUI_Widget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "TECHY|Inventory")
	void ShowPickupMessagePrompt(const FTINV_ItemDataDefinition& ItemData, const FText& ItemType, const int32 StackCount);

	UFUNCTION(BlueprintImplementableEvent, Category = "TECHY|Inventory")
	void PressedPickupMessagePrompt();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "TECHY|Inventory")
	void HidePickupMessagePrompt();
protected:

private:

};
#pragma endregion
/*-------------------------------------------------------------------------*/
