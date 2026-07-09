// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Cyberscape/Public/Character/OperatorCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Combat/OperatorCombatComponent.h"
#include "Data/WeaponData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Weapon.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region OperatorCharacter.cpp_Functions
// Sets default values
AOperatorCharacter::AOperatorCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Camera Boom
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 0.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;
	SpringArm->bUsePawnControlRotation = true;

	// First-Person Camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(SpringArm);
	FirstPersonCamera->bUsePawnControlRotation = false;

	// First-Person Character Arms
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1P"));
	Mesh1P->SetupAttachment(FirstPersonCamera);
	Mesh1P->bOnlyOwnerSee = true;
	Mesh1P->bOwnerNoSee = false;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;

	GetMesh()->bOnlyOwnerSee = false;
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bReceivesDecals = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	CombatComponent = CreateDefaultSubobject<UOperatorCombatComponent>("CombatComponent");
	CombatComponent->SetIsReplicated(true);

	DefaultFOV = 90.0f;
	TurningStatus = ETurningInPlace::NotTurning;
	bWeaponFirstReplicated = false;
}

void AOperatorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* OperatorInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	OperatorInputComponent->BindAction(CycleWeaponAction, ETriggerEvent::Started, this, &AOperatorCharacter::Input_CycleWeapon);
	OperatorInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Started, this, &AOperatorCharacter::Input_FireWeapon_Pressed);
	OperatorInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Completed, this, &AOperatorCharacter::Input_FireWeapon_Released);
	OperatorInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Started, this, &AOperatorCharacter::Input_Aim_Pressed);
	OperatorInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Completed, this, &AOperatorCharacter::Input_Aim_Released);
	OperatorInputComponent->BindAction(ReloadWeaponAction, ETriggerEvent::Started, this, &AOperatorCharacter::Input_ReloadWeapon);
}

void AOperatorCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (IsValid(CombatComponent))
	{
		CombatComponent->SpawnInventory();
	}
}

void AOperatorCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (IsValid(CombatComponent))
	{
		CombatComponent->InitializeWeaponWidgets();
	}
}

FName AOperatorCharacter::GetWeaponAttachmentPoint_Implementation(const FGameplayTag& WeaponType) const
{
	checkf(CombatComponent->WeaponData, TEXT("No Weapon Data Asset - Please fill out BP_OperatorCharacter"))
	return CombatComponent->WeaponData->GripPoints.FindChecked(WeaponType);
}

USkeletalMeshComponent* AOperatorCharacter::GetMesh1P_Implementation() const
{
	return Mesh1P;
	
}

USkeletalMeshComponent* AOperatorCharacter::GetMesh3P_Implementation() const
{
	return GetMesh();
}

void AOperatorCharacter::WeaponReplicated_Implementation()
{
	if (!bWeaponFirstReplicated)
	{
		bWeaponFirstReplicated = true;
		OnWeaponFirstReplicated.Broadcast(CombatComponent->CurrentWeapon, CombatComponent->bHitPlayer);
	}
}

AWeapon* AOperatorCharacter::GetCurrentWeapon_Implementation()
{
	return CombatComponent->CurrentWeapon;
}

int32 AOperatorCharacter::GetReserveAmmo_Implementation() const
{
	return CombatComponent->CurrentReserveAmmo;
}

FRotator AOperatorCharacter::GetFixedAimRotation() const
{
	FRotator AimRotation = GetBaseAimRotation();
	if (AimRotation.Pitch > 90.f && !IsLocallyControlled())
	{
		const FVector2D InRange(270.f, 360.f);
		const FVector2D OutRange(-90.f, 0.f);
		AimRotation.Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, AimRotation.Pitch);
	}
	return AimRotation;
}

void AOperatorCharacter::Input_CycleWeapon()
{
	CombatComponent->Initiate_CycleWeapon();
}

void AOperatorCharacter::Input_FireWeapon_Pressed()
{
	CombatComponent->Initiate_FireWeapon_Pressed();
}

void AOperatorCharacter::Input_FireWeapon_Released()
{
	CombatComponent->Initiate_FireWeapon_Released();
}

