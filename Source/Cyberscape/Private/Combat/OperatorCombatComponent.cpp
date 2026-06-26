// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Combat/OperatorCombatComponent.h"
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

void UOperatorCombatComponent::Initiate_CycleWeapon()
{
	
}

void UOperatorCombatComponent::Initiate_FireWeapon_Pressed()
{
	
}

void UOperatorCombatComponent::Initiate_FireWeapon_Released()
{
	
}

void UOperatorCombatComponent::Initiate_ReloadWeapon()
{
	
}

void UOperatorCombatComponent::Initiate_Aim_Pressed()
{
	
}

void UOperatorCombatComponent::Initiate_Aim_Released()
{
	
}
#pragma endregion
/*-------------------------------------------------------------------------*/