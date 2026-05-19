// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Interfaces/DS_PortalManagement.h"
#include "UI/HTTP/DS_HTTPRequestManager.h"
#include "Interfaces/IHttpRequest.h"
#include "UI/HTTP/DS_HTTPRequestTypes.h"
#include "DS_PortalManager.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_PortalManager.h_Class
UCLASS(Blueprintable)
class DEDICATEDSERVERS_API UDS_PortalManager : public UDS_HTTPRequestManager, public IDS_PortalManagement
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable) FDS_APIStatusMessage SignInStatusMessageDelegate;
	UPROPERTY(BlueprintAssignable) FDS_APIStatusMessage SignUpStatusMessageDelegate;
	UPROPERTY(BlueprintAssignable) FDS_APIStatusMessage SignOutStatusMessageDelegate;
	UPROPERTY(BlueprintAssignable) FDS_APIStatusMessage AuthenticationStatusMessageDelegate;
	UPROPERTY(BlueprintAssignable) FDS_APIStatusMessage OnResendAuthCodeSucceeded;
	UPROPERTY(BlueprintAssignable) FDS_APIStatusMessage AlreadyReceivedAuthCodeStatusMessageDelegate;
	UPROPERTY(BlueprintAssignable) FDS_OnAPIRequestSucceeded OnSignUpSucceeded;
	UPROPERTY(BlueprintAssignable) FDS_OnAPIRequestSucceeded OnAuthenticationSucceeded;
	
	void SignIn(const FString& Username, const FString& Password);
	void SignUp(const FString& Username, const FString& Password, const FString& Email);
	void SignOut(const FString& AccessToken);
	void AuthConfirmation(const FString& Code);
	void AlreadyHaveCodeAuthConfirmation(const FString& Username, const FString& Code);
	void ResendAuthConfirmation(const FString& Username);

	// IDS_PortalManagement Interface
	virtual void RefreshTokens(const FString& RefreshToken) override;

	UFUNCTION()
	void QuitGame();

	UPROPERTY()	FDS_SignUpResponse LastSignUpResponse;

	UPROPERTY() FString LastUsername;

private:
	void SignIn_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void SignUp_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void SignOut_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void AuthenticateSignUp_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void ResendAuthConfirmation_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void RefreshTokens_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/