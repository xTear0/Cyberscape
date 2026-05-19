// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/DS_PortalManager.h"
#include "GameplayTags/DedicatedServersTags.h"
#include "Data/API/APIData.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DS_LocalPlayerSubsystem.h"
#include "UI/Portal/Interfaces/DS_HUDManagement.h"
#include "GameFramework/HUD.h"
#include "Utils/DS_ErrorUtils.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_PortalManager.cpp_Functions
void UDS_PortalManager::SignIn(const FString& Username, const FString& Password)
{
	SignInStatusMessageDelegate.Broadcast(TEXT("Signing in..."), false, EDS_DelegateResponse::BroadcastClick);
	
	check(APIData);
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UDS_PortalManager::SignIn_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::SignIn);
	Request->SetURL(APIUrl);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");

	LastUsername = Username;
	
	TMap<FString, FString> Params = {
		{ TEXT("username"), Username },
		{ TEXT("password"), Password }
	};
	const FString Content = SerializeJsonContent(Params);
	
	Request->SetContentAsString(Content);
	Request->ProcessRequest();
}

void UDS_PortalManager::SignUp(const FString& Username, const FString& Password, const FString& Email)
{
	SignUpStatusMessageDelegate.Broadcast(TEXT("Creating New Account..."), false, EDS_DelegateResponse::BroadcastClick);
	
	check(APIData);
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UDS_PortalManager::SignUp_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::SignUp);
	Request->SetURL(APIUrl);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");

	LastUsername = Username;
	
	TMap<FString, FString> Params = {
		{ TEXT("username"), Username },
		{ TEXT("password"), Password },
		{ TEXT("email"), Email}
	};
	const FString Content = SerializeJsonContent(Params);
	
	Request->SetContentAsString(Content);
	Request->ProcessRequest();
}

void UDS_PortalManager::QuitGame()
{
	APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	if (IsValid(LocalPlayerController))
	{
		UKismetSystemLibrary::QuitGame(this, LocalPlayerController, EQuitPreference::Quit, false);
	}
}

void UDS_PortalManager::SignIn_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			FString Exception = UDS_ErrorUtils::GetInitiateAuthException(JsonObject);
			SignInStatusMessageDelegate.Broadcast(Exception, true, EDS_DelegateResponse::ResponseError);
			return;
		}
		SignInStatusMessageDelegate.Broadcast(TEXT("Sign-in Successful."), false, EDS_DelegateResponse::ResponseSuccess);
		FDS_InitiateAuthResponse InitiateAuthResponse;
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &InitiateAuthResponse);

		UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = GetDS_LocalPlayerSubsystem();
		if (IsValid(LocalPlayerSubsystem))
		{
			LocalPlayerSubsystem->InitializeTokens(InitiateAuthResponse.AuthenticationResult, this);
			LocalPlayerSubsystem->Username = LastUsername;
			LocalPlayerSubsystem->Email = InitiateAuthResponse.email;
			LocalPlayerSubsystem->bIsLoggedIn = true;
		}

		APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
		if (IsValid(LocalPlayerController))
		{
			if (IDS_HUDManagement* HUDManagementInterface = Cast<IDS_HUDManagement>(LocalPlayerController->GetHUD()))
			{
				HUDManagementInterface->OnSignIn();
			}
		}
	}
}

void UDS_PortalManager::SignUp_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			FString Exception = UDS_ErrorUtils::GetSignUpException(JsonObject);
			SignUpStatusMessageDelegate.Broadcast(Exception, true, EDS_DelegateResponse::ResponseError);
			return;
		}
		
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &LastSignUpResponse);
		LastSignUpResponse.Dump();
		OnSignUpSucceeded.Broadcast();
	}
}

void UDS_PortalManager::AuthConfirmation(const FString& Code)
{
	SignUpStatusMessageDelegate.Broadcast(TEXT("Authenticating..."), false, EDS_DelegateResponse::BroadcastClick);
	
	check(APIData);
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UDS_PortalManager::AuthenticateSignUp_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::SignUpConfirm);
	Request->SetURL(APIUrl);
	Request->SetVerb("PUT");
	Request->SetHeader("Content-Type", "application/json");

	TMap<FString, FString> Params = {
		{ TEXT("username"), LastUsername },
		{ TEXT("confirmationCode"), Code }
	};
	const FString Content = SerializeJsonContent(Params);
	
	Request->SetContentAsString(Content);
	Request->ProcessRequest();
}

