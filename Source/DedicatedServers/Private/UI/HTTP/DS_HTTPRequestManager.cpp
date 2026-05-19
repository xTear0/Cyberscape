// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/HTTP/DS_HTTPRequestManager.h"
#include "JsonObjectConverter.h"
#include "DedicatedServers/DedicatedServers.h"
#include "Player/DS_LocalPlayerSubsystem.h"
#include "UI/HTTP/DS_HTTPRequestTypes.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_HTTPRequestManager.cpp_Functions
UDS_LocalPlayerSubsystem* UDS_HTTPRequestManager::GetDS_LocalPlayerSubsystem() const
{
	// Get Local Player Subsystem to set the Credentials there.
	APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	if (IsValid(LocalPlayerController))
	{
		ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(LocalPlayerController->Player);
		if (IsValid(LocalPlayer))
		{
			return LocalPlayer->GetSubsystem<UDS_LocalPlayerSubsystem>();
		}
	}
	return nullptr;
}

bool UDS_HTTPRequestManager::ContainsErrors(TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject->HasField(TEXT("errorType")) || JsonObject->HasField(TEXT("errorMessage")))
	{
		FString ErrorType = JsonObject->HasField(TEXT("errorType")) ? JsonObject->GetStringField(TEXT("errorType")) : TEXT("Unknown Error");
		FString ErrorMessage = JsonObject->HasField(TEXT("errorMessage")) ? JsonObject->GetStringField(TEXT("errorMessage")) : TEXT("Unknown Error Message");
			
		UE_LOG(LogDedicatedServers, Error, TEXT("ErrorType: %s"), *ErrorType);
		UE_LOG(LogDedicatedServers, Error, TEXT("ErrorMessage: %s"), *ErrorMessage);

		return true;
	}

	if (JsonObject->HasField(TEXT("$fault")))
	{
		FString ErrorType = JsonObject->HasField(TEXT("name")) ? JsonObject->GetStringField(TEXT("name")) : TEXT("Unknown Error");
		UE_LOG(LogDedicatedServers, Error, TEXT("ErrorType: %s"), *ErrorType);

		return true;
	}
	return false;
}

void UDS_HTTPRequestManager::DumpMetaData(TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject->HasField(TEXT("$metadata")))
	{
		TSharedPtr<FJsonObject> MetaDataJsonObject = JsonObject->GetObjectField(TEXT("$metadata"));

		FDS_MetaData DS_MetaData;
		FJsonObjectConverter::JsonObjectToUStruct(

		MetaDataJsonObject.ToSharedRef(), &DS_MetaData);
		DS_MetaData.Dump();
	}
}

FString UDS_HTTPRequestManager::SerializeJsonContent(const TMap<FString, FString>& Params)
{
	TSharedPtr<FJsonObject> ContentJsonObject = MakeShareable(new FJsonObject);
	
	for (const auto& Param : Params)
	{
		ContentJsonObject->SetStringField(Param.Key, Param.Value);
	}
	
	FString Content;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Content);
	FJsonSerializer::Serialize(ContentJsonObject.ToSharedRef(), JsonWriter);

	return Content;
}
#pragma endregion
/*-------------------------------------------------------------------------*/