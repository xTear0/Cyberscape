// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Core/SYS7_ColorServiceComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Core/SYS7_StyleAsset.h"
#include "Core/SYS7_Widget.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_ColorServiceComponent.cpp_Functions
void USYS7_ColorServiceComponent::OnPreConstruct(bool bIsDesignTime)
{
    Super::OnPreConstruct(bIsDesignTime);

    if (ColorToken.IsEmpty()) return;
    if (!IsValid(StyleAsset)) return;

    const FLinearColor Color = GetColor();

    UWidget* ComponentOwner = GetOwner().Get();
    if (!IsValid(ComponentOwner)) return;

    if (UTextBlock* TextBlock = Cast<UTextBlock>(ComponentOwner))
    {
        TextBlock->SetColorAndOpacity(Color);
    }
    else if (UImage* Image = Cast<UImage>(ComponentOwner))
    {
        Image->SetColorAndOpacity(Color);
    }
    else if (UUserWidget* UserWidget = Cast<UUserWidget>(ComponentOwner))
    {
        UserWidget->SetColorAndOpacity(Color);
    }
    else if (UBorder* Border = Cast<UBorder>(ComponentOwner))
    {
        Border->SetContentColorAndOpacity(Color);
    }
    else if (UEditableTextBox* EditableTextBox = Cast<UEditableTextBox>(ComponentOwner))
    {
        // FEditableTextBoxStyle TextBoxStyle = EditableTextBox->WidgetStyle;
        // TextBoxStyle.TextStyle.ColorAndOpacity = Color;
        // EditableTextBox->SetWidgetStyle(TextBoxStyle);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ColorServiceComponent: unsupported owner type '%s' — cannot apply color override."),
            *ComponentOwner->GetClass()->GetName());
    }
}

FLinearColor USYS7_ColorServiceComponent::GetColor() const
{
    if (!IsValid(StyleAsset) || ColorToken.IsEmpty())
        return FLinearColor::White;

    return StyleAsset->GetColorByName(ColorToken);
}

TArray<FString> USYS7_ColorServiceComponent::GetColorNames() const
{
    if (!IsValid(StyleAsset))
        return {};

    return StyleAsset->GetActiveColorNames();
}
#pragma endregion
/*-------------------------------------------------------------------------*/