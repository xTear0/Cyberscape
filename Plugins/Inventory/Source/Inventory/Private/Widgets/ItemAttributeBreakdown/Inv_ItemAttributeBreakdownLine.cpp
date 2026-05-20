// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/ItemAttributeBreakdown/Inv_ItemAttributeBreakdownLine.h"
#include "Components/TextBlock.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemAttributeBreakdownLine.cpp_Functions
void UInv_ItemAttributeBreakdownLine::SetLineData(
        const FText& AttributeText,
        const FLinearColor& AttributeColor,
        const FText& ValueText,
        const FLinearColor& ValueColor) const
{
    if (ItemText)
    {
        ItemText->SetText(AttributeText);
        ItemText->SetColorAndOpacity(FSlateColor(AttributeColor));
    }

    if (ItemValue)
    {
        ItemValue->SetText(ValueText);
        ItemValue->SetColorAndOpacity(FSlateColor(ValueColor));
    }
}
#pragma endregion
/*-------------------------------------------------------------------------*/