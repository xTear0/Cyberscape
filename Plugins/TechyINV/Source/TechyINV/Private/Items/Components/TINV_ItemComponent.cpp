// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Items/Components/TINV_ItemComponent.h"
#include "Net/UnrealNetwork.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_ItemComponent.cpp_Functions
UTINV_ItemComponent::UTINV_ItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTINV_ItemComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, ItemManifest);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
