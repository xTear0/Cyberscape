// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "DS_EnumTypes.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
UENUM(BlueprintType)
enum class EDS_CountdownTimerState : uint8
{
	NotStarted,
	Started,
	Paused,
	Stopped
};

UENUM()
enum class EDS_MatchStatus : uint8
{
	WaitingForPlayers,
	PreMatch,
	Match,
	PostMatch,
	SeamlessTraveling
};

UENUM()
enum class EDS_LobbyStatus : uint8
{
	WaitingForPlayers,
	CountdownToSeamlessTravel,
	SeamlessTraveling
};

UENUM(BlueprintType)
enum class EDS_CountdownTimerType : uint8
{
	LobbyCountdown,
	PreMatch,
	Match,
	PostMatch,
	None
};

UENUM(BlueprintType)
enum class EDS_DelegateResponse : uint8
{
	BroadcastClick,
	ResponseSuccess,
	ResponseSuccessSuper,
	ResponseError,
	ResponseErrorCritical,
	ResponseNextStep,
	Null,
};
/*-------------------------------------------------------------------------*/