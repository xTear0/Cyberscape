// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "DS_GameModeBase.h"
#include "DS_MatchGameMode.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UDS_GameStatsManager;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_MatchGameMode.h_Class
UCLASS()
class DEDICATEDSERVERS_API ADS_MatchGameMode : public ADS_GameModeBase
{
	GENERATED_BODY()
public:
	ADS_MatchGameMode();

	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void Logout(AController* Exiting) override;
	virtual void InitSeamlessTravelPlayer(AController* NewController) override;
	
	UPROPERTY(BlueprintReadOnly)
	EDS_MatchStatus MatchStatus;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_GameStatsManager> GameStatsManagerClass;

protected:
	virtual void OnCountdownTimerFinished(EDS_CountdownTimerType Type) override;
	
	UPROPERTY(EditDefaultsOnly)
	FDS_CountdownTimerHandle PreMatchTimer;

	UPROPERTY(EditDefaultsOnly)
	FDS_CountdownTimerHandle MatchTimer;

	UPROPERTY(EditDefaultsOnly)
	FDS_CountdownTimerHandle PostMatchTimer;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> LobbyMap;

	void SetClientInputEnabled(bool bEnabled);
	void OnMatchEnded();
	void OnMatchStarted();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDS_GameStatsManager> GameStatsManager;
};
#pragma endregion
/*-------------------------------------------------------------------------*/