// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Combat/OperatorCombatComponent.h"
#include "Data/WeaponData.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/PlayerInterface.h"
#include "TimerManager.h"
#include "Cyberscape/Cyberscape.h"
#include "Kismet/KismetMathLibrary.h"
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

	TraceLength = 20'000.f;
	bAiming = false;
	bTriggerPressed = false;
}

void UOperatorCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (!IsValid(OwningPawn) || !OwningPawn->IsLocallyControlled()) return;
	
	APlayerController* PC = Cast<APlayerController>(OwningPawn->GetController());
	if (!IsValid(PC)) return;

	FVector EyesWorldLocation;
	FRotator EyesWorldRotation;

	PC->GetActorEyesViewPoint(EyesWorldLocation, EyesWorldRotation);
	const FVector EyesWorldDirection = UKismetMathLibrary::GetForwardVector(EyesWorldRotation);
	const FVector Start = EyesWorldLocation;
	const FVector End = Start + EyesWorldDirection * TraceLength;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	ResponseParams.CollisionResponse.SetResponse(ECC_PhysicsBody, ECR_Block);

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, CyberscapeTraceChannels::ECC_Weapon, QueryParams, ResponseParams);
	bHitPlayer = IsValid(HitResult.GetActor()) && HitResult.GetActor()->Implements<UPlayerInterface>();

	if (bHitPlayer != bHitPlayerLastFrame)
	{
		OnTargetingPlayerStatusChanged.Broadcast(bHitPlayer);
	}
	
	bHitPlayerLastFrame = bHitPlayer;
}

void UOperatorCombatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UOperatorCombatComponent, Inventory);
	DOREPLIFETIME(UOperatorCombatComponent, CurrentWeapon);
	DOREPLIFETIME_CONDITION(UOperatorCombatComponent, bAiming, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UOperatorCombatComponent, CurrentReserveAmmo, COND_OwnerOnly);
}

void UOperatorCombatComponent::Initiate_CycleWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Initiate_CycleWeapon"), false);
}

void UOperatorCombatComponent::Initiate_FireWeapon_Pressed()
{
	if (!IsValid(CurrentWeapon)) return;
	bTriggerPressed = true;

	if (CurrentWeapon->Ammo > 0)
	{
		Local_FireWeapon();
	}
}

void UOperatorCombatComponent::Local_FireWeapon()
{
	if (!IsValid(CurrentWeapon)) return;
	// Locally, play the Anim Montage for firing the weapon.
	ensure(IsValid(WeaponData));
	UAnimMontage* Montage1P = WeaponData->FirstPersonMontages.FindChecked(CurrentWeapon->WeaponType).FireMontage;
	USkeletalMeshComponent* Mesh1P = IPlayerInterface::Execute_GetMesh1P(GetOwner());

	if (IsValid(Mesh1P) && IsValid(Montage1P))
	{
		Mesh1P->GetAnimInstance()->Montage_Play(Montage1P);
	}

	FHitResult Hit;
	CurrentWeapon->WeaponTrace(Hit, TraceLength);
	EPhysicalSurface ImpactSurfaceType = Hit.PhysMaterial.IsValid(false) ? Hit.PhysMaterial->SurfaceType.GetValue() : SurfaceType1;
	CurrentWeapon->Local_Fire(Hit.ImpactPoint, Hit.ImpactNormal, ImpactSurfaceType, true);

	GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ThisClass::FireTimerFinished, CurrentWeapon->FireTime);

	OnRoundFired.Broadcast(CurrentWeapon->Ammo, CurrentWeapon->MagCapacity, CurrentReserveAmmo);
	// Tell the Server to fire the weapon.
	Server_FireWeapon(Hit);
}

void UOperatorCombatComponent::FireTimerFinished()
{
	if (!IsValid(CurrentWeapon)) return;

	if (bTriggerPressed && CurrentWeapon->FireType == EFireType::Auto && CurrentWeapon->Ammo > 0)
	{
		Local_FireWeapon();
	}
}

