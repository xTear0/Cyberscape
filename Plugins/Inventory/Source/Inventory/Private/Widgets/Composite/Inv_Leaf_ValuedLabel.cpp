// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Composite/Inv_Leaf_ValuedLabel.h"
#include "Components/TextBlock.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_Leaf_ValuedLabel.cpp_Functions
void UInv_Leaf_ValuedLabel::SetAttributeValueAndTextWithColor(
	const FText& AttributeValue,
	const FText& AttributeText,
	const FLinearColor Color) const
{
	Text_Value->SetText(AttributeValue);
	Text_Value->SetColorAndOpacity(Color);
	Text_Label->SetText(AttributeText);
	Text_Label->SetColorAndOpacity(Color);
}

void UInv_Leaf_ValuedLabel::NativePreConstruct()
{
	Super::NativePreConstruct();

	FSlateFontInfo FontInfo_Label = Text_Label->GetFont();
	FontInfo_Label.Size = FontSize_Label;
	Text_Label->SetFont(FontInfo_Label);

	FSlateFontInfo FontInfo_Value = Text_Value->GetFont();
	FontInfo_Value.Size = FontSize_Value;
	Text_Value->SetFont(FontInfo_Value);
}
#pragma endregion
/*-------------------------------------------------------------------------*/

