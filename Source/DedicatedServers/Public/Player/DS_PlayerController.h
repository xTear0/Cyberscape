// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Lobby/DS_LobbyPlayerInfo.h"
#include "Types/DS_EnumTypes.h"
#include "DS_PlayerController.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDS_OnTimerStateChangedDelegate, float, Time, EDS_CountdownTimerType, Type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDS_OnUpdatePlayerArray);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_PlayerController.h_Class
UCLASS()
class DEDICATEDSERVERS_API ADS_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADS_PlayerController();
	virtual void ReceivedPlayer() override;
	virtual void OnRep_PlayerState() override;
	virtual void PostSeamlessTravel() override;
	virtual void BeginPlay() override;
	
	UFUNCTION(Client, Reliable)
	void Client_TimerUpdated(float CountdownTimeLeft, EDS_CountdownTimerType Type) const;

	UFUNCTION(Client, Reliable)
	void Client_TimerStopped(float CountdownTimeLeft, EDS_CountdownTimerType Type) const;

	UFUNCTION(Client, Reliable)
	void Client_SetInputEnabled(bool bEnabled);

	void SetUsernameAndPlayerSessionId(const FString& InUsername, const FString& InPlayerSessionId);
	
	UPROPERTY(BlueprintAssignable)
	FDS_OnTimerStateChangedDelegate OnTimerUpdated;

	UPROPERTY(BlueprintAssignable)
	FDS_OnTimerStateChangedDelegate OnTimerStopped;

	UPROPERTY(BlueprintAssignable)
	FDS_OnUpdatePlayerArray OnUpdatePlayerArray;
	
	UPROPERTY(BlueprintReadOnly)
	FString PlayerUsername;

	UPROPERTY(BlueprintReadOnly)
	FString PlayerSessionId;
	
protected:
	UFUNCTION(Server, Reliable)
	void Server_Ping(float TimeOfRequest);

	UFUNCTION(Client, Reliable)
	void Client_Pong(float TimeOfRequest);
	
private:
	float SingleTripTime;
};
#pragma endregion
/*-------------------------------------------------------------------------*/