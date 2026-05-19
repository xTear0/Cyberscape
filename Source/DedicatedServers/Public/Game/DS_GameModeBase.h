// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Types/DS_StructTypes.h"
#include "DS_GameModeBase.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_GameModeBase.h_Class
UCLASS()
class DEDICATEDSERVERS_API ADS_GameModeBase : public AGameMode
{
	GENERATED_BODY()

protected:
	void StartCountdownTimer(FDS_CountdownTimerHandle& CountdownTimerHandle);
	void StopCountdownTimer(FDS_CountdownTimerHandle& CountdownTimerHandle);
	virtual void OnCountdownTimerFinished(EDS_CountdownTimerType Type);
	void UpdateCountdownTimer(const FDS_CountdownTimerHandle& CountdownTimerHandle);
	void TrySeamlessTravel(const TSoftObjectPtr<UWorld>& DestinationMap);

	void RemovePlayerSession(AController* Exiting);
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/