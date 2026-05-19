// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_CareerXPBar.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UProgressBar;
class UTextBlock;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_CareerXPBar.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_CareerXPBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget)) UProgressBar* ProgressBar_XP;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlock_XP;

	
};
#pragma endregion
/*-------------------------------------------------------------------------*/