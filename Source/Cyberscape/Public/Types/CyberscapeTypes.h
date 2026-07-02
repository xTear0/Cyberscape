// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CyberscapeTypes.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region OperatorCharacter.cpp_Functions
UENUM(BlueprintType)
enum class ETurningInPlace : uint8
{
	Left		UMETA(DisplayName = "TurningLeft"),
	Right		UMETA(DisplayName = "TurningRight"),
	NotTurning	UMETA(DisplayName = "NotTurning")
};
#pragma endregion
/*-------------------------------------------------------------------------*/