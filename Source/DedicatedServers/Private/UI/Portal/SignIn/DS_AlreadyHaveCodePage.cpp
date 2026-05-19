// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/SignIn/DS_AlreadyHaveCodePage.h"
#include "Buttons/SYS7_Button_Wide.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Texts/SYS7_EditableTextBox.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_AlreadyHaveCodePage.cpp_Functions
void UDS_AlreadyHaveCodePage::ClearTextBoxes() const
{
	TextBox_StatusMessage->SetText(FText::GetEmpty());
	TextBox_ConfirmationCode->SetText(FText::GetEmpty());
}

void UDS_AlreadyHaveCodePage::UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets, EDS_DelegateResponse DelegateResponse)
{
	TextBox_StatusMessage->SetText(FText::FromString(Message));
	if (bShouldResetWidgets)
	{
		Button_ResendCode->SetIsEnabled(true);
		Button_ConfirmCode->SetIsEnabled(true);
	}
}

void UDS_AlreadyHaveCodePage::NativeConstruct()
{
	Super::NativeConstruct();
	Button_ConfirmCode->SetIsEnabled(false);
	Button_ResendCode->SetIsEnabled(false);
	TextBox_ConfirmationCode->OnTextChanged.AddDynamic(this, &UDS_AlreadyHaveCodePage::UpdateButtonStates);
	TextBox_Username->OnTextChanged.AddDynamic(this, &UDS_AlreadyHaveCodePage::UpdateButtonStates);

}

void UDS_AlreadyHaveCodePage::UpdateButtonStates(const FText& Text)
{
	// Is there a valid username entered in the box?
	const bool bIsValidUsername = IsValidUsername();
	const bool bIsSixDigitsEntered = IsSixDigitsEntered();

	
	if (bIsValidUsername)
	{
		Button_ResendCode->SetIsEnabled(true);
	} else
	{
		Button_ResendCode->SetIsEnabled(false);
	}
	
	if (bIsSixDigitsEntered)
	{
		Button_ConfirmCode->SetIsEnabled(true);
	} else
	{
		Button_ConfirmCode->SetIsEnabled(false);
	}
}

bool UDS_AlreadyHaveCodePage::IsValidUsername()
{
	const FString Username = TextBox_Username->GetText().ToString();
	const FRegexPattern UsernamePattern(
		TEXT(R"((?i)^[A-Z0-9_]{3,16}$)")
	);

	FRegexMatcher UsernameMatcher(UsernamePattern, Username);

	if (!UsernameMatcher.FindNext())
	{
		TextBox_StatusMessage->SetText(FText::FromString(TEXT("Please enter a valid username between 3 and 16 characters.")));
		return false;
	}
	return true;
}

bool UDS_AlreadyHaveCodePage::IsSixDigitsEntered()
{
	const FRegexPattern SixDigitsPattern(TEXT(R"(^\d{6}$)"));	
	FRegexMatcher Matcher(SixDigitsPattern, TextBox_ConfirmationCode->GetText().ToString());
	const bool bValidConfirmationCode = Matcher.FindNext();
	
	if (bValidConfirmationCode)
	{
		TextBox_StatusMessage->SetText(FText::GetEmpty());
		return true;
	}
	else
	{
		TextBox_StatusMessage->SetText(FText::FromString("Please enter six numerical digits."));
		return false;
	}
}

#pragma endregion
/*-------------------------------------------------------------------------*/

