// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Texts/CUI_EditableTextBox.h"
#include "Styling/CoreStyle.h"
#include "Components/EditableTextBox.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_EditableTextBox.cpp_Functions
void UCUI_EditableTextBox::SetEditableTextHint(const FText& Text) const
{
	UE_EditableTextBox->SetHintText(Text);
}

void UCUI_EditableTextBox::SetText(const FText& Text) const
{
	UE_EditableTextBox->SetText(Text);
}

FText UCUI_EditableTextBox::GetText() const
{
	return UE_EditableTextBox->GetText();
}

void UCUI_EditableTextBox::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(UE_EditableTextBox))
	{
		SetEditableTextHint(HintText);
		UE_EditableTextBox->SetIsPassword(bIsPassword);
	}
}

void UCUI_EditableTextBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(UE_EditableTextBox))
	{
		UE_EditableTextBox->OnTextChanged.AddDynamic(this, &UCUI_EditableTextBox::HandleTextChanged);
	}
}

void UCUI_EditableTextBox::NativeDestruct()
{
	if (IsValid(UE_EditableTextBox))
	{
		UE_EditableTextBox->OnTextChanged.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void UCUI_EditableTextBox::HandleTextChanged(const FText& Text)
{
	OnTextChanged.Broadcast(Text);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
