// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Cyberscape/Public/Character/OperatorCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Combat/OperatorCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
}

void AOperatorCharacter::Input_Aim_Released()
{
	CombatComponent->Initiate_Aim_Released();
}

void AOperatorCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*if (HasAuthority())
	{
		OnTakeAnyDamage.AddDynamic(this, &AOperatorCharacter::ReceiveDamage);
	}
	if (AttachedGrenade)
	{
		AttachedGrenade->SetVisibility(false);
	}*/
}

void AOperatorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
#pragma endregion
/*-------------------------------------------------------------------------*/