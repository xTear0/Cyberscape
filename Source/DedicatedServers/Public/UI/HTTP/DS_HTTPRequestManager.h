// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Types/DS_EnumTypes.h"
#include "UObject/Object.h"
#include "DS_HTTPRequestManager.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDS_APIStatusMessage, const FString&, StatusMessage, bool, bShouldResetWidgets, EDS_DelegateResponse, DelegateResponse); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDS_OnAPIRequestSucceeded);

class UAPIData;
class FJsonObject;
class UDS_LocalPlayerSubsystem;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_HTTPRequestManager.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_HTTPRequestManager : public UObject
{
	GENERATED_BODY()
public:
	UDS_LocalPlayerSubsystem* GetDS_LocalPlayerSubsystem() const;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAPIData> APIData;

	bool ContainsErrors(TSharedPtr<FJsonObject> JsonObject);
	void DumpMetaData(TSharedPtr<FJsonObject> JsonObject);
	

	static FString SerializeJsonContent(const TMap<FString, FString>& Params);
};
#pragma endregion
/*-------------------------------------------------------------------------*/