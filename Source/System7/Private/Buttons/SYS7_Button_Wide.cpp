// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Buttons/SYS7_Button_Wide.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_Button_Wide.cpp_Functions

void USYS7_Button_Wide::NativeConstruct()
{
    Super::NativeConstruct();

    if (ensure(UE_Button))
    {
        UE_Button->OnClicked.AddDynamic(this,   &USYS7_Button_Wide::HandleClicked);
        UE_Button->OnPressed.AddDynamic(this,   &USYS7_Button_Wide::HandlePressed);
        UE_Button->OnReleased.AddDynamic(this,  &USYS7_Button_Wide::HandleReleased);
        UE_Button->OnHovered.AddDynamic(this,   &USYS7_Button_Wide::HandleHovered);
        UE_Button->OnUnhovered.AddDynamic(this, &USYS7_Button_Wide::HandleUnhovered);
    }
}

void USYS7_Button_Wide::NativeDestruct()
{
    if (IsValid(UE_Button))
    {
        UE_Button->OnClicked.RemoveAll(this);
        UE_Button->OnPressed.RemoveAll(this);
        UE_Button->OnReleased.RemoveAll(this);
        UE_Button->OnHovered.RemoveAll(this);
        UE_Button->OnUnhovered.RemoveAll(this);
    }

    Super::NativeDestruct();
}

void USYS7_Button_Wide::SetTextContent() const
{
    if (IsValid(TextBlock_Button))
    {
        TextBlock_Button->SetText(TextContent);
        
        FSlateFontInfo SlateFontInfo;
        SlateFontInfo.FontObject = FontObject;
        SlateFontInfo.Size = TextSize;
        TextBlock_Button->SetFont(SlateFontInfo);
    }
}

void USYS7_Button_Wide::NativePreConstruct()
{
    Super::NativePreConstruct();

    SetTextContent();
}

void USYS7_Button_Wide::SetIsButtonEnabled(bool bInIsEnabled)
{
    if (IsValid(UE_Button))
    {
        UE_Button->SetIsEnabled(bInIsEnabled);
        OnIsEnabled.Broadcast(bInIsEnabled);
    }
}

bool USYS7_Button_Wide::GetIsButtonEnabled() const
{
    return UE_Button ? UE_Button->GetIsEnabled() : false;
}

void USYS7_Button_Wide::SetText(const FText& InText) const
{
    if (IsValid(TextBlock_Button))
    {
        TextBlock_Button->SetText(InText);
    }
    UE_LOG(LogSYS7, Warning, TEXT("[SYS7] Optional TextBlock_Button is not valid, no text will be set."));
}

FText USYS7_Button_Wide::GetText() const
{
    if (IsValid(TextBlock_Button))
    {
        return TextBlock_Button->GetText();
    }
    UE_LOG(LogSYS7, Warning, TEXT("[SYS7] Optional TextBlock_Button is not valid, no text will be returned."));
    return FText();
}

void USYS7_Button_Wide::PlayTransitionAnimation(bool Reverse)
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

void USYS7_Button_Wide::ClearAnimations()
{
    StopAllAnimations();
}
#pragma endregion
/*-------------------------------------------------------------------------*/