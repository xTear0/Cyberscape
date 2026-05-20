// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Composite/Inv_Leaf_LabeledValue.h"
#include "Components/TextBlock.h"
/*-------------------------------------------------------------------------*/




/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_Leaf_LabledValue.cpp_Functions
void UInv_Leaf_LabeledValue::SetText_Label(const FText& Text, bool bCollapse) const
{
	if (bCollapse)
	{
		Text_Label->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	Text_Label->SetText(Text);
}

void UInv_Leaf_LabeledValue::SetText_Value(const FText& Text, bool bCollapse) const
{
	if (bCollapse)
	{
		Text_Value->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	Text_Value->SetText(Text);
}

void UInv_Leaf_LabeledValue::SetText_LabelColorAs(const FLinearColor Color) const
{
	Text_Label->SetColorAndOpacity(Color);
}

void UInv_Leaf_LabeledValue::SetText_ValueColorAs(const FLinearColor Color) const
{
	Text_Value->SetColorAndOpacity(Color);
}

void UInv_Leaf_LabeledValue::NativePreConstruct()
{
	Super::NativePreConstruct();

	FSlateFontInfo FontInfo_Label = Text_Label->GetFont();
	FontInfo_Label.Size = FontSize_Label;
	Text_Label->SetFont(FontInfo_Label);

	FSlateFontInfo FontInfo_Value = Text_Value->GetFont();
	FontInfo_Value.Size = FontSize_Value;
	Text_Value->SetFont(FontInfo_Value);
}

FText UInv_Leaf_LabeledValue::GetTextValue()
{
	return Text_Value->GetText();
}
#pragma endregion
/*-------------------------------------------------------------------------*/

