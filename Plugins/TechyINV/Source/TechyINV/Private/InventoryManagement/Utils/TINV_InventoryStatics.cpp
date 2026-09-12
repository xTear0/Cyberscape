// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "InventoryManagement/Utils/TINV_InventoryStatics.h"
#include "InventoryManagement/Components/TINV_InventoryComponent.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryStatics.cpp_Functions
UTINV_InventoryComponent* UTINV_InventoryStatics::GetInventoryComponent(const APlayerController* PC)
{
	if (!IsValid(PC)) return nullptr;
	UTINV_InventoryComponent* IC = PC->FindComponentByClass<UTINV_InventoryComponent>();
	return IC;
}
#pragma endregion
/*-------------------------------------------------------------------------*/
