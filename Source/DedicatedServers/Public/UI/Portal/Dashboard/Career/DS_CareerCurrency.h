// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_CareerCurrency.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_CareerCurrency.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_CareerCurrency : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlock_Credits;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlock_Platinum;

	
};
#pragma endregion
/*-------------------------------------------------------------------------*/