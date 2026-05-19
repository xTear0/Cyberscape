// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/DS_PortalHUD.h"
#include "Blueprint/UserWidget.h"
#include "Player/DS_LocalPlayerSubsystem.h"
#include "UI/Portal/Dashboard/DS_DashboardOverlay.h"
#include "UI/Portal/SignIn/DS_SignInOverlay.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_PortalHUD.cpp_Functions
void ADS_PortalHUD::OnSignIn()
{
	if (IsValid(SignInOverlay))
	{
		SignInOverlay->RemoveFromParent();
	}
	
	APlayerController* OwningPlayerController = GetOwningPlayerController();
	DashboardOverlay = CreateWidget<UDS_DashboardOverlay>(OwningPlayerController, DashboardOverlayClass);
	if (IsValid(DashboardOverlay))
	{
		DashboardOverlay->AddToViewport();
	}
}

void ADS_PortalHUD::OnSignOut()
{
	if (IsValid(DashboardOverlay))
	{
		DashboardOverlay->RemoveFromParent();
	}
	
	APlayerController* OwningPlayerController = GetOwningPlayerController();
	SignInOverlay = CreateWidget<UDS_SignInOverlay>(OwningPlayerController, SignInOverlayClass);
	if (IsValid(SignInOverlay))
	{
		SignInOverlay->AddToViewport();
	}
}

void ADS_PortalHUD::BeginPlay()
{
	Super::BeginPlay();

	// Check if the Player is still logged in.
	UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = nullptr;
	bool bIsLoggedIn = false;
	APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	if (IsValid(LocalPlayerController))
	{
		ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(LocalPlayerController->Player);
		if (IsValid(LocalPlayer))
		{
			LocalPlayerSubsystem = LocalPlayer->GetSubsystem<UDS_LocalPlayerSubsystem>();
		}
	}
	if (IsValid(LocalPlayerSubsystem))
	{
		bIsLoggedIn = LocalPlayerSubsystem->bIsLoggedIn;
	}

	if (bIsLoggedIn) // We are already logged in with tokens. We should open the dashboard overlay.
	{
		APlayerController* OwningPlayerController = GetOwningPlayerController();
		DashboardOverlay = CreateWidget<UDS_DashboardOverlay>(OwningPlayerController, DashboardOverlayClass);
		if (IsValid(DashboardOverlay))
		{
			DashboardOverlay->AddToViewport();
			FInputModeGameAndUI InputModeData;
			OwningPlayerController->SetInputMode(InputModeData);
			OwningPlayerController->SetShowMouseCursor(true);
		}
	}
	else // We are not logged in. We should open the sign in overlay.
	{
		APlayerController* OwningPlayerController = GetOwningPlayerController();
		SignInOverlay = CreateWidget<UDS_SignInOverlay>(OwningPlayerController, SignInOverlayClass);
		if (IsValid(SignInOverlay))
		{
			SignInOverlay->AddToViewport();
			FInputModeGameAndUI InputModeData;
			OwningPlayerController->SetInputMode(InputModeData);
			OwningPlayerController->SetShowMouseCursor(true);
		}
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/