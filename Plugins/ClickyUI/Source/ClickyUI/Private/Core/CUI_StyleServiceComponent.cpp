// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Core/CUI_StyleServiceComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Core/CUI_StyleAsset.h"
#include "Core/CUI_Widget.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_StyleServiceComponent.cpp_Functions
void UCUI_StyleServiceComponent::OnPreConstruct(bool bIsDesignTime)
{
    Super::OnPreConstruct(bIsDesignTime);

    if (!IsValid(StyleAsset)) return;

    UWidget* ComponentOwner = GetOwner().Get();
    if (!IsValid(ComponentOwner)) return;

    const FLinearColor Color = GetColor();
    const bool bHasColor      = !ColorToken.IsEmpty();
    const bool bHasFontFamily = !FontFamilyToken.IsEmpty();

    if (UTextBlock* TextBlock = Cast<UTextBlock>(ComponentOwner))
    {
        if (bHasColor) TextBlock->SetColorAndOpacity(Color);

        if (bHasFontFamily)
        {
            const FSlateFontInfo Font = BuildFont();
            if (Font.HasValidFont())
            {
                TextBlock->SetFont(Font);
            }
        }
    }
    else if (UImage* Image = Cast<UImage>(ComponentOwner))
    {
        if (bHasColor) Image->SetColorAndOpacity(Color);
    }
    else if (UButton* Button = Cast<UButton>(ComponentOwner))
    {
        if (bHasColor) Button->SetColorAndOpacity(Color);

        FButtonStyle Style = Button->GetStyle();
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

    // Warn if font family was set on a non-text owner
    if (!Cast<UTextBlock>(ComponentOwner) && bHasFontFamily)
    {
        UE_LOG(LogTemp, Warning, TEXT("StyleServiceComponent: font family is set on '%s' but owner '%s' is not a UTextBlock — font will be ignored."),
            *GetName(), *ComponentOwner->GetClass()->GetName());
    }
}

FLinearColor UCUI_StyleServiceComponent::GetColor() const
{
    if (!IsValid(StyleAsset) || ColorToken.IsEmpty())
        return FLinearColor::White;

    return StyleAsset->GetColorByName(ColorToken);
}

FSlateSound UCUI_StyleServiceComponent::GetSound(const FString& Token) const
{
    if (!IsValid(StyleAsset) || Token.IsEmpty())
        return FSlateSound();

    return StyleAsset->GetSoundByName(Token);
}

FSlateFontInfo UCUI_StyleServiceComponent::BuildFont() const
{
    FSlateFontInfo Font;

    if (!IsValid(StyleAsset) || FontFamilyToken.IsEmpty())
        return Font;

    const FCUI_FontFamily Family = StyleAsset->GetFontFamilyByName(FontFamilyToken);
    if (Family.FontObject == nullptr)
        return Font;

    Font.FontObject       = Family.FontObject;
    Font.TypefaceFontName = Family.Typeface;
    Font.Size             = FontSizeOverride > 0.0f ? FontSizeOverride : Family.DefaultSize;
    return Font;
}

TArray<FString> UCUI_StyleServiceComponent::GetColorNames() const
{
    if (!IsValid(StyleAsset))
        return {};

    return StyleAsset->GetActiveColorNames();
}

TArray<FString> UCUI_StyleServiceComponent::GetSoundNames() const
{
    if (!IsValid(StyleAsset))
        return {};

    return StyleAsset->GetActiveSoundNames();
}

TArray<FString> UCUI_StyleServiceComponent::GetFontFamilyNames() const
{
    if (!IsValid(StyleAsset))
        return {};

    return StyleAsset->GetActiveFontFamilyNames();
}

#pragma endregion
/*-------------------------------------------------------------------------*/
