// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UI/HTTP/DS_HTTPRequestManager.h"
#include "UI/HTTP/DS_HTTPRequestTypes.h"
#include "DS_APITestManager.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListFleetsResponseReceived, const FDS_ListFleetsResponse&, ListFleetsResponse, bool, bWasSuccessful);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_APITestManager.h_Class
UCLASS(Blueprintable)
class DEDICATEDSERVERS_API UDS_APITestManager : public UDS_HTTPRequestManager
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ListFleets();

	UPROPERTY()
	FOnListFleetsResponseReceived OnListFleetsResponseReceived;
	
	void ListFleets_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/