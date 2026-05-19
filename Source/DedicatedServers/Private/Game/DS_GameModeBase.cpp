// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Game/DS_GameModeBase.h"
#if WITH_GAMELIFT
#include "aws/gamelift/server/GameLiftServerAPI.h"
#endif
#include "Kismet/GameplayStatics.h"
#include "Player/DS_PlayerController.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_GameModeBase.cpp_Functions
void ADS_GameModeBase::StartCountdownTimer(FDS_CountdownTimerHandle& CountdownTimerHandle)
{
	CountdownTimerHandle.TimerFinishedDelegate.BindWeakLambda(this, [&]()
	{
		OnCountdownTimerFinished(CountdownTimerHandle.Type);
	});

	GetWorldTimerManager().SetTimer(
	CountdownTimerHandle.TimerFinishedHandle,
	CountdownTimerHandle.TimerFinishedDelegate,
	CountdownTimerHandle.CountdownTime,
	false);

	CountdownTimerHandle.TimerUpdateDelegate.BindWeakLambda(this, [&]()
	{	
		UpdateCountdownTimer(CountdownTimerHandle);
	});

	GetWorldTimerManager().SetTimer(
		CountdownTimerHandle.TimerUpdateHandle,
		CountdownTimerHandle.TimerUpdateDelegate,
		CountdownTimerHandle.CountdownUpdateInterval,
		true);
	UpdateCountdownTimer(CountdownTimerHandle);
}

void ADS_GameModeBase::StopCountdownTimer(FDS_CountdownTimerHandle& CountdownTimerHandle)
{
	CountdownTimerHandle.State = EDS_CountdownTimerState::Stopped;
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle.TimerFinishedHandle);
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle.TimerUpdateHandle);

	if (CountdownTimerHandle.TimerFinishedDelegate.IsBound())
	{
		CountdownTimerHandle.TimerFinishedDelegate.Unbind();
	}

	if (CountdownTimerHandle.TimerUpdateDelegate.IsBound())
	{
		CountdownTimerHandle.TimerUpdateDelegate.Unbind();
	}

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		ADS_PlayerController* DS_PlayerController = Cast<ADS_PlayerController>(Iterator->Get());
		if (IsValid(DS_PlayerController))
		{
			DS_PlayerController->Client_TimerStopped(0.f, CountdownTimerHandle.Type);	
		}
	}
}

void ADS_GameModeBase::OnCountdownTimerFinished(EDS_CountdownTimerType Type)
{
	
}

void ADS_GameModeBase::UpdateCountdownTimer(const FDS_CountdownTimerHandle& CountdownTimerHandle)
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		ADS_PlayerController* DS_PlayerController = Cast<ADS_PlayerController>(Iterator->Get());
		if (IsValid(DS_PlayerController))
		{
			const float CountdownTimeLeft = CountdownTimerHandle.CountdownTime - GetWorldTimerManager().GetTimerElapsed(
				CountdownTimerHandle.TimerFinishedHandle);
			DS_PlayerController->Client_TimerUpdated(CountdownTimeLeft, CountdownTimerHandle.Type);
		}
	}
}

void ADS_GameModeBase::TrySeamlessTravel(const TSoftObjectPtr<UWorld>& DestinationMap)
{
	const FString MapName = DestinationMap.ToSoftObjectPath().GetAssetName();

	
	GetWorld()->ServerTravel(MapName);
	
	/*if (GIsEditor)
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, DestinationMap);
	} else
	{
		GetWorld()->ServerTravel(MapName);
	}*/
}

void ADS_GameModeBase::RemovePlayerSession(AController* Exiting)
{
	if (ADS_PlayerController* DS_PlayerController = Cast<ADS_PlayerController>(Exiting))
	{
		if (!IsValid(DS_PlayerController)) return;
#if WITH_GAMELIFT
		const FString& PlayerSessionId = DS_PlayerController->PlayerSessionId;
		if (!PlayerSessionId.IsEmpty())
		{
			Aws::GameLift::Server::RemovePlayerSession(TCHAR_TO_ANSI(*PlayerSessionId));
		}
#endif
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/

