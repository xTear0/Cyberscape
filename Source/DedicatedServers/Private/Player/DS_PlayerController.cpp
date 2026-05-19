// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Player/DS_PlayerController.h"
#include "Game/DS_LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Lobby/DS_LobbyState.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_PlayerController.cpp_Functions
ADS_PlayerController::ADS_PlayerController()
{
	SingleTripTime = 0.f;

	PlayerUsername = "";
	PlayerSessionId = "";
}

void ADS_PlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	
	if (GetNetMode() == NM_Standalone) return;

	if (IsLocalController())
	{
		Server_Ping(GetWorld()->GetTimeSeconds());
	}
}

void ADS_PlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (IsLocalController())
	{
		DisableInput(this);
	}
}

void ADS_PlayerController::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();

	if (IsLocalController())
	{
		Server_Ping(GetWorld()->GetTimeSeconds());
		DisableInput(this);
	}
}

void ADS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() == NM_Standalone)
	{
		DisableInput(this);
	}

	
}

void ADS_PlayerController::SetUsernameAndPlayerSessionId(const FString& InUsername, const FString& InPlayerSessionId)
{
	PlayerUsername = InUsername;
	PlayerSessionId = InPlayerSessionId;
	if (APlayerState* PS = GetPlayerState<APlayerState>())
	{
		PS->SetPlayerName(InUsername);
	}
}

void ADS_PlayerController::Client_SetInputEnabled_Implementation(bool bEnabled)
{
	if (bEnabled)
	{
		EnableInput(this);
	} else
	{
		DisableInput(this);
	}
}

void ADS_PlayerController::Client_TimerUpdated_Implementation(float CountdownTimeLeft, EDS_CountdownTimerType Type) const
{
	OnTimerUpdated.Broadcast(CountdownTimeLeft - SingleTripTime, Type);
}

void ADS_PlayerController::Client_TimerStopped_Implementation(float CountdownTimeLeft, EDS_CountdownTimerType Type) const
{
	OnTimerStopped.Broadcast(CountdownTimeLeft - SingleTripTime, Type);
}

void ADS_PlayerController::Server_Ping_Implementation(float TimeOfRequest)
{
	Client_Pong(TimeOfRequest);
}

void ADS_PlayerController::Client_Pong_Implementation(float TimeOfRequest)
{
	const float RoundTripTime = GetWorld()->GetTimeSeconds() - TimeOfRequest;
	SingleTripTime = RoundTripTime * 0.5f;
}
#pragma endregion
/*-------------------------------------------------------------------------*/
