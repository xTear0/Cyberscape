// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_ListFleetsBox.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UScrollBox;
class UButton;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ADS_ListFleetsBox.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_ListFleetsBox : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> ScrollBox_ListFleets;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Button_ListFleets;
};
#pragma endregion
/*-------------------------------------------------------------------------*/