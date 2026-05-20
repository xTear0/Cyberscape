// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Inv_Leaf.h"
#include "Inv_Leaf_LabeledValue.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Delcarations	                                                       */
/*-------------------------------------------------------------------------*/
class UTextBlock;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_Leaf_LabledValue.h_Class
UCLASS()
class INVENTORY_API UInv_Leaf_LabeledValue : public UInv_Leaf
{
	GENERATED_BODY()
public:
	void SetText_Label(const FText& Text, bool bCollapse) const;
	void SetText_Value(const  FText& Text, bool bCollapse) const;
	void SetText_LabelColorAs(const FLinearColor Color) const;
	void SetText_ValueColorAs(const FLinearColor Color) const;
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Inventory|Widgets")
	FText GetTextValue();

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