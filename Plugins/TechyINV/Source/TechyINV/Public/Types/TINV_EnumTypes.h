// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "TINV_EnumTypes.generated.h"
/*-------------------------------------------------------------------------*/


UENUM(BlueprintType)
enum class ETINV_ItemTier : uint8
{
	Scrap,
	Tier1,
	Tier2,
	Tier3,
	Tier4,
	Tier5,
	Prem
};

UENUM(BlueprintType)
enum class ETINV_ContainerRarity : uint8
{
	Standard,
	Rare,
	Legendary,
	Omega
};

UENUM(BlueprintType)
enum class ETINV_ContainerGrade : uint8
{
	Grade_I,
	Grade_II,
	Grade_III,
	Grade_V,
	Grade_X
};

UENUM(BlueprintType)
enum class ETINV_WeaponFireType : uint8
{
	Automatic,
	Semiauto,
	Burst,
	BoltAction,
	ChargeUp
};

UENUM(BlueprintType)
enum class ETINV_WeaponDamageType : uint8
{
	Kinetic,
	Energy,
	Hazchem,
	Atomic,
	Missile,
	Burn,
	Plasma,
	Gravity
};
