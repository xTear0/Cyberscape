// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/SignIn/DS_SignInOverlay.h"

#include "Buttons/SYS7_Button_Wide.h"
#include "Data/Themes/DS_UITheme.h"
#include "UI/API/GameSessions/DS_JoinGame.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "GameplayTags/DedicatedServersTags.h"
#include "Kismet/GameplayStatics.h"
#include "Texts/SYS7_EditableTextBox.h"
#include "UI/Portal/SignIn/DS_SignInPage.h"
#include "UI/Portal/SignIn/DS_SignUpPage.h"
#include "UI/Portal/SignIn/DS_SignUpPageConfirmation.h"
#include "UI/Portal/SignIn/DS_SignUpSuccess.h"
#include "UI/Portal/DS_PortalManager.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_SignInOverlay.cpp_Functions
void UDS_SignInOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	if (!IsValid(PortalManagerClass)) return;
	PortalManager = NewObject<UDS_PortalManager>(this, PortalManagerClass);
	
	// Bind the Button to show sign-up page.
	SignInPage->Button_SignUp->OnClicked.AddDynamic(this, &UDS_SignInOverlay::ShowSignUpPage);
	SignInPage->Button_SignIn->OnClicked.AddDynamic(this, &UDS_SignInOverlay::SignInButtonClicked);
	// Bind the button to quit the game.
	SignInPage->Button_Quit->OnClicked.AddDynamic(PortalManager, &UDS_PortalManager::QuitGame);

	// Sign Up Page Button Bindings
	SignUpPage->Button_Back->OnClicked.AddDynamic(this, &UDS_SignInOverlay::ShowSignInPage);
	SignUpPage->Button_SignUp->OnClicked.AddDynamic(this, &UDS_SignInOverlay::SignUpButtonClicked);
	SignUpPage->Button_AlreadyHaveCode->OnClicked.AddDynamic(this, &UDS_SignInOverlay::AlreadyHaveCodeButtonClicked);
	
	// Portal Manager Bindings
	// Widget Switchers
	PortalManager->OnSignUpSucceeded.AddDynamic(this, &UDS_SignInOverlay::OnSignUpSucceeded);
	PortalManager->OnAuthenticationSucceeded.AddDynamic(this, &UDS_SignInOverlay::OnAuthenticationSucceeded);
	PortalManager->OnResendAuthCodeSucceeded.AddDynamic(AlreadyHaveCodePage, &UDS_AlreadyHaveCodePage::UpdateStatusMessage);
	
	// Status Message Delegates
	PortalManager->SignUpStatusMessageDelegate.AddDynamic(SignUpPage, &UDS_SignUpPage::UpdateStatusMessage);
	PortalManager->AuthenticationStatusMessageDelegate.AddDynamic(SignUpPageConfirmation, &UDS_SignUpPageConfirmation::UpdateStatusMessage);
	PortalManager->SignInStatusMessageDelegate.AddDynamic(SignInPage, &UDS_SignInPage::UpdateStatusMessage);
	PortalManager->AlreadyReceivedAuthCodeStatusMessageDelegate.AddDynamic(AlreadyHaveCodePage, &UDS_AlreadyHaveCodePage::UpdateStatusMessage);

	// Status Message Sound Events
	PortalManager->SignUpStatusMessageDelegate.AddDynamic(this, &UDS_SignInOverlay::StatusMessageSoundEvent);
	PortalManager->AuthenticationStatusMessageDelegate.AddDynamic(this, &UDS_SignInOverlay::StatusMessageSoundEvent);
	PortalManager->SignInStatusMessageDelegate.AddDynamic(this, &UDS_SignInOverlay::StatusMessageSoundEvent);
	PortalManager->AlreadyReceivedAuthCodeStatusMessageDelegate.AddDynamic(this, &UDS_SignInOverlay::StatusMessageSoundEvent);
	
	// Sign Up Page Confirmation Button Binding
	SignUpPageConfirmation->Button_Confirm->OnClicked.AddDynamic(this, &UDS_SignInOverlay::AuthConfirmButtonClicked);
	SignUpPageConfirmation->Button_Back->OnClicked.AddDynamic(this, &UDS_SignInOverlay::ShowSignUpPage);

	// Sign Up Succeeded Button Binding
	SignUpSuccess->Button_Ok->OnClicked.AddDynamic(this, &UDS_SignInOverlay::ShowSignInPage);

	// Already have a code Button Binding
	AlreadyHaveCodePage->Button_ConfirmCode->OnClicked.AddDynamic(this, &UDS_SignInOverlay::AlreadyHaveCodeConfirmButtonClicked);
	AlreadyHaveCodePage->Button_ResendCode->OnClicked.AddDynamic(this, &UDS_SignInOverlay::ResendAuthCodeButtonClicked);
	AlreadyHaveCodePage->Button_Back->OnClicked.AddDynamic(this, &UDS_SignInOverlay::ShowSignUpPage);
}

void UDS_SignInOverlay::ShowSignInPage()
{
	WidgetSwitcher->SetActiveWidget(SignInPage);
}

void UDS_SignInOverlay::ShowSignUpPage()
{
	WidgetSwitcher->SetActiveWidget(SignUpPage);
}

