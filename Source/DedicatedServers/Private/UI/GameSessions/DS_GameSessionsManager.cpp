// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/GameSessions/DS_GameSessionsManager.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Data/API/APIData.h"
#include "GameFramework/PlayerState.h"
#include "GameplayTags/DedicatedServersTags.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DS_LocalPlayerSubsystem.h"
#include "UI/HTTP/DS_HTTPRequestTypes.h"
#include "Utils/DS_ErrorUtils.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_GameSessionsManager.cpp_Functions
void UDS_GameSessionsManager::JoinGameSession()
{
	BroadcastJoinGameSessionMessage.Broadcast(TEXT("Searching for a Game Session..."), false, EDS_DelegateResponse::BroadcastClick);

	check(APIData);
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UDS_GameSessionsManager::FindOrCreateGameSession_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::GameSessionsAPI::FindOrCreateGameSession);
	Request->SetURL(APIUrl);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");

	UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = GetDS_LocalPlayerSubsystem();
	if (IsValid(LocalPlayerSubsystem))
	{
		if (LocalPlayerSubsystem->GetAuthenticationResult().AccessToken.IsEmpty())
		{
			BroadcastJoinGameSessionMessage.Broadcast(TEXT("Authentication credentials are stale. Please log in again."), true, EDS_DelegateResponse::ResponseError);
			return;
		}
		Request->SetHeader(TEXT("Authorization"), LocalPlayerSubsystem->GetAuthenticationResult().AccessToken);
	}
	Request->ProcessRequest();
}

void UDS_GameSessionsManager::FindOrCreateGameSession_Response(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			FString Exception = UDS_ErrorUtils::GetFindOrCreateGameSessionResponseException(JsonObject);
			BroadcastJoinGameSessionMessage.Broadcast(Exception, true, EDS_DelegateResponse::ResponseError);
		}
		
		FDS_GameSession GameSession;
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &GameSession);

		const FString GameSessionId = GameSession.GameSessionId;
		const FString GameSessionStatus = GameSession.Status;
		HandleGameSessionStatus(GameSessionStatus, GameSessionId);
	}
}

void UDS_GameSessionsManager::CreatePlayerSession_Response(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			FString Exception = UDS_ErrorUtils::GetCreatePlayerResponseException(JsonObject);
			BroadcastJoinGameSessionMessage.Broadcast(Exception, true, EDS_DelegateResponse::ResponseError);
		}
		
		FDS_PlayerSession PlayerSession;
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &PlayerSession);
		PlayerSession.Dump();

		// Set Player Input Mode
		APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
		if (IsValid(LocalPlayerController))
		{
			FInputModeGameOnly GameInputMode;
			LocalPlayerController->SetInputMode(GameInputMode);
			LocalPlayerController->SetShowMouseCursor(false);

			const FString Options =
				"?PlayerSessionId=" + PlayerSession.PlayerSessionId +
				"?Username=" + PlayerSession.PlayerId;

			// Join Level from IP and Port
			const FString IpAndPort = PlayerSession.IpAddress + TEXT(":") + FString::FromInt(PlayerSession.Port);
			const FName Address(*IpAndPort);
			//LocalPlayerController->ClientTravel(*IpAndPort, TRAVEL_Absolute);
			UGameplayStatics::OpenLevel(this, Address, true, Options);
		}
	}
}

FString UDS_GameSessionsManager::GetUniquePlayerId() const
{
	APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	if (IsValid(LocalPlayerController))
	{
		APlayerState* LocalPlayerState = LocalPlayerController->GetPlayerState<APlayerState>();
		if (IsValid(LocalPlayerState) && LocalPlayerState->GetUniqueId().IsValid())
		{
			const FString UniqueId = TEXT("Player_") + FString::FromInt(LocalPlayerState->GetUniqueID());
			return UniqueId;
		}
	} return FString();
}

void UDS_GameSessionsManager::HandleGameSessionStatus(const FString& Status, const FString& GameSessionId)
{
	if (Status.Equals(TEXT("ACTIVE")))
	{
		BroadcastJoinGameSessionMessage.Broadcast(TEXT("Found active Game Session. Creating a Player Session..."), false, EDS_DelegateResponse::ResponseSuccess);

		if (UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = GetDS_LocalPlayerSubsystem(); IsValid(LocalPlayerSubsystem))
		{
			TryCreatePlayerSession(LocalPlayerSubsystem->Username, GameSessionId);
		}
	}
	else if (Status.Equals(TEXT("ACTIVATING")))
	{
		FTimerDelegate CreateSessionDelegate;
		CreateSessionDelegate.BindUObject(this, &ThisClass::JoinGameSession);
        
		APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
		if (IsValid(LocalPlayerController))
		{
			LocalPlayerController->GetWorldTimerManager().ClearTimer(CreateSessionTimer);
			LocalPlayerController->GetWorldTimerManager().SetTimer(CreateSessionTimer, CreateSessionDelegate, 0.5f, false);
		}
	}
	else
	{
		BroadcastJoinGameSessionMessage.Broadcast(TEXT("Could not find or connect to a server running this game version. Please contact support."), true, EDS_DelegateResponse::ResponseErrorCritical);
	}
}

void UDS_GameSessionsManager::TryCreatePlayerSession(const FString& PlayerId, const FString& GameSessionId)
{
	check(APIData);
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UDS_GameSessionsManager::CreatePlayerSession_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::GameSessionsAPI::CreatePlayerSession);
	Request->SetURL(APIUrl);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");

	TMap<FString, FString> Params = {
		{ TEXT("playerId"), PlayerId },
		{ TEXT("gameSessionId"), GameSessionId },
	};
	const FString Content = SerializeJsonContent(Params);
	
	Request->SetContentAsString(Content);
	Request->ProcessRequest();
}
#pragma endregion
/*-------------------------------------------------------------------------*/