void UDS_PortalManager::AlreadyHaveCodeAuthConfirmation(const FString& Username, const FString& Code)
{
	AlreadyReceivedAuthCodeStatusMessageDelegate.Broadcast(TEXT("Authenticating..."), false, EDS_DelegateResponse::BroadcastClick);
	
	check(APIData);
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UDS_PortalManager::AuthenticateSignUp_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::SignUpConfirm);
	Request->SetURL(APIUrl);
	Request->SetVerb("PUT");
	Request->SetHeader("Content-Type", "application/json");

	TMap<FString, FString> Params = {
		{ TEXT("username"), Username },
		{ TEXT("confirmationCode"), Code }
	};
	const FString Content = SerializeJsonContent(Params);
	
	Request->SetContentAsString(Content);
	Request->ProcessRequest();
}

void UDS_PortalManager::ResendAuthConfirmation(const FString& Username)
{
	SignUpStatusMessageDelegate.Broadcast(TEXT("Resending..."), false, EDS_DelegateResponse::BroadcastClick);
	
	check(APIData);
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UDS_PortalManager::ResendAuthConfirmation_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::ResendSignUpConfirm);
	Request->SetURL(APIUrl);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");

	TMap<FString, FString> Params = {
		{ TEXT("username"), Username },
	};
	const FString Content = SerializeJsonContent(Params);
	
	Request->SetContentAsString(Content);
	Request->ProcessRequest();
}

void UDS_PortalManager::AuthenticateSignUp_Response(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                                    bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			FString Exception = UDS_ErrorUtils::GetConfirmSignUpException(JsonObject);
			AuthenticationStatusMessageDelegate.Broadcast(Exception, true, EDS_DelegateResponse::ResponseError);
			AlreadyReceivedAuthCodeStatusMessageDelegate.Broadcast(Exception, true, EDS_DelegateResponse::ResponseError);
			return;
		}
		OnAuthenticationSucceeded.Broadcast();
		AuthenticationStatusMessageDelegate.Broadcast("Succeeded", true, EDS_DelegateResponse::ResponseSuccessSuper);
	}
}

void UDS_PortalManager::ResendAuthConfirmation_Response(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			FString Exception = UDS_ErrorUtils::GetResendConfirmationCodeException(JsonObject);
			AlreadyReceivedAuthCodeStatusMessageDelegate.Broadcast(Exception, true, EDS_DelegateResponse::ResponseError);
			return;
		}
		AlreadyReceivedAuthCodeStatusMessageDelegate.Broadcast("Authentication code resent!", true, EDS_DelegateResponse::ResponseSuccess);
	}
}

void UDS_PortalManager::RefreshTokens(const FString& RefreshToken)
{
	SignInStatusMessageDelegate.Broadcast(TEXT("Refreshing..."), false, EDS_DelegateResponse::Null);
	
	check(APIData);
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UDS_PortalManager::RefreshTokens_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::SignIn);
	Request->SetURL(APIUrl);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	
	TMap<FString, FString> Params = {
		{ TEXT("refreshToken"), RefreshToken }
	};
	const FString Content = SerializeJsonContent(Params);
	
	Request->SetContentAsString(Content);
	Request->ProcessRequest();
}

void UDS_PortalManager::RefreshTokens_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful) return;

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			return;
		}

		FDS_InitiateAuthResponse InitiateAuthResponse;
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &InitiateAuthResponse);

		UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = GetDS_LocalPlayerSubsystem();
		if (IsValid(LocalPlayerSubsystem))
		{
			LocalPlayerSubsystem->RefreshTokens(
				InitiateAuthResponse.AuthenticationResult.AccessToken,
				InitiateAuthResponse.AuthenticationResult.IdToken);
		}
		
	}
}

void UDS_PortalManager::SignOut(const FString& AccessToken)
{
	SignOutStatusMessageDelegate.Broadcast(TEXT("Signing out..."), false, EDS_DelegateResponse::Null);
	
	check(APIData);
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UDS_PortalManager::SignOut_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::SignOut);
	Request->SetURL(APIUrl);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	
	TMap<FString, FString> Params = {
		{ TEXT("accessToken"), AccessToken }
	};
	const FString Content = SerializeJsonContent(Params);
	
	Request->SetContentAsString(Content);
	Request->ProcessRequest();
}

void UDS_PortalManager::SignOut_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			FString Exception = UDS_ErrorUtils::GetGlobalSignOutException(JsonObject);
			
			SignOutStatusMessageDelegate.Broadcast(Exception, true, EDS_DelegateResponse::ResponseError);
			return;
		}
		SignOutStatusMessageDelegate.Broadcast("Successfully signed out.", false, EDS_DelegateResponse::ResponseSuccess);
		APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
		if (IsValid(LocalPlayerController))
		{
			if (IDS_HUDManagement* HUDManagementInterface = Cast<IDS_HUDManagement>(LocalPlayerController->GetHUD()))
			{
				UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = GetDS_LocalPlayerSubsystem();
				if (IsValid(LocalPlayerSubsystem))
				{
					LocalPlayerSubsystem->bIsLoggedIn = false;
				}
				HUDManagementInterface->OnSignOut();
			}
		}
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
