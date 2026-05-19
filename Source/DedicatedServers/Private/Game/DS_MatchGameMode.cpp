// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Game/DS_MatchGameMode.h"
//#include "Game/MatchGameState.h"
//#include "Player/MatchPlayerState.h"
#include "Player/DS_MatchPlayerState.h"
#include "Player/DS_PlayerController.h"
#include "UI/GameStats/DS_GameStatsManager.h"
#include "UI/HTTP/DS_HTTPRequestTypes.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_MatchGameMode.cpp_Functions
class AMatchGameState;

ADS_MatchGameMode::ADS_MatchGameMode()
{
	bUseSeamlessTravel = true;
	MatchStatus = EDS_MatchStatus::WaitingForPlayers;
	PreMatchTimer.Type = EDS_CountdownTimerType::PreMatch;
	MatchTimer.Type = EDS_CountdownTimerType::Match;
	PostMatchTimer.Type = EDS_CountdownTimerType::PostMatch;
}

void ADS_MatchGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (MatchStatus == EDS_MatchStatus::WaitingForPlayers)
	{
		MatchStatus = EDS_MatchStatus::PreMatch;
		StartCountdownTimer(PreMatchTimer);
	}

	if (MatchStatus == EDS_MatchStatus::Match)
	{
		SetClientInputEnabled(true);
	}
}

void ADS_MatchGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	RemovePlayerSession(Exiting);
}

void ADS_MatchGameMode::InitSeamlessTravelPlayer(AController* NewController)
{
	Super::InitSeamlessTravelPlayer(NewController);

	if (MatchStatus == EDS_MatchStatus::WaitingForPlayers)
	{
		MatchStatus = EDS_MatchStatus::PreMatch;
		StartCountdownTimer(PreMatchTimer);
	}
}

void ADS_MatchGameMode::OnCountdownTimerFinished(EDS_CountdownTimerType Type)
{
	Super::OnCountdownTimerFinished(Type);
	
	if (Type == EDS_CountdownTimerType::PreMatch)
	{
		StopCountdownTimer(PreMatchTimer);
		MatchStatus = EDS_MatchStatus::Match;
		StartCountdownTimer(MatchTimer);
		SetClientInputEnabled(true);
	}
	if (Type == EDS_CountdownTimerType::Match)
	{
		StopCountdownTimer(MatchTimer);
		MatchStatus = EDS_MatchStatus::PostMatch;
		StartCountdownTimer(PostMatchTimer);
		SetClientInputEnabled(false);
		OnMatchEnded();
	}
	if (Type == EDS_CountdownTimerType::PostMatch)
	{
		StopCountdownTimer(PostMatchTimer);
		MatchStatus = EDS_MatchStatus::SeamlessTraveling;
		TrySeamlessTravel(LobbyMap);
	}
}

void ADS_MatchGameMode::SetClientInputEnabled(bool bEnabled)
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		ADS_PlayerController* DS_PlayerController = Cast<ADS_PlayerController>(Iterator->Get());
		if (IsValid(DS_PlayerController))
		{
			DS_PlayerController->Client_SetInputEnabled(bEnabled);
		}
	}
}

void ADS_MatchGameMode::OnMatchEnded()
{
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        if (ADS_PlayerController* DS_PlayerController = Cast<ADS_PlayerController>(Iterator->Get());!IsValid(DS_PlayerController))
        {
	        if (ADS_MatchPlayerState* MatchPlayerState = DS_PlayerController->GetPlayerState<ADS_MatchPlayerState>(); IsValid(MatchPlayerState))
	        {
	        	MatchPlayerState->OnMatchEnded(DS_PlayerController->PlayerUsername);
	        }
        }
    }
}

void ADS_MatchGameMode::OnMatchStarted()
{
	// If needed, its here.
}
#pragma endregion
/*-------------------------------------------------------------------------*/

