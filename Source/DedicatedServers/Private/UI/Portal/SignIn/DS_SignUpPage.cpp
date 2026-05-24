// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/SignIn/DS_SignUpPage.h"

#include "Buttons/CUI_Button_Wide.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Texts/CUI_EditableTextBox.h"
/*-------------------------------------------------------------------------*/


void UDS_SignUpPage::UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets, EDS_DelegateResponse DelegateResponse)
{
	TextBox_StatusMessage->SetText(FText::FromString(Message));
	if (bShouldResetWidgets)
	{
		Button_SignUp->SetIsEnabled(true);
	}
}

void UDS_SignUpPage::ClearTextBoxes() const
{
	TextBox_StatusMessage->SetText(FText::GetEmpty());
	TextBox_Username->SetText(FText::GetEmpty());
	TextBox_Password->SetText(FText::GetEmpty());
	TextBox_ConfirmPassword->SetText(FText::GetEmpty());
	TextBox_Email->SetText(FText::GetEmpty());
}

void UDS_SignUpPage::NativeConstruct()
{
	Super::NativeConstruct();
	Button_SignUp->SetIsEnabled(false);

	TextBox_Username->OnTextChanged.AddDynamic(this, &UDS_SignUpPage::UpdateSignUpButtonState);
	TextBox_Password->OnTextChanged.AddDynamic(this, &UDS_SignUpPage::UpdateSignUpButtonState);
	TextBox_ConfirmPassword->OnTextChanged.AddDynamic(this, &UDS_SignUpPage::UpdateSignUpButtonState);
	TextBox_Email->OnTextChanged.AddDynamic(this, &UDS_SignUpPage::UpdateSignUpButtonState);
}

void UDS_SignUpPage::UpdateSignUpButtonState(const FText& Text)
{
	/*-------------------------------------------------------------------------*/
	/* Separation of Concerns												   */
	/*-------------------------------------------------------------------------*/
	#pragma region SignUpRequirementsLogic
	// Is the Username Valid?
	const bool bIsValidUsername = IsValidUsername();
	if (!bIsValidUsername) return;
	
	// Is the Password Valid (Strong)?
	const bool bIsValidPassword = IsStrongPassword();
	if (!bIsValidPassword) return;
	
	// Are both Passwords matching?
	if (TextBox_Password->GetText().ToString() != TextBox_ConfirmPassword->GetText().ToString())
	{
		TextBox_StatusMessage->SetText(FText::FromString(TEXT("Passwords must match.")));
		return;
	}
	
	// Is the Email Valid?
	const bool bIsValidEmail = IsValidEmail();
	if (!bIsValidEmail) return;
	#pragma endregion
	/*-------------------------------------------------------------------------*/
	TextBox_StatusMessage->SetText(FText::FromString(TEXT("")));
	Button_SignUp->SetIsEnabled(true); 
}

bool UDS_SignUpPage::IsValidEmail()
{
	const FString Email = TextBox_Email->GetText().ToString();
	
	const FRegexPattern EmailPattern(
	TEXT(R"((?i)^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)")
	);

	FRegexMatcher EmailMatcher(EmailPattern, Email);
	if (!EmailMatcher.FindNext())
	{
		TextBox_StatusMessage->SetText(FText::FromString(TEXT("Please enter a valid email address.")));
		return false;
	}
	return true;
}

bool UDS_SignUpPage::IsValidUsername()
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

bool UDS_SignUpPage::IsStrongPassword()
{
	const FString Password = TextBox_Password->GetText().ToString();
	
	const FRegexPattern NumberCharPattern(TEXT(R"(\d)"));		// Contains at least one number char.
	const FRegexPattern SpecialCharPattern(TEXT(R"([!@#$%^&*()\-+=\[\]{};:'",.<>/?\\|`~])"));	// Contains at least one special char.
	const FRegexPattern UppercasePattern(TEXT(R"([A-Z])"));		// Contains at least one uppercase char.			
	const FRegexPattern LowercasePattern(TEXT(R"([a-z])"));		// Contains at least one lowercase char.
	FRegexMatcher NumberMatcher(NumberCharPattern, Password);
	FRegexMatcher SpecialCharMatcher(SpecialCharPattern, Password);
	FRegexMatcher UppercaseMatcher(UppercasePattern, Password);
	FRegexMatcher LowercaseMatcher(LowercasePattern, Password);

	if (!NumberMatcher.FindNext())
	{
		TextBox_StatusMessage->SetText(FText::FromString(TEXT("Password must contain at least one number.")));
		return false;
	}
	if (!SpecialCharMatcher.FindNext())
	{
		TextBox_StatusMessage->SetText(FText::FromString(TEXT("Password must contain at least one ASCII special character.")));
		return false;
	}
	if (!UppercaseMatcher.FindNext())
	{
		TextBox_StatusMessage->SetText(FText::FromString(TEXT("Password must contain at least one uppercase character.")));
		return false;
	}
	if (!LowercaseMatcher.FindNext())
	{
		TextBox_StatusMessage->SetText(FText::FromString(TEXT("Password must contain at least one lowercase character.")));
		return false;
	}

	if (Password.Len() < 12 || Password.Len() > 64)
	{
		TextBox_StatusMessage->SetText(FText::FromString(TEXT("Password must be between 12 and 64 characters.")));
		return false;
	}
	
	return true;
}
