// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UI/HTTP/DS_HTTPRequestManager.h"
#include "DS_GameStatsManager.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRetrievedMatchStatsResponseReceived, const FDS_RetrieveMatchStatsResponse&, RetrieveMatchStatsResponse);

struct FDS_RetrieveMatchStatsResponse;
struct FDS_RecordMatchStatsInput;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_GameStatsManager.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_GameStatsManager : public UDS_HTTPRequestManager
{
	GENERATED_BODY()

public:
	void RecordMatchStats(const FDS_RecordMatchStatsInput& RecordMatchStatsInput);
	void RetrieveMatchStats();

	UPROPERTY()
	FOnRetrievedMatchStatsResponseReceived OnRetrievedMatchStatsResponseReceived;
private:
	void RetrieveMatchStats_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
#pragma endregion
/*-------------------------------------------------------------------------*/