void UDS_SignInOverlay::ShowAlreadyHaveCodePage()
{
	WidgetSwitcher->SetActiveWidget(AlreadyHaveCodePage);
}

void UDS_SignInOverlay::ShowSignUpPageConfirmation()
{
	WidgetSwitcher->SetActiveWidget(SignUpPageConfirmation);
}

void UDS_SignInOverlay::ShowSignUpSuccess()
{
	WidgetSwitcher->SetActiveWidget(SignUpSuccess);
	SignInPage->ClearTextBoxes();
	SignUpPage->ClearTextBoxes();
	SignUpPageConfirmation->ClearTextBoxes();
	AlreadyHaveCodePage->ClearTextBoxes();
}

void UDS_SignInOverlay::SignInButtonClicked()
{
	const FString Username = SignInPage->TextBox_Username->GetText().ToString();
	const FString Password = SignInPage->TextBox_Password->GetText().ToString();
	
	PortalManager->SignIn(Username, Password);
}

void UDS_SignInOverlay::SignUpButtonClicked()
{
	const FString Username = SignUpPage->TextBox_Username->GetText().ToString();
	const FString Password = SignUpPage->TextBox_Password->GetText().ToString();
	const FString Email = SignUpPage->TextBox_Email->GetText().ToString();
	
	PortalManager->SignUp(Username, Password, Email);	
}

void UDS_SignInOverlay::AuthConfirmButtonClicked()
{
	const FString AuthCode = SignUpPageConfirmation->TextBox_ConfirmationCode->GetText().ToString();
	SignUpPageConfirmation->Button_Confirm->SetIsEnabled(false);
	PortalManager->AuthConfirmation(AuthCode);
}

void UDS_SignInOverlay::AlreadyHaveCodeButtonClicked()
{
	SignUpPageConfirmation->ClearTextBoxes();
	ShowAlreadyHaveCodePage();
}

void UDS_SignInOverlay::AlreadyHaveCodeConfirmButtonClicked()
{
	const FString Username = AlreadyHaveCodePage->TextBox_Username->GetText().ToString();
	const FString AuthCode = AlreadyHaveCodePage->TextBox_ConfirmationCode->GetText().ToString();
	AlreadyHaveCodePage->Button_ConfirmCode->SetIsEnabled(false);
	PortalManager->AlreadyHaveCodeAuthConfirmation(Username, AuthCode);
}

void UDS_SignInOverlay::ResendAuthCodeButtonClicked()
{
	const FString Username = AlreadyHaveCodePage->TextBox_Username->GetText().ToString();
	AlreadyHaveCodePage->Button_ResendCode->SetIsEnabled(false);
	PortalManager->ResendAuthConfirmation(Username);
}

void UDS_SignInOverlay::OnSignUpSucceeded()
{
	SignUpPage->ClearTextBoxes();
	
	if (!PortalManager->LastSignUpResponse.CodeDeliveryDetails.Destination.IsEmpty())
	{
		SignUpPageConfirmation->TextBox_Destination->SetText(FText::FromString(
		PortalManager->LastSignUpResponse.CodeDeliveryDetails.Destination));
	} else
	{
		SignUpPageConfirmation->TextBox_Destination->SetText(FText::FromString("Username's Email"));
	}
	ShowSignUpPageConfirmation();
	UGameplayStatics::PlaySound2D(this,Theme_Asset->SFX_NextStep);
}

void UDS_SignInOverlay::OnAuthenticationSucceeded()
{
	SignUpPageConfirmation->ClearTextBoxes();
	ShowSignUpSuccess();
}

void UDS_SignInOverlay::StatusMessageSoundEvent(const FString& Message, bool bShouldResetWidgets,
	EDS_DelegateResponse DelegateResponse)
{
	if (DelegateResponse == EDS_DelegateResponse::ResponseError)
	{
		if (Theme_Asset->SFX_Error)
		{
			UGameplayStatics::PlaySound2D(this, Theme_Asset->SFX_Error);
		}
	}
	if (DelegateResponse == EDS_DelegateResponse::ResponseErrorCritical)
	{
		if (Theme_Asset->SFX_Error_Critical)
		{
			UGameplayStatics::PlaySound2D(this, Theme_Asset->SFX_Error_Critical);
		}
	}
	if (DelegateResponse == EDS_DelegateResponse::ResponseSuccess)
	{
		if (Theme_Asset->SFX_Success)
		{
			UGameplayStatics::PlaySound2D(this, Theme_Asset->SFX_Success);
		}
	}
	if (DelegateResponse == EDS_DelegateResponse::ResponseSuccessSuper)
	{
		if (Theme_Asset->SFX_Success_Super)
		{
			UGameplayStatics::PlaySound2D(this, Theme_Asset->SFX_Success_Super);
		}
	}
	if (DelegateResponse == EDS_DelegateResponse::ResponseNextStep)
	{
		if (Theme_Asset->SFX_NextStep)
		{
			UGameplayStatics::PlaySound2D(this, Theme_Asset->SFX_NextStep);
		}
	}
	if (DelegateResponse == EDS_DelegateResponse::BroadcastClick)
	{
		if (Theme_Asset->SFX_Click)
		{
			UGameplayStatics::PlaySound2D(this, Theme_Asset->SFX_Click);
		}
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
