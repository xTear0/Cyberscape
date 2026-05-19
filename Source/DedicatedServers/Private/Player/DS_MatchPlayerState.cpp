// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Player/DS_MatchPlayerState.h"
#include "Game/DS_LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "Lobby/DS_LobbyState.h"
#include "UI/GameStats/DS_GameStatsManager.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_MatchPlayerState.cpp_Functions
void ADS_MatchPlayerState::OnMatchEnded(const FString& Username)
{
	
}

void ADS_MatchPlayerState::BeginPlay()
{
	Super::BeginPlay();

	GameStatsManager = NewObject<UDS_GameStatsManager>(this, GameStatsManagerClass);
}

void ADS_MatchPlayerState::RecordMatchStats(const FDS_RecordMatchStatsInput& RecordMatchStatsInput)
{
	check(IsValid(GameStatsManager));
	GameStatsManager->RecordMatchStats(RecordMatchStatsInput);
}
#pragma endregion
/*-------------------------------------------------------------------------*/