// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "DS_LobbyPlayerInfo.h"
#include "GameFramework/Info.h"
#include "DS_LobbyState.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
struct FDS_LobbyPlayerInfoArray;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInfoChanged, const FDS_LobbyPlayerInfo&, PlayerInfo);

USTRUCT()
struct FDS_LobbyPlayerInfoDelta
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FDS_LobbyPlayerInfo> AddedPlayers{};

	UPROPERTY()
	TArray<FDS_LobbyPlayerInfo> RemovedPlayers{};
};
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_LobbyState.h_Class


UCLASS()
class DEDICATEDSERVERS_API ADS_LobbyState : public AInfo
{
	GENERATED_BODY()
public:
	ADS_LobbyState();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerInfoChanged OnPlayerInfoAdded;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerInfoChanged OnPlayerInfoRemoved;

	void AddPlayerInfo(const FDS_LobbyPlayerInfo& PlayerInfo);
	void RemovePlayerInfo(const FString& Username);
	
	TArray<FDS_LobbyPlayerInfo> GetPlayers() const;

	FDS_LobbyPlayerInfoArray& GetPlayerArray() { return PlayerInfoArray; }
	
protected:

	UFUNCTION()
	void OnRep_LobbyPlayerInfo();

private:

	UPROPERTY(ReplicatedUsing=OnRep_LobbyPlayerInfo)
	FDS_LobbyPlayerInfoArray PlayerInfoArray;

	UPROPERTY()
	FDS_LobbyPlayerInfoArray LastPlayerInfoArray;

	FDS_LobbyPlayerInfoDelta ComputeInfoDelta(const TArray<FDS_LobbyPlayerInfo>& OldArray, const TArray<FDS_LobbyPlayerInfo>& NewArray); 
};
#pragma endregion
/*-------------------------------------------------------------------------*/