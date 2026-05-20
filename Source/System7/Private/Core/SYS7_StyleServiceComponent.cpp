// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Core/SYS7_StyleServiceComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Core/SYS7_StyleAsset.h"
#include "Core/SYS7_Widget.h"
#include "Sound/SoundBase.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_StyleServiceComponent.cpp_Functions
void USYS7_StyleServiceComponent::OnPreConstruct(bool bIsDesignTime)
{
    Super::OnPreConstruct(bIsDesignTime);

    if (!IsValid(StyleAsset)) return;

    UWidget* ComponentOwner = GetOwner().Get();
    if (!IsValid(ComponentOwner)) return;

    const FLinearColor Color = GetColor();
    const bool bHasColor = !ColorToken.IsEmpty();

    if (UTextBlock* TextBlock = Cast<UTextBlock>(ComponentOwner))
    {
        if (bHasColor) TextBlock->SetColorAndOpacity(Color);
    }
    else if (UImage* Image = Cast<UImage>(ComponentOwner))
    {
        if (bHasColor) Image->SetColorAndOpacity(Color);
    }
    else if (UButton* Button = Cast<UButton>(ComponentOwner))
    {
        if (bHasColor) Button->SetColorAndOpacity(Color);

        FButtonStyle Style = Button->WidgetStyle;
        bool bStyleChanged = false;

        if (!PressedSoundToken.IsEmpty())
        {
            Style.PressedSlateSound = GetSound(PressedSoundToken);
            bStyleChanged = true;
        }
        if (!HoverSoundToken.IsEmpty())
        {
            Style.HoveredSlateSound = GetSound(HoverSoundToken);
            bStyleChanged = true;
        }

        if (bStyleChanged)
        {
            Button->SetStyle(Style);
        }
    }
    else if (UBorder* Border = Cast<UBorder>(ComponentOwner))
    {
        if (bHasColor) Border->SetContentColorAndOpacity(Color);
    }
    else if (UUserWidget* UserWidget = Cast<UUserWidget>(ComponentOwner))
    {
        if (bHasColor) UserWidget->SetColorAndOpacity(Color);
    }
    else if (UEditableTextBox* EditableTextBox = Cast<UEditableTextBox>(ComponentOwner))
    {
        // FEditableTextBoxStyle TextBoxStyle = EditableTextBox->WidgetStyle;
        // TextBoxStyle.TextStyle.ColorAndOpacity = Color;
        // EditableTextBox->SetWidgetStyle(TextBoxStyle);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("StyleServiceComponent: unsupported owner type '%s' — cannot apply style override."),
            *ComponentOwner->GetClass()->GetName());
    }

    // Warn if sound tokens were set on a non-button owner
    if (!Cast<UButton>(ComponentOwner) && (!PressedSoundToken.IsEmpty() || !HoverSoundToken.IsEmpty()))
    {
        UE_LOG(LogTemp, Warning, TEXT("StyleServiceComponent: sound tokens are set on '%s' but owner '%s' is not a UButton — sounds will be ignored."),
            *GetName(), *ComponentOwner->GetClass()->GetName());
    }
}

FLinearColor USYS7_StyleServiceComponent::GetColor() const
{
    if (!IsValid(StyleAsset) || ColorToken.IsEmpty())
        return FLinearColor::White;

    return StyleAsset->GetColorByName(ColorToken);
}

FSlateSound USYS7_StyleServiceComponent::GetSound(const FString& Token) const
{
    FSlateSound Sound;
    if (!IsValid(StyleAsset) || Token.IsEmpty())
        return Sound;

    if (USoundBase* SoundBase = StyleAsset->GetSoundByName(Token))
    {
        Sound.SetResourceObject(SoundBase);
    }
    return Sound;
}

TArray<FString> USYS7_StyleServiceComponent::GetColorNames() const
{
    if (!IsValid(StyleAsset))
        return {};

    return StyleAsset->GetActiveColorNames();
}

TArray<FString> USYS7_StyleServiceComponent::GetSoundNames() const
{
    if (!IsValid(StyleAsset))
        return {};

    return StyleAsset->GetActiveSoundNames();
}
#pragma endregion
/*-------------------------------------------------------------------------*/