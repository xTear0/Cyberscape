// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Buttons/CUI_Button_Wide.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Button_Wide.cpp_Functions

void UCUI_Button_Wide::NativeConstruct()
{
    Super::NativeConstruct();

}

void UCUI_Button_Wide::NativeDestruct()
{

    Super::NativeDestruct();
}

void UCUI_Button_Wide::SetTextContent() const
{
    if (IsValid(TextBlock_Button))
    {
        TextBlock_Button->SetText(TextContent);
        FSlateFontInfo SlateFontInfo = TextBlock_Button->GetFont();
        SlateFontInfo.Size = TextSize;
        TextBlock_Button->SetFont(SlateFontInfo);
    }
}

void UCUI_Button_Wide::NativePreConstruct()
{
    Super::NativePreConstruct();

    SetTextContent();
}

void UCUI_Button_Wide::SetIsButtonEnabled(bool bInIsEnabled)
{
    if (IsValid(UE_Button))
    {
        UE_Button->SetIsEnabled(bInIsEnabled);
        OnIsEnabled.Broadcast(bInIsEnabled);
    }
}

bool UCUI_Button_Wide::GetIsButtonEnabled() const
{
    return UE_Button ? UE_Button->GetIsEnabled() : false;
}

void UCUI_Button_Wide::SetText(const FText& InText) const
{
    if (IsValid(TextBlock_Button))
    {
        TextBlock_Button->SetText(InText);
    }
    UE_LOG(LogCUI, Warning, TEXT("[CUI] Optional TextBlock_Button is not valid, no text will be set."));
}

FText UCUI_Button_Wide::GetText() const
{
    if (IsValid(TextBlock_Button))
    {
        return TextBlock_Button->GetText();
    }
    UE_LOG(LogCUI, Warning, TEXT("[CUI] Optional TextBlock_Button is not valid, no text will be returned."));
    return FText();
}

void UCUI_Button_Wide::PlayTransitionAnimation(bool Reverse)
{
    if (!Reverse)
    {
        if (Anim_Transition)
        {
            PlayAnimation(Anim_Transition);
        }
        if (Anim_Enabled)
        {
            PlayAnimation(Anim_Enabled);
        }
    } else
    {
        if (Anim_Transition)
        {
            // Play Animation in reverse
            PlayAnimation(Anim_Transition, 0, 1, EUMGSequencePlayMode::Reverse, 1, false);
        }
        if (Anim_Enabled)
        {
            PlayAnimation(Anim_Enabled);
        }
    }
}

void UCUI_Button_Wide::ClearAnimations()
{
    StopAllAnimations();
}
#pragma endregion
/*-------------------------------------------------------------------------*/
