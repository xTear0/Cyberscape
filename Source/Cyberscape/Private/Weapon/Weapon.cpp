// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Weapon/Weapon.h"

#include "KismetTraceUtils.h"
#include "Cyberscape/Cyberscape.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/PlayerInterface.h"
#include "Kismet/KismetMathLibrary.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Weapon.cpp_Functions
// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bNetUseOwnerRelevancy = true; // If you can see the owner, then you can see this weapon.

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh1P");
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh1P->CastShadow = false;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->SetHiddenInGame(true);
	SetRootComponent(Mesh1P);
	
	Mesh3P = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh3P");
	Mesh3P->CastShadow = true;
	Mesh1P->bReceivesDecals = false;
	Mesh3P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh3P->SetupAttachment(Mesh1P);
	Mesh3P->SetHiddenInGame(true);

	// TODO: Eventually, the attachments will drive the FOV amount granted by the weapon.
	AimFOV = 65.0f; // Default aiming on ANY weapon is 65.0f.
	TraceRadius = 5.f;

	FireTime = 0.1f;
	MagCapacity = 10;
	Ammo = 5;
	StartingCarriedAmmo = 10;
	Sequence = 0;
}

void AWeapon::OnRep_Instigator()
{
	Super::OnRep_Instigator();
	AttachToOwningPawn();
}

USkeletalMeshComponent* AWeapon::GetMesh1P() const
{
	return Mesh1P;
}

USkeletalMeshComponent* AWeapon::GetMesh3P() const
{
	return Mesh3P;
}

UMaterialInstanceDynamic* AWeapon::GetReticleDynamicMaterialInstance()
{
	if (!IsValid(DynMatInst_Reticle))
	{
		DynMatInst_Reticle = UMaterialInstanceDynamic::Create(ReticleMaterial, this);
	}
	return DynMatInst_Reticle;
}

UMaterialInstanceDynamic* AWeapon::GetAmmoCounterDynamicMaterialInstance()
{
	if (!IsValid(DynMatInst_AmmoCounter))
	{
		DynMatInst_AmmoCounter = UMaterialInstanceDynamic::Create(AmmoCounterMaterial, this);
	}
	return DynMatInst_AmmoCounter;
}

void AWeapon::AttachToOwningPawn() const
{
	APawn* OwningPawn = GetInstigator();
	if (!IsValid(OwningPawn) || !OwningPawn->Implements<UPlayerInterface>()) return;
	SetMeshVisibility(OwningPawn);

	const FName AttachPoint = IPlayerInterface::Execute_GetWeaponAttachmentPoint(OwningPawn, WeaponType);
	USkeletalMeshComponent* PawnMesh1P = IPlayerInterface::Execute_GetMesh1P(OwningPawn);
	USkeletalMeshComponent* PawnMesh3P = IPlayerInterface::Execute_GetMesh3P(OwningPawn);

	Mesh1P->AttachToComponent(PawnMesh1P, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
	Mesh3P->AttachToComponent(PawnMesh3P, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
}

void AWeapon::WeaponTrace(FHitResult& OutHit, float TraceLength) const
{
	FCollisionQueryParams QueryParams;
	QueryParams.bReturnPhysicalMaterial = true;
	QueryParams.AddIgnoredActor(GetOwner());

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	ResponseParams.CollisionResponse.SetResponse(ECC_WorldStatic, ECR_Block);
	ResponseParams.CollisionResponse.SetResponse(ECC_WorldDynamic, ECR_Block);
	ResponseParams.CollisionResponse.SetResponse(ECC_PhysicsBody, ECR_Block);

	ensure(GetInstigator());
	if (APlayerController* PC = Cast<APlayerController>(GetInstigator()->GetController()); IsValid(PC))
	{
		FVector EyesWorldLocation;
		FRotator EyesWorldRotation;
		PC->GetActorEyesViewPoint(EyesWorldLocation, EyesWorldRotation);
		const FVector EyesWorldDirection = UKismetMathLibrary::GetForwardVector(EyesWorldRotation);

		const FVector Start = EyesWorldLocation;
		const FVector End = Start + EyesWorldDirection * TraceLength;

		const bool bHit = GetWorld()->SweepSingleByChannel(
			OutHit,
			Start,
			End,
			FQuat::Identity,
			CyberscapeTraceChannels::ECC_Weapon,
			FCollisionShape::MakeSphere(TraceRadius),
			QueryParams,
			ResponseParams);

		if (!bHit)
		{
			OutHit.ImpactPoint = End;
		}
	}
}

void AWeapon::Local_Fire(const FVector& ImpactPoint, const FVector& ImpactNormal,
	TEnumAsByte<EPhysicalSurface> ImpactSurfaceType, bool bIsFirstPerson)
{
	FireEffects(ImpactPoint, ImpactNormal, ImpactSurfaceType, bIsFirstPerson);

	if (GetInstigator()->IsLocallyControlled())
	{
		Ammo = FMath::Clamp(Ammo - 1, 0, MagCapacity);
		if (GetInstigator()->IsLocallyControlled() && !GetInstigator()->HasAuthority())
		{
			++Sequence;
		}
	}
}

void AWeapon::Auth_Fire()
{
	Ammo = FMath::Clamp(Ammo - 1, 0, MagCapacity);
}

void AWeapon::Rep_Fire(int32 AuthAmmo)
{
	if (GetInstigator()->IsLocallyControlled() && !GetInstigator()->HasAuthority())
	{
		Ammo = AuthAmmo;
		-- Sequence;
		Ammo -= Sequence;
	}
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::SetMeshVisibility(APawn* OwningPawn) const
{
	if (OwningPawn->IsLocallyControlled())
	{
		Mesh1P->SetHiddenInGame(false);
		Mesh3P->SetHiddenInGame(true);
	}
	else
	{
		Mesh1P->SetHiddenInGame(true);
		Mesh3P->SetHiddenInGame(false);
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/