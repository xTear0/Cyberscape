// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "Net/Serialization/FastArraySerializer.h"
#include "DS_LobbyPlayerInfo.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_MULTICAST_DELEGATE(FOnPlayerInfoArrayUpdated);


USTRUCT()
struct FDS_LobbyPlayerInfo : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FDS_LobbyPlayerInfo() {}

	// Construct with simple name
	explicit FDS_LobbyPlayerInfo(const FString& Name) : Username(Name) {}

	// Construct with full player data
	FDS_LobbyPlayerInfo(const FString& Name, const FString& Rank, const int32 Level) : Username(Name), Rank(Rank), Level(Level) {}
	
	UPROPERTY()	FString Username{};
	UPROPERTY() FString Rank{};
	UPROPERTY() int32 Level{};
	UPROPERTY()	int32 Kills{};
	UPROPERTY()	int32 Deaths{};
	UPROPERTY()	float Accuracy{};
	UPROPERTY()	int32 HighestKillStreak{};
};

USTRUCT()
struct FDS_LobbyPlayerInfoArray : public FFastArraySerializer
{
	GENERATED_BODY()

	FOnPlayerInfoArrayUpdated OnArrayUpdated;	
	
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
	{
		OnArrayUpdated.Broadcast();
	}

	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
	{
		OnArrayUpdated.Broadcast();
	}

	void PostReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
	{
		OnArrayUpdated.Broadcast();
	}

	
	UPROPERTY()
	TArray<FDS_LobbyPlayerInfo> Players;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FastArrayDeltaSerialize<FDS_LobbyPlayerInfo, FDS_LobbyPlayerInfoArray>
		(Players, DeltaParams, *this);
	}

	void AddPlayer(const FDS_LobbyPlayerInfo& NewPlayerInfo);
	void RemovePlayer(const FString& Username);
	void UpdatePlayer(const FString& Username, const int32 Kills, const int32 Deaths, const int32 Accuracy, const int32 HighestKillStreak);
};

template<>
struct TStructOpsTypeTraits<FDS_LobbyPlayerInfoArray> : public TStructOpsTypeTraitsBase2<FDS_LobbyPlayerInfoArray>
{
	enum
	{
		WithNetDeltaSerialize = true
	};
};
/*-------------------------------------------------------------------------*/