void UOperatorCombatComponent::Server_FireWeapon_Implementation(const FHitResult& Hit)
{
	if (!IsValid(CurrentWeapon)) return;
	if (GetNetMode() != NM_DedicatedServer || !Cast<APawn>(GetOwner())->IsLocallyControlled())
	{
		CurrentWeapon->Auth_Fire();
	}
	
	Multicast_FireWeapon(Hit, CurrentWeapon->Ammo);
}

void UOperatorCombatComponent::Multicast_FireWeapon_Implementation(const FHitResult& Hit, int32 AuthAmmo)
{
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (OwningPawn->IsLocallyControlled())
	{
		CurrentWeapon->Rep_Fire(AuthAmmo);
	}
	else
	{
		ensure(IsValid(WeaponData));
		
		EPhysicalSurface ImpactSurfaceType = SurfaceType1;
		if (Hit.PhysMaterial.IsValid())
		{
			if (UPhysicalMaterial* PhysMat = Hit.PhysMaterial.Get())
			{
				ImpactSurfaceType = PhysMat->SurfaceType.GetValue();
			}
		}
		
		CurrentWeapon->Local_Fire(Hit.ImpactPoint, Hit.ImpactNormal, ImpactSurfaceType, false);
		
		UAnimMontage* Montage3P = WeaponData->ThirdPersonMontages.FindChecked(CurrentWeapon->WeaponType).FireMontage;

		if (USkeletalMeshComponent* Mesh3P = IPlayerInterface::Execute_GetMesh3P(GetOwner()); IsValid(Mesh3P) && IsValid(Montage3P))
		{
			Mesh3P->GetAnimInstance()->Montage_Play(Montage3P);
		} 
	}
}

void UOperatorCombatComponent::Initiate_FireWeapon_Released()
{
	bTriggerPressed = false;
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

void UOperatorCombatComponent::OnRep_CurrentReserveAmmo()
{
	if (IsValid(CurrentWeapon))
	{
		OnCurrentWeaponReserveAmmoChanged.Broadcast(CurrentReserveAmmo, CurrentWeapon->Ammo); 
	}
}

void UOperatorCombatComponent::Local_Aim(bool bPressed)
{
	bAiming = bPressed;
	OnAimingStatusChanged.Broadcast(bAiming);
}


void UOperatorCombatComponent::Equip(AWeapon* Weapon)
{
	CurrentWeapon = Weapon;
	CurrentWeapon->AttachToOwningPawn();
	
	CurrentReserveAmmo = ReserveAmmo.FindChecked(CurrentWeapon->WeaponType);
	OnCurrentWeaponReserveAmmoChanged.Broadcast(CurrentReserveAmmo, CurrentWeapon->Ammo);
}

void UOperatorCombatComponent::SpawnInventory()
{
	if (GetOwner()->GetLocalRole() < ROLE_Authority) return;
	
	for (TSubclassOf<AWeapon>& WeaponClass : DefaultWeaponClasses)
	{
		AWeapon* Weapon = SpawnWeapon(WeaponClass);
		Inventory.AddUnique(Weapon); // TODO: Ensure we want a unique weapon. What if the player has 2?
		ReserveAmmo.Add(Weapon->WeaponType, Weapon->StartingCarriedAmmo);
	}

	if (Inventory.Num() > 0)
	{
		Equip(Inventory[0]);
		InitializeWeaponWidgets();
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

void UOperatorCombatComponent::InitializeWeaponWidgets() const
{
	if (IsValid(CurrentWeapon))
	{
		OnReticleChanged.Broadcast(CurrentWeapon->GetReticleDynamicMaterialInstance(), CurrentWeapon->ReticleParams, bHitPlayer);
		OnAmmoCounterChanged.Broadcast(CurrentWeapon->GetAmmoCounterDynamicMaterialInstance(),
			CurrentWeapon->Ammo,
			CurrentWeapon->MagCapacity);
		OnAimingStatusChanged.Broadcast(bAiming);
	}
}

void UOperatorCombatComponent::OnRep_CurrentWeapon(AWeapon* LastWeapon)
{
	if (!IsValid(CurrentWeapon)) return;
	CurrentWeapon->AttachToOwningPawn();
	IPlayerInterface::Execute_WeaponReplicated(GetOwner());
	InitializeWeaponWidgets();
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