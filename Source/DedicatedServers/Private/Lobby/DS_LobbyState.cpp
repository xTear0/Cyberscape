// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Lobby/DS_LobbyState.h"
#include "Net/UnrealNetwork.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_LobbyState.cpp_Functions
ADS_LobbyState::ADS_LobbyState()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bAlwaysRelevant = true;
}

void ADS_LobbyState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADS_LobbyState, PlayerInfoArray);
}

void ADS_LobbyState::AddPlayerInfo(const FDS_LobbyPlayerInfo& PlayerInfo)
{
	PlayerInfoArray.AddPlayer(PlayerInfo);
}

void ADS_LobbyState::RemovePlayerInfo(const FString& Username)
{
	PlayerInfoArray.RemovePlayer(Username);
}

TArray<FDS_LobbyPlayerInfo> ADS_LobbyState::GetPlayers() const
{
	return PlayerInfoArray.Players;
}

void ADS_LobbyState::OnRep_LobbyPlayerInfo()
{
	FDS_LobbyPlayerInfoDelta Delta = ComputeInfoDelta(LastPlayerInfoArray.Players, PlayerInfoArray.Players);
	for (const auto& PlayerInfo : Delta.AddedPlayers)
	{
		OnPlayerInfoAdded.Broadcast(PlayerInfo);
	}
	for (const auto& PlayerInfo : Delta.RemovedPlayers)
	{
		OnPlayerInfoRemoved.Broadcast(PlayerInfo);
	}
	
	LastPlayerInfoArray = PlayerInfoArray;
}

FDS_LobbyPlayerInfoDelta ADS_LobbyState::ComputeInfoDelta(const TArray<FDS_LobbyPlayerInfo>& OldArray,
	const TArray<FDS_LobbyPlayerInfo>& NewArray)
{
	FDS_LobbyPlayerInfoDelta Delta;

	TMap<FString, const FDS_LobbyPlayerInfo*> OldMap;
	TMap<FString, const FDS_LobbyPlayerInfo*> NewMap;

	// Populate the old array.
	for (const auto& PlayerInfo	: OldArray)
	{
		OldMap.Add(PlayerInfo.Username, &PlayerInfo);
	}

	// Populate the new array.
	for (const auto& PlayerInfo	: NewArray)
	{
		NewMap.Add(PlayerInfo.Username, &PlayerInfo);
	}

	// Check to see the differences between the delta:
	for (const auto& OldPlayerInfo : OldArray)
	{
		if (!NewMap.Contains(OldPlayerInfo.Username)) // One of the players has been removed.
		{
			Delta.RemovedPlayers.Add(OldPlayerInfo);
		}
	}

	for (const auto& NewPlayerInfo : NewArray)
	{
		if (!OldMap.Contains(NewPlayerInfo.Username)) // One of the players has been added.
		{
			Delta.AddedPlayers.Add(NewPlayerInfo);
		}
	}
	
	return Delta;
}
#pragma endregion
/*-------------------------------------------------------------------------*/