// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Texts/CUI_TieredItemNameText.h"
#include "Components/TextBlock.h"
#include "Core/CUI_StyleAsset.h"
#include "Misc/Icons/CUI_TieredItemIcon.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region CUI_TieredItemNameText.cpp_Functions
void UCUI_TieredItemNameText::NativePreConstruct()
{
    Super::NativePreConstruct();

#if WITH_EDITORONLY_DATA
    if (IsDesignTime())
    {
        CurrentName = PreviewName;
        CurrentTier = PreviewTier;
    }
#endif

    // At runtime this re-applies whatever was set before the widget was (re)constructed.
    ApplyName();
    ApplyColor();
}

void UCUI_TieredItemNameText::SetItemNameAndTier(const FText& ItemName, ECUI_ItemTier Tier)
{
    CurrentName = ItemName;
    CurrentTier = Tier;
    ApplyName();
    ApplyColor();
}

void UCUI_TieredItemNameText::ApplyName()
{
    if (TextBox_ItemName)
    {
        TextBox_ItemName->SetText(CurrentName);
    }
}

void UCUI_TieredItemNameText::ApplyColor()
{
    // No style asset assigned: leave whatever the designer set.
    if (!IsValid(StyleAsset))
    {
        return;
    }

    // Same rarity color the icon uses for its outline.
    const FString Token = UCUI_TieredItemIcon::GetTierStrokeColorToken(CurrentTier);
    const FString& Resolved = Token.IsEmpty() ? FallbackToken : Token;
    if (Resolved.IsEmpty())
    {
        return;
    }

    const FSlateColor Color(StyleAsset->GetColorByName(Resolved));

    ApplyColorTo(TextBox_Bracket1, Color);
    ApplyColorTo(TextBox_ItemName, Color);
    ApplyColorTo(TextBox_Bracket2, Color);
}

void UCUI_TieredItemNameText::ApplyColorTo(UTextBlock* Target, const FSlateColor& Color) const
{
    if (Target)
    {
        Target->SetColorAndOpacity(Color);
    }
}

TArray<FString> UCUI_TieredItemNameText::GetColorTokenOptions() const
{
    return IsValid(StyleAsset) ? StyleAsset->GetActiveColorNames() : TArray<FString>{};
}
#pragma endregion
/*-------------------------------------------------------------------------*/