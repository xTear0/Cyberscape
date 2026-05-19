// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Texts/SYS7_EditableTextBox.h"
#include "Styling/CoreStyle.h"
#include "Components/EditableTextBox.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_EditableTextBox.cpp_Functions
void USYS7_EditableTextBox::SetEditableTextHint(const FText& Text) const
{
	UE_EditableTextBox->SetHintText(Text);
}

void USYS7_EditableTextBox::SetText(const FText& Text) const
{
	UE_EditableTextBox->SetText(Text);
}

FText USYS7_EditableTextBox::GetText() const
{
	return UE_EditableTextBox->GetText();
}

void USYS7_EditableTextBox::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(UE_EditableTextBox))
	{
		SetEditableTextHint(HintText);
		UE_EditableTextBox->SetIsPassword(bIsPassword);
	}
}

void USYS7_EditableTextBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(UE_EditableTextBox))
	{
		UE_EditableTextBox->OnTextChanged.AddDynamic(this, &USYS7_EditableTextBox::HandleTextChanged);
	}
}

void USYS7_EditableTextBox::NativeDestruct()
{
	if (IsValid(UE_EditableTextBox))
	{
		UE_EditableTextBox->OnTextChanged.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void USYS7_EditableTextBox::HandleTextChanged(const FText& Text)
{
	OnTextChanged.Broadcast(Text);
}
#pragma endregion
/*-------------------------------------------------------------------------*/