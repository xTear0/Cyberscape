// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "InventoryManagement/Utils/TINV_InventoryStatics.h"
#include "InventoryManagement/Components/TINV_InventoryComponent.h"
#include "Items/Components/TINV_ItemComponent.h"
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

FGameplayTag UTINV_InventoryStatics::GetItemIDFromItemComp(UTINV_ItemComponent* ItemComp)
{
	FGameplayTag Tag;
	if (!IsValid(ItemComp)) return Tag;
	Tag = ItemComp->GetItemManifest().GetItemID();
	return Tag;	
}
#pragma endregion
/*-------------------------------------------------------------------------*/
