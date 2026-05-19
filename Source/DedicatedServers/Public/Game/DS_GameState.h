// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DS_GameState.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class ADS_LobbyState;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLobbyStateInitialized, ADS_LobbyState*, LobbyState);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_GameState.h_Class
UCLASS()
class DEDICATEDSERVERS_API ADS_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ADS_GameState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_LobbyState)
	TObjectPtr<ADS_LobbyState> LobbyState;

	UPROPERTY(BlueprintAssignable)
	FOnLobbyStateInitialized OnLobbyStateInitialized;
	
protected:
	virtual void BeginPlay() override;
	void CreateLobbyState();
	
private:
	UFUNCTION()
	void OnRep_LobbyState();
};
#pragma endregion
/*-------------------------------------------------------------------------*/