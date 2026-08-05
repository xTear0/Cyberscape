// Copyright xTear Studios
/*-------------------------------------------------------------------------*/

#include "Items/Components/TINV_ItemComponent.h"

/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_ItemComponent.cpp_Functions
UTINV_ItemComponent::UTINV_ItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	PickupMessage = FString("Item");
}
#pragma endregion
/*-------------------------------------------------------------------------*/
