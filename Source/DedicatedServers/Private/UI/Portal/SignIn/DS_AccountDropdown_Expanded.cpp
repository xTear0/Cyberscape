// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/SignIn/DS_AccountDropdown_Expanded.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/Portal/DS_PortalManager.h"
#include "Data/Themes/DS_UITheme.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DS_LocalPlayerSubsystem.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_AccountDropdown_Expanded.cpp_Functions

void UDS_AccountDropdown_Expanded::NativeConstruct()
{
	Super::NativeConstruct();
	check(PortalManagerClass)
	check(Theme_Asset)

	PortalManager = NewObject<UDS_PortalManager>(this, PortalManagerClass);

	Button_SignOut->OnClicked.AddDynamic(this, &UDS_AccountDropdown_Expanded::SignOutButton_OnClicked);
	Button_SignOut->OnHovered.AddDynamic(this, &UDS_AccountDropdown_Expanded::SignOutButton_Hover);
	Button_SignOut->OnUnhovered.AddDynamic(this, &UDS_AccountDropdown_Expanded::SignOutButton_Unhover);

	PortalManager->SignOutStatusMessageDelegate.AddDynamic(this, &UDS_AccountDropdown_Expanded::UpdateSignOutStatusMessage);
	PortalManager->SignOutStatusMessageDelegate.AddDynamic(this, &UDS_AccountDropdown_Expanded::StatusMessageSoundEvent);
	ClearStatusMessageText();

	UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = GetLocalPlayerSubsystem();
	if (IsValid(LocalPlayerSubsystem))
	{
		TextBlock_Email->SetText(FText::FromString(LocalPlayerSubsystem->Email));
	}
}

void UDS_AccountDropdown_Expanded::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Import Global Assets
	if (Theme_Asset)
	{
		HoveredTextColor = Theme_Asset->HoveredTextColor;
		UnhoveredTextColor = Theme_Asset->UnhoveredTextColor;
	}
	
	SetStyleSignOutButtonTransparent();
	SignOutButton_Unhover();
}

void UDS_AccountDropdown_Expanded::SetStyleSignOutButtonTransparent() const
{
	FButtonStyle Style;
	FSlateBrush Brush;
	Brush.TintColor = FSlateColor(FLinearColor(0.f, 0.f, 0.f, 0.f));

	Style.Disabled = Brush;
	Style.Hovered = Brush;
	Style.Pressed = Brush;
	Style.Normal = Brush;
	Button_SignOut->SetStyle(Style);
}

void UDS_AccountDropdown_Expanded::ClearStatusMessageText() const
{
	TextBlock_SignOutStatusMessage->SetText(FText::GetEmpty());
}

void UDS_AccountDropdown_Expanded::SignOutButton_Hover()
{
	TextBlock_SignOutButtonText->SetColorAndOpacity(HoveredTextColor);
}

void UDS_AccountDropdown_Expanded::SignOutButton_Unhover()
{
	TextBlock_SignOutButtonText->SetColorAndOpacity(UnhoveredTextColor);
}

void UDS_AccountDropdown_Expanded::SignOutButton_OnClicked()
{
	Button_SignOut->SetIsEnabled(false);

	check(PortalManager)
	UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = GetLocalPlayerSubsystem();
	if (IsValid(LocalPlayerSubsystem))
	{
		FDS_AuthenticationResult AuthResult = LocalPlayerSubsystem->GetAuthenticationResult();
		PortalManager->SignOut(AuthResult.AccessToken);
	}
}

void UDS_AccountDropdown_Expanded::UpdateSignOutStatusMessage(const FString& Message, bool bShouldResetWidgets,
	EDS_DelegateResponse DelegateResponse)
{
	TextBlock_SignOutStatusMessage->SetText(FText::FromString(Message));
	if (bShouldResetWidgets) Button_SignOut->SetIsEnabled(true);
}

void UDS_AccountDropdown_Expanded::StatusMessageSoundEvent(const FString& Message, bool bShouldResetWidgets,
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
			UGameplayStatics::PlaySound2D(this,		Theme_Asset->SFX_Error_Critical);
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

UDS_LocalPlayerSubsystem* UDS_AccountDropdown_Expanded::GetLocalPlayerSubsystem()
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
#pragma endregion
/*-------------------------------------------------------------------------*/

