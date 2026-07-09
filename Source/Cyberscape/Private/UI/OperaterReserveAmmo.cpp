// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/OperaterReserveAmmo.h"

#include "Character/OperatorCharacter.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Weapon/Weapon.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region OperaterReserveAmmo.cpp_Functions
void UOperaterReserveAmmo::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Image_WeaponIcon->SetRenderOpacity(0.f);
	Text_Ammo->SetRenderOpacity(0.f);

	GetOwningPlayer()->OnPossessedPawnChanged.AddDynamic(this, &ThisClass::OnPossessedPawnChanged);
	
	AOperatorCharacter* OperatorCharacter = Cast<AOperatorCharacter>(GetOwningPlayer()->GetPawn());
	if (!IsValid(OperatorCharacter)) return;

	OnPossessedPawnChanged(nullptr, OperatorCharacter);

	if (OperatorCharacter->HasWeaponFirstReplicated())
	{
		AWeapon* Weapon = IPlayerInterface::Execute_GetCurrentWeapon(OperatorCharacter);
		if (IsValid(Weapon))
		{
			// Reserve Ammo amount for the current weapon, also need CurrentCeapon->Ammo.
			OnCurrentReserveAmmoChanged(
				IPlayerInterface::Execute_GetReserveAmmo(OperatorCharacter), Weapon->Ammo);
		}
	} else
	{
		OperatorCharacter->OnWeaponFirstReplicated.AddDynamic(this, &ThisClass::OnWeaponFirstReplicated);
	}

	if (OperatorCharacter->HasAuthority())
	{
		AWeapon* Weapon = IPlayerInterface::Execute_GetCurrentWeapon(OperatorCharacter);
		if (IsValid(Weapon))
		{
			OnCurrentReserveAmmoChanged(
				IPlayerInterface::Execute_GetReserveAmmo(OperatorCharacter), Weapon->Ammo);
		}
	}
}

void UOperaterReserveAmmo::OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	// Unbind from Delegates on the OldPawn,
	UOperatorCombatComponent* OldPawnCombat = UOperatorCombatComponent::FindCombatComponent(OldPawn);
	if (IsValid(OldPawnCombat))
	{
		OldPawnCombat->OnCurrentWeaponReserveAmmoChanged.RemoveDynamic(this, &ThisClass::UOperaterReserveAmmo::OnCurrentReserveAmmoChanged);
		OldPawnCombat->OnRoundFired.RemoveDynamic(this, &ThisClass::OnRoundFired);
	}
	// Bind to Delegates on the Operator Combat Component
	UOperatorCombatComponent* NewPawnCombat = UOperatorCombatComponent::FindCombatComponent(NewPawn);
	if (IsValid(NewPawnCombat))
	{
		Image_WeaponIcon->SetRenderOpacity(1.f);
		Text_Ammo->SetRenderOpacity(1.f);
		NewPawnCombat->OnCurrentWeaponReserveAmmoChanged.AddDynamic(this, &ThisClass::OnCurrentReserveAmmoChanged);
		NewPawnCombat->OnRoundFired.AddDynamic(this, &ThisClass::OnRoundFired);
	}
}

void UOperaterReserveAmmo::OnCurrentReserveAmmoChanged(int32 RoundsInReserve, int32 RoundsInWeapon)
{
	// TODO: Change Weapon Icon
	
	// RoundsInWeapon / RoundsInReserve
	if (IsValid(Text_Ammo))
	{
		FText AmmoText = FText::Format(NSLOCTEXT("AmmoText", "AmmoKey", "{0}/{1}"), RoundsInWeapon, RoundsInReserve);
		Text_Ammo->SetText(AmmoText);
	}
}

void UOperaterReserveAmmo::OnRoundFired(int32 RoundsCurrent, int32 RoundsMax, int32 RoundsInReserve)
{
	if (IsValid(Text_Ammo))
	{
		FText AmmoText = FText::Format(NSLOCTEXT("AmmoText", "AmmoKey", "{0}/{1}"), RoundsCurrent, RoundsInReserve);
		Text_Ammo->SetText(AmmoText);
	}
}

void UOperaterReserveAmmo::OnWeaponFirstReplicated(AWeapon* Weapon, bool bTargetingPlayer)
{
	AOperatorCharacter* OperatorCharacter = Cast<AOperatorCharacter>(GetOwningPlayer()->GetPawn());
	if (!IsValid(OperatorCharacter)) return;
	OnCurrentReserveAmmoChanged(
		IPlayerInterface::Execute_GetReserveAmmo(OperatorCharacter), Weapon->Ammo);
}
#pragma endregion
/*-------------------------------------------------------------------------*/

