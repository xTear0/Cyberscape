// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Combat/OperatorCombatComponent.h"
#include "Data/WeaponData.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/PlayerInterface.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/Weapon.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region OperatorCombatComponent.cpp_Functions
UOperatorCombatComponent::UOperatorCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UOperatorCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UOperatorCombatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UOperatorCombatComponent, Inventory);
	DOREPLIFETIME(UOperatorCombatComponent, CurrentWeapon);
	DOREPLIFETIME_CONDITION(UOperatorCombatComponent, bAiming, COND_SkipOwner);
}

void UOperatorCombatComponent::Initiate_CycleWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Initiate_CycleWeapon"), false);
}

void UOperatorCombatComponent::Initiate_FireWeapon_Pressed()
{
	Local_FireWeapon();
}

void UOperatorCombatComponent::Local_FireWeapon()
{
	// Locally, play the Anim Montage for firing the weapon.
	ensure(IsValid(WeaponData));
	UAnimMontage* Montage1P = WeaponData->FirstPersonMontages.FindChecked(CurrentWeapon->WeaponType).FireMontage;
	USkeletalMeshComponent* Mesh1P = IPlayerInterface::Execute_GetMesh1P(GetOwner());

	if (IsValid(Mesh1P) && IsValid(Montage1P))
	{
		Mesh1P->GetAnimInstance()->Montage_Play(Montage1P);
	}

	// Tell the Server to fire the weapon.
	Server_FireWeapon();
	
}

void UOperatorCombatComponent::Server_FireWeapon_Implementation()
{
	Multicast_FireWeapon();
}

void UOperatorCombatComponent::Multicast_FireWeapon_Implementation()
{
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (OwningPawn->IsLocallyControlled())
	{
		// Do locally controlled stuff here.
	}
	else
	{
		ensure(IsValid(WeaponData));
		UAnimMontage* Montage3P = WeaponData->ThirdPersonMontages.FindChecked(CurrentWeapon->WeaponType).FireMontage;
		USkeletalMeshComponent* Mesh3P = IPlayerInterface::Execute_GetMesh3P(GetOwner());

		if (IsValid(Mesh3P) && IsValid(Montage3P))
		{
			Mesh3P->GetAnimInstance()->Montage_Play(Montage3P);
		} 
	}
}

void UOperatorCombatComponent::Initiate_FireWeapon_Released()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Initiate_FireWeapon_Released"), false);
}

void UOperatorCombatComponent::Initiate_ReloadWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Initiate_ReloadWeapon"), false);
}

void UOperatorCombatComponent::Initiate_Aim_Pressed()
{
	Local_Aim(true);
	Server_Aim(true);
}

void UOperatorCombatComponent::Initiate_Aim_Released()
{
	Local_Aim(false);
	Server_Aim(false);
}

void UOperatorCombatComponent::Server_Aim_Implementation(bool bPressed)
{
	Local_Aim(bPressed);
}

void UOperatorCombatComponent::Local_Aim(bool bPressed)
{
	bAiming = bPressed;
}


void UOperatorCombatComponent::Equip(AWeapon* Weapon)
{
	CurrentWeapon = Weapon;
	CurrentWeapon->AttachToOwningPawn();
}

void UOperatorCombatComponent::SpawnInventory()
{
	if (GetOwner()->GetLocalRole() < ROLE_Authority) return;
	
	for (TSubclassOf<AWeapon>& WeaponClass : DefaultWeaponClasses)
	{
		AWeapon* Weapon = SpawnWeapon(WeaponClass);
		Inventory.AddUnique(Weapon); // TODO: Ensure we want a unique weapon. What if the player has 2?
	}

	if (Inventory.Num() > 0)
	{
		Equip(Inventory[0]);
	}
}

void UOperatorCombatComponent::DestroyInventory()
{
	for (AWeapon* Weapon : Inventory)
	{
		if (IsValid(Weapon))
		{
			Weapon->Destroy();
		}
	}
}

void UOperatorCombatComponent::OnRep_CurrentWeapon(AWeapon* LastWeapon)
{
	if (!IsValid(CurrentWeapon)) return;
	CurrentWeapon->AttachToOwningPawn();
}

AWeapon* UOperatorCombatComponent::SpawnWeapon(TSubclassOf<AWeapon> WeaponClass) const
{
	AActor* OwningActor = GetOwner();
	if (!IsValid(OwningActor)) return nullptr;
	if (OwningActor->GetLocalRole() < ROLE_Authority) return nullptr;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = Cast<APawn>(OwningActor);
	SpawnInfo.Owner = OwningActor;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return GetWorld()->SpawnActor<AWeapon>(WeaponClass, SpawnInfo);
}




#pragma endregion
/*-------------------------------------------------------------------------*/