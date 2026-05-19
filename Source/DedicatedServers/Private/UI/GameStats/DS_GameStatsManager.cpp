// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/GameStats/DS_GameStatsManager.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Data/API/APIData.h"
#include "GameplayTags/DedicatedServersTags.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Player/DS_LocalPlayerSubsystem.h"
#include "UI/HTTP/DS_HTTPRequestTypes.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_GameStatsManager.cpp_Functions
void UDS_GameStatsManager::RecordMatchStats(const FDS_RecordMatchStatsInput& RecordMatchStatsInput)
{
	FString JsonString;
	FJsonObjectConverter::UStructToJsonObjectString(
		FDS_RecordMatchStatsInput::StaticStruct(),
		&RecordMatchStatsInput,
		JsonString);

	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::GameStatsAPI::RecordMatchStats);
	Request->SetURL(APIUrl);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(JsonString);
	Request->ProcessRequest();
}

void UDS_GameStatsManager::RetrieveMatchStats()
{
	UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = GetDS_LocalPlayerSubsystem();
	if (!IsValid(LocalPlayerSubsystem)) return;
	check(APIData);
	
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::GameStatsAPI::RetrieveMatchStats);
	Request->OnProcessRequestComplete().BindUObject(this, &UDS_GameStatsManager::RetrieveMatchStats_Response);
	Request->SetURL(APIUrl);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");

	TMap<FString, FString> Params = {
		{TEXT("accessToken"), LocalPlayerSubsystem->GetAuthenticationResult().AccessToken }
	};
	const FString Content = SerializeJsonContent(Params);
	
	Request->SetContentAsString(Content);
	Request->ProcessRequest();
}

void UDS_GameStatsManager::RetrieveMatchStats_Response(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		OnRetrievedMatchStatsResponseReceived.Broadcast(FDS_RetrieveMatchStatsResponse());
		return;
	}
		
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{	
		if (ContainsErrors(JsonObject))
		{
			OnRetrievedMatchStatsResponseReceived.Broadcast(FDS_RetrieveMatchStatsResponse());
			return;
		}
		
		FDS_RetrieveMatchStatsResponse RetrieveMatchStatsResponse;
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &RetrieveMatchStatsResponse);
		RetrieveMatchStatsResponse.Dump();
			
		OnRetrievedMatchStatsResponseReceived.Broadcast(RetrieveMatchStatsResponse);
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/

