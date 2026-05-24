// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/SignIn/DS_SignUpPageConfirmation.h"
#include "Buttons/CUI_Button_Wide.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Texts/CUI_EditableTextBox.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_SignUpPageConfirmation.cpp_Functions
void UDS_SignUpPageConfirmation::ClearTextBoxes() const
{
	TextBox_StatusMessage->SetText(FText::GetEmpty());
	TextBox_Destination->SetText(FText::GetEmpty());
	TextBox_ConfirmationCode->SetText(FText::GetEmpty());
}

void UDS_SignUpPageConfirmation::UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets, EDS_DelegateResponse DelegateResponse)
{
	TextBox_StatusMessage->SetText(FText::FromString(Message));
	if (bShouldResetWidgets)
	{
		Button_Confirm->SetIsEnabled(true);
	}
}

void UDS_SignUpPageConfirmation::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Confirm->SetIsEnabled(false);
	TextBox_ConfirmationCode->OnTextChanged.AddDynamic(this, &UDS_SignUpPageConfirmation::UpdateConfirmButtonState);
}

void UDS_SignUpPageConfirmation::UpdateConfirmButtonState(const FText& Text)
{
	const FRegexPattern SixDigitsPattern(TEXT(R"(^\d{6}$)"));	
	FRegexMatcher Matcher(SixDigitsPattern, Text.ToString());

	const bool bValidConfirmationCode = Matcher.FindNext();
	Button_Confirm->SetIsEnabled(bValidConfirmationCode);
	if (bValidConfirmationCode)
	{
		TextBox_StatusMessage->SetText(FText::GetEmpty());
	}
	else
	{
		TextBox_StatusMessage->SetText(FText::FromString("Please enter six numerical digits."));
	}
}

#pragma endregion
/*-------------------------------------------------------------------------*/