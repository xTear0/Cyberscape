// Copyright xTear Studio
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Inv_Leaf.h"
#include "Inv_Leaf_ValuedLabel.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Delcarations	                                                       */
/*-------------------------------------------------------------------------*/
class UTextBlock;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_Leaf_ValuedLabel.h_Class
UCLASS()
class INVENTORY_API UInv_Leaf_ValuedLabel : public UInv_Leaf
{
	GENERATED_BODY()
public:
	void SetAttributeValueAndTextWithColor(const FText& AttributeValue, const FText& AttributeText, const FLinearColor Color) const;
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Label;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Value;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 FontSize_Label{12};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 FontSize_Value{18};
};
#pragma endregion
/*-------------------------------------------------------------------------*/
