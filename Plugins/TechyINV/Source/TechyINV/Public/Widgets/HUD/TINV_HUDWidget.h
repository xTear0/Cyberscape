// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
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
class UCUI_TextStatusNotification;

UCLASS()
class TECHYINV_API UTINV_HUDWidget : public UCUI_Widget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "TECHY|Inventory")
	void ShowPickupMessagePrompt(const FString& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = "TECHY|Inventory")
	void HidePickupMessagePrompt();
protected:

private:

};
#pragma endregion
/*-------------------------------------------------------------------------*/
