// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_ItemAttributeBreakdownLine.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations		                                                   */
/*-------------------------------------------------------------------------*/
class UTextBlock;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemAttributeBreakdownLine.h_Class
UCLASS()
class INVENTORY_API UInv_ItemAttributeBreakdownLine : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetLineData(
		const FText& AttributeText,
		const FLinearColor& AttributeColor, 
		const FText& ValueText,
		const FLinearColor& ValueColor) const;

	
protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemValue;
};
/*-------------------------------------------------------------------------*/
