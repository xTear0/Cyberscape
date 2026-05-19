// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Player/DS_LocalPlayerSubsystem.h"
#include "UI/Portal/Interfaces/DS_PortalManagement.h"
#include "UI/Portal/DS_PortalManager.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_LocalPlayerSubsystem.cpp_Functions
void UDS_LocalPlayerSubsystem::InitializeTokens(const FDS_AuthenticationResult& AuthResult, TScriptInterface<IDS_PortalManagement> PortalManagement)
{
	AuthenticationResult = AuthResult;
	PortalManagementInterface = PortalManagement;
	SetRefreshTokenTimer();
}

void UDS_LocalPlayerSubsystem::RefreshTokens(const FString& AccessToken, const FString& IdToken)
{
	AuthenticationResult.AccessToken = AccessToken;
	AuthenticationResult.IdToken = IdToken;
	AuthenticationResult.Dump();
	SetRefreshTokenTimer();
}

void UDS_LocalPlayerSubsystem::SetRefreshTokenTimer()
{
	UWorld* World = GetWorld();
	if (IsValid(World) && IsValid(PortalManagementInterface.GetObject()))
	{
		FTimerDelegate RefreshDelegate;
		RefreshDelegate.BindLambda([this]()
		{
			PortalManagementInterface->RefreshTokens(AuthenticationResult.RefreshToken);
		});
		World->GetTimerManager().SetTimer(TokenRefreshTimerHandle, RefreshDelegate, TokenRefreshInterval, false);
	}
}

FDS_AuthenticationResult UDS_LocalPlayerSubsystem::GetAuthenticationResult() const
{
	return AuthenticationResult;
}
#pragma endregion
/*-------------------------------------------------------------------------*/

