// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
UCLASS

()
class TECHYINV_API UTINV_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "TECHY|Inventory")
	void ShowPickupMessagePrompt(const FString& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = "TECHY|Inventory")
	void HidePickupMessagePrompt();
protected:

private:
};
#pragma endregion
/*-------------------------------------------------------------------------*/
