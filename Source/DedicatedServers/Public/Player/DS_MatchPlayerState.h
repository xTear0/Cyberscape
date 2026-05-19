// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DS_MatchPlayerState.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UDS_GameStatsManager;
struct FDS_RecordMatchStatsInput;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_MatchPlayerState.h_Class
UCLASS()
class DEDICATEDSERVERS_API ADS_MatchPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void OnMatchEnded(const FString& Username);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_GameStatsManager> GameStatsManagerClass;


protected:
	virtual void BeginPlay() override;
	void RecordMatchStats(const FDS_RecordMatchStatsInput& RecordMatchStatsInput);

private:
	UPROPERTY()
	TObjectPtr<UDS_GameStatsManager> GameStatsManager;
};
#pragma endregion
/*-------------------------------------------------------------------------*/