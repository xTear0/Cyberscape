// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "DS_GameModeBase.h"
#if WITH_GAMELIFT
#include "GameLiftServerSDK.h"
#include "GameLiftServerSDKModels.h"
#endif
#include "DS_LobbyGameMode.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UDS_GameInstanceSubsystem;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_LobbyGameMode.h_Class
UCLASS()
class DEDICATEDSERVERS_API ADS_LobbyGameMode : public ADS_GameModeBase
{
	GENERATED_BODY()

public:
	ADS_LobbyGameMode();
	void CheckAndStartLobbyCountdown();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnCountdownTimerFinished(EDS_CountdownTimerType Type) override;
	virtual void InitSeamlessTravelPlayer(AController* NewController) override;
	void CheckAndStopLobbyCountdown();
	virtual void Logout(AController* Exiting) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = L"") override;

	UPROPERTY(EditDefaultsOnly)
	int32 MinPlayers;
	
	UPROPERTY(BlueprintReadOnly)
	EDS_LobbyStatus LobbyStatus;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DestinationMap;
	
private:
	UPROPERTY()
	TObjectPtr<UDS_GameInstanceSubsystem> DS_GameInstanceSubsystem;

	UPROPERTY(EditDefaultsOnly)
	FDS_CountdownTimerHandle LobbyCountdownTimer;
	
#if WITH_GAMELIFT
	// This function tells the Game Instance Subsystem to Initialize GameLift
	// with the correct server parameters.
	void InitGameLift();
	void SetServerParameters(FServerParameters& OutServerParametersForAnywhere);
	
#endif

	void TryAcceptPlayerSession(const FString& PlayerSessionId, const FString& Username, FString& OutErrorMessage);
	void AddPlayerInfoToLobbyState(AController* Player) const;
	void RemovePlayerInfoFromLobbyState(AController* Player) const;

	
};
#pragma endregion
/*-------------------------------------------------------------------------*/