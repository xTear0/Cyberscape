// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/SignIn/DS_SignInPage.h"
#include "Sound/SoundBase.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "System7/Public/Buttons/SYS7_Button_Wide.h"
#include "Texts/SYS7_EditableTextBox.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_SignInPage.cpp_Functions
void UDS_SignInPage::NativeConstruct()
{
	Super::NativeConstruct();
	Button_SignIn->SetIsButtonEnabled(false);
	
	TextBox_Username->OnTextChanged.AddDynamic(this, &UDS_SignInPage::UpdateSignInButtonState);
	TextBox_Password->OnTextChanged.AddDynamic(this, &UDS_SignInPage::UpdateSignInButtonState);
}

void UDS_SignInPage::UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets, EDS_DelegateResponse DelegateResponse)
{
	TextBox_StatusMessage->SetText(FText::FromString(Message));
	if (bShouldResetWidgets)
	{
		if (IsValidPassword() && IsValidUsername())
		{
			Button_SignIn->SetIsButtonEnabled(true);
		}
	}
}

void UDS_SignInPage::UpdateSignInButtonState(const FText& Text)
{
	if (IsValidPassword() && IsValidUsername())
	{
		Button_SignIn->SetIsButtonEnabled(true);
	}
}

void UDS_SignInPage::ClearTextBoxes()
{
	TextBox_Username->SetText(FText::GetEmpty());
	TextBox_Password->SetText(FText::GetEmpty());
	TextBox_StatusMessage->SetText(FText::GetEmpty());
}

bool UDS_SignInPage::IsValidUsername()
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

bool UDS_SignInPage::IsValidPassword()
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
		return false;
	}
	if (!SpecialCharMatcher.FindNext())
	{
		return false;
	}
	if (!UppercaseMatcher.FindNext())
	{
		return false;
	}
	if (!LowercaseMatcher.FindNext())
	{
		return false;
	}
	if (Password.Len() < 12 || Password.Len() > 64)
	{
		return false;
	}
	
	return true;
}

#pragma endregion
/*-------------------------------------------------------------------------*/

