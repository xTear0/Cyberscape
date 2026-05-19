// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UI/HTTP/DS_HTTPRequestManager.h"
#include "DS_GameSessionsManager.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_GameSessionsManager.h_Class
UCLASS(Blueprintable)
class DEDICATEDSERVERS_API UDS_GameSessionsManager : public UDS_HTTPRequestManager
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FDS_APIStatusMessage BroadcastJoinGameSessionMessage;

	void JoinGameSession();

private:
	void FindOrCreateGameSession_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void CreatePlayerSession_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	FString GetUniquePlayerId() const;
	void HandleGameSessionStatus(const FString& Status, const FString& GameSessionId);
	void TryCreatePlayerSession(const FString& PlayerId, const FString& GameSessionId);
	
	FTimerHandle CreateSessionTimer;
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/