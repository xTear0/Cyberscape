// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Lobby/DS_LobbyPlayerInfo.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_LobbyPlayerInfo.cpp_Functions
void FDS_LobbyPlayerInfoArray::AddPlayer(const FDS_LobbyPlayerInfo& NewPlayerInfo)
{
	int32 Index = Players.Add(NewPlayerInfo);
	MarkItemDirty(Players[Index]);
	Players[Index].PostReplicatedAdd(*this);
}

void FDS_LobbyPlayerInfoArray::RemovePlayer(const FString& Username)
{
	for (int32 PlayerIndex = 0; PlayerIndex < Players.Num(); ++PlayerIndex)
	{
		FDS_LobbyPlayerInfo& PlayerInfo = Players[PlayerIndex];
		if (PlayerInfo.Username == Username)
		{
			PlayerInfo.PreReplicatedRemove(*this);
			Players.RemoveAtSwap(PlayerIndex);
			MarkArrayDirty();
			break;
		}
	}
}

void FDS_LobbyPlayerInfoArray::UpdatePlayer(const FString& Username, const int32 Kills, const int32 Deaths,
	const int32 Accuracy, const int32 HighestKillStreak)
{
	for (int32 PlayerIndex = 0; PlayerIndex < Players.Num(); ++PlayerIndex)
	{
		FDS_LobbyPlayerInfo& PlayerInfo = Players[PlayerIndex];
		if (PlayerInfo.Username == Username)
		{
			PlayerInfo.Kills = Kills;
			PlayerInfo.Deaths = Deaths;
			PlayerInfo.Accuracy = Accuracy;
			PlayerInfo.HighestKillStreak = HighestKillStreak;

			MarkItemDirty(PlayerInfo);
			break;
		}
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/