void AOperatorCharacter::Input_ReloadWeapon()
{
	CombatComponent->Initiate_ReloadWeapon();
}

void AOperatorCharacter::Input_Aim_Pressed()
{
	CombatComponent->Initiate_Aim_Pressed();
	OnAim(true);
}

void AOperatorCharacter::Input_Aim_Released()
{
	CombatComponent->Initiate_Aim_Released();
	OnAim(false);
}

bool AOperatorCharacter::HasCurrentWeapon() const
{
	return IsValid(CombatComponent) && CombatComponent->CurrentWeapon != nullptr;
}

void AOperatorCharacter::BeginPlay()
{
	Super::BeginPlay();

	FirstPersonCamera->SetFieldOfView(DefaultFOV);

	StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
	
	/*if (HasAuthority())
	{
		OnTakeAnyDamage.AddDynamic(this, &AOperatorCharacter::ReceiveDamage);
	}
	if (AttachedGrenade)
	{
		AttachedGrenade->SetVisibility(false);
	}*/
}

void AOperatorCharacter::CalculateFABRIKSocketTransform()
{
	if (IsValid(CombatComponent) && IsValid(CombatComponent->CurrentWeapon) && IsValid(CombatComponent->CurrentWeapon->GetMesh3P()))
	{
		FABRIK_SocketTransform = CombatComponent->CurrentWeapon->GetMesh3P()->GetSocketTransform("FABRIK_Socket", RTS_World);

		FVector OutLocation;
		FRotator OutRotation;
		GetMesh()->TransformToBoneSpace("hand_r",
        FABRIK_SocketTransform.GetLocation(),
        FABRIK_SocketTransform.GetRotation().Rotator(),
        OutLocation,
        OutRotation);
		FABRIK_SocketTransform.SetLocation(OutLocation);
		FABRIK_SocketTransform.SetRotation(OutRotation.Quaternion());
	}
}

void AOperatorCharacter::CalculateTurnInPlaceParameters(float DeltaTime)
{
	// Are we running? Get velocity, see if it's 0.
	FVector Velocity = GetVelocity();
	float Speed = Velocity.Size2D();
	
	// Are we falling? Check to see if we are in air.
	bool bIsInAir = GetCharacterMovement()->IsFalling();
	
	// If standing still and not jumping,
	if (Speed == 0.f && !bIsInAir)
	{
		// Get current Aim Rotation.
		FRotator CurrentAimRotation(0.f, GetBaseAimRotation().Yaw, 0.f); 
		// Get Delta Aim Rotation (change in rotation of current aim vs. initial aim, set in begin play).
		FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, StartingAimRotation);
		// Store the Yaw of the delta aim rotation (AO_Yaw).
		AO_Yaw = DeltaAimRotation.Yaw;
		if (TurningStatus == ETurningInPlace::NotTurning)
		{
			InterpAO_Yaw = AO_Yaw;
		}
		TurnInPlace(DeltaTime);
	}

	if (Speed > 0.f || bIsInAir)
	{
		StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		AO_Yaw = 0.f;

		FRotator AimRotation = GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
		TurningStatus = ETurningInPlace::NotTurning;
	}

	AO_Yaw *= -1.f;
}

void AOperatorCharacter::TurnInPlace(float DeltaTime)
{
	if (AO_Yaw > 90.f)
	{
		TurningStatus = ETurningInPlace::Right;
	}
	else if (AO_Yaw < -90.f)
	{
		TurningStatus = ETurningInPlace::Left;
	}
	if (TurningStatus != ETurningInPlace::NotTurning) // We are turning.
	{
		InterpAO_Yaw = FMath::FInterpTo(InterpAO_Yaw, 0.f, DeltaTime, 4.0f);
		AO_Yaw = InterpAO_Yaw;
		if (FMath::Abs(AO_Yaw) < 5.f)
		{
			TurningStatus = ETurningInPlace::NotTurning;
			StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		}
	}
}

void AOperatorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CalculateTurnInPlaceParameters(DeltaTime);
	CalculateFABRIKSocketTransform();
}
#pragma endregion
/*-------------------------------------------------------------------------*/