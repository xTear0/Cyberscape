// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/Dashboard/Menu/DS_AccountDropdown.h"

#include "Buttons/CUI_Button_Wide.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Menus/Dropdown/CUI_Menu_Dropdown_Expanded.h"
#include "Player/DS_LocalPlayerSubsystem.h"
#include "UI/Portal/DS_PortalManager.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_AccountDropdown.cpp_Functions
void UDS_AccountDropdown::NativeConstruct()
{
	Super::NativeConstruct();

	UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = GetLocalPlayerSubsystem();
	if (!IsValid(LocalPlayerSubsystem))
	{
		return;
	}

	PortalManager = NewObject<UDS_PortalManager>(this, PortalManagerClass);

	/*-------------------------------------------------------------------------*/
	// All the buttons are independently assignable to whatever you need.
	// This class is an example of an interface between the CUI Menu Dropdown
	// and a functional dedicated servers class.
	/*-------------------------------------------------------------------------*/
	/*	Legend:	*/
	 /* Button_Option1 - Change Password	*/
	Menu_Expanded->Button_Option1->SetText(FText::FromString("Change Password"));
	Menu_Expanded->Button_Option1->OnClicked.AddDynamic(this, &UDS_AccountDropdown::ChangePasswordButton_OnClicked);

	/* Button_Option2 - Change Email		*/
	Menu_Expanded->Button_Option2->SetText(FText::FromString("Change Email"));
	Menu_Expanded->Button_Option2->OnClicked.AddDynamic(this, &UDS_AccountDropdown::ChangeEmailButton_OnClicked);

	/* Button_Option3 - Contact Support		*/
	Menu_Expanded->Button_Option3->SetText(FText::FromString("Contact Support"));
	Menu_Expanded->Button_Option3->OnClicked.AddDynamic(this, &UDS_AccountDropdown::ContactSupportButton_OnClicked);

	/* Button_Option4 - Sign Out			*/
	Menu_Expanded->Button_Option4->SetText(FText::FromString("Sign Out"));
	Menu_Expanded->Button_Option4->OnClicked.AddDynamic(this, &UDS_AccountDropdown::SignOutButton_OnClicked);
	PortalManager->SignOutStatusMessageDelegate.AddDynamic(this, &UDS_AccountDropdown::UpdateSignOutStatusMessage);
	PortalManager->SignOutStatusMessageDelegate.AddDynamic(this, &UDS_AccountDropdown::StatusMessageSoundEvent);
	
	ClearStatusMessageText();

	// Fill in Dynamic Title.
	Button_ToggleDropdown->SetText(FText::FromString(LocalPlayerSubsystem->Username));
	
	// Fill in Dynamic Subtitle.
	Menu_Expanded->TextBlock_OptionsSubtitle->SetText(FText::FromString(LocalPlayerSubsystem->Email));
}

UDS_LocalPlayerSubsystem* UDS_AccountDropdown::GetLocalPlayerSubsystem() const
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (IsValid(PlayerController) && IsValid(PlayerController->GetLocalPlayer()))
	{
		UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UDS_LocalPlayerSubsystem>();
		if (IsValid(LocalPlayerSubsystem))
		{
			return LocalPlayerSubsystem;
		}
	}
	return nullptr;
}

void UDS_AccountDropdown::ChangePasswordButton_OnClicked()
{
	// TODO: Implement
}

void UDS_AccountDropdown::ChangeEmailButton_OnClicked()
{
	// TODO: Implement
}

void UDS_AccountDropdown::ContactSupportButton_OnClicked()
{
	// TODO: Implement
}

void UDS_AccountDropdown::SignOutButton_OnClicked()
{
	Menu_Expanded->Button_Option4->SetIsEnabled(false);

	check(PortalManager)
	UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = GetLocalPlayerSubsystem();
	if (IsValid(LocalPlayerSubsystem))
	{
		FDS_AuthenticationResult AuthResult = LocalPlayerSubsystem->GetAuthenticationResult();
		PortalManager->SignOut(AuthResult.AccessToken);
	}
}

void UDS_AccountDropdown::UpdateSignOutStatusMessage(const FString& Message, bool bShouldResetWidgets,
	EDS_DelegateResponse DelegateResponse)
{
	Menu_Expanded->TextBlock_StatusMessage->SetText(FText::FromString(Message));
	if (bShouldResetWidgets) Menu_Expanded->Button_Option4->SetIsEnabled(true);
}

void UDS_AccountDropdown::StatusMessageSoundEvent(const FString& Message, bool bShouldResetWidgets,
	EDS_DelegateResponse DelegateResponse)
{
	if (DelegateResponse == EDS_DelegateResponse::ResponseError)
	{
		UGameplayStatics::PlaySound2D(this, StyleAsset->GetSoundBaseByName(TEXT("Error")));
	}
	if (DelegateResponse == EDS_DelegateResponse::ResponseErrorCritical)
	{
		UGameplayStatics::PlaySound2D(this, StyleAsset->GetSoundBaseByName(TEXT("Incorrect Credentials")));
	}
	if (DelegateResponse == EDS_DelegateResponse::ResponseSuccess)
	{
		UGameplayStatics::PlaySound2D(this, StyleAsset->GetSoundBaseByName(TEXT("Transition")));
	}
	if (DelegateResponse == EDS_DelegateResponse::ResponseSuccessSuper)
	{
		UGameplayStatics::PlaySound2D(this, StyleAsset->GetSoundBaseByName(TEXT("Successful Login")));
	}
	if (DelegateResponse == EDS_DelegateResponse::ResponseNextStep)
	{
		UGameplayStatics::PlaySound2D(this, StyleAsset->GetSoundBaseByName(TEXT("Next")));
	}
	if (DelegateResponse == EDS_DelegateResponse::BroadcastClick)
	{
		UGameplayStatics::PlaySound2D(this, StyleAsset->GetSoundBaseByName(TEXT("Button Click")));
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
