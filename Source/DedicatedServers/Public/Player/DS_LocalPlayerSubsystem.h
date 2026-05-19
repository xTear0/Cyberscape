// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "UI/HTTP/DS_HTTPRequestTypes.h"
#include "DS_LocalPlayerSubsystem.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class IDS_PortalManagement;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_LocalPlayerSubsystem.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_LocalPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	FString Username;
	FString Email;
	bool bIsLoggedIn{false};
	
	void InitializeTokens(const FDS_AuthenticationResult& AuthResult, TScriptInterface<IDS_PortalManagement> PortalManagement);
	void RefreshTokens(const FString& AccessToken, const FString& IdToken);
	void SetRefreshTokenTimer();
	FDS_AuthenticationResult GetAuthenticationResult() const;
	
private:
	UPROPERTY()
	FDS_AuthenticationResult AuthenticationResult;

	UPROPERTY()
	TScriptInterface<IDS_PortalManagement> PortalManagementInterface;

	float TokenRefreshInterval = 1740.f;
	// Refreshed once every 29 minutes, since tokens expire every hour. This gives
	// a fallback refresh if a refresh fails for any reason. 

	FTimerHandle TokenRefreshTimerHandle;
};
#pragma endregion
/*-------------------------------------------------------------------------*/