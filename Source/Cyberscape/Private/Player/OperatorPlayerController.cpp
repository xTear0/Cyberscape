// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Cyberscape/Public/Player/OperatorPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HeadMountedDisplayTypes.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region OperatorPlayerController.cpp_Functions
AOperatorPlayerController::AOperatorPlayerController()
{
	bReplicates = true;
	
}

void AOperatorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(OperatorIMC, 0);
	}
}

void AOperatorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* OperatorInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	OperatorInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOperatorPlayerController::Input_Move);
	OperatorInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOperatorPlayerController::Input_Look);
	OperatorInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AOperatorPlayerController::Input_Jump);
	OperatorInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AOperatorPlayerController::Input_Crouch);
}

void AOperatorPlayerController::Input_Crouch()
{
	if (!IsValid(GetCharacter())) return;
	if (UCharacterMovementComponent* CMC = GetCharacter()->GetCharacterMovement(); IsValid(CMC))
	{
		CMC->bWantsToCrouch = !CMC->bWantsToCrouch;
	}
}

void AOperatorPlayerController::Input_Jump()
{
	if (!IsValid(GetCharacter())) return;
	UCharacterMovementComponent* CMC = GetCharacter()->GetCharacterMovement();
	if (!IsValid(CMC)) return;

	if (CMC->bWantsToCrouch)
	{
		CMC->bWantsToCrouch = false;
	}
	else
	{
		GetCharacter()->Jump();
	}
}

void AOperatorPlayerController::Input_Move(const FInputActionValue& Value)
{
	/*if (bDisableGameplay) return;*/
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
	const FVector RightDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AOperatorPlayerController::Input_Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
