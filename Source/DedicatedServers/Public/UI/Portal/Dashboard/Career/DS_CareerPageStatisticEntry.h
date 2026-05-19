// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_CareerPageStatisticEntry.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_CareerPageStatisticEntry.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_CareerPageStatisticEntry : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetStatisticText(const FString& StatisticName, int32 StatisticValue);

	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_StatisticName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_StatisticValue;
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/