// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Cyberscape/Public/Character/OperatorAnimInstance.h"
#include "Cyberscape/Public/Character/OperatorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region OperatorAnimInstance.cpp_Functions
void UOperatorAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OperatorCharacter = Cast<AOperatorCharacter>(TryGetPawnOwner());
	
}

void UOperatorAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!IsValid(OperatorCharacter))
	{
		OperatorCharacter = Cast<AOperatorCharacter>(TryGetPawnOwner());
	}

	if (!IsValid(OperatorCharacter)) return;

	FVector Velocity = OperatorCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = OperatorCharacter->GetCharacterMovement()->IsFalling();

	bIsAccelerating = OperatorCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

	
}
#pragma endregion
/*-------------------------------------------------------------------------*/
