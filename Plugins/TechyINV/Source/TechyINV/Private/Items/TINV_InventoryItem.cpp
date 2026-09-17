// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Items/TINV_InventoryItem.h"
#include "Net/UnrealNetwork.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryItem.cpp_Functions
void UTINV_InventoryItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, ItemManifest);
}

bool UTINV_InventoryItem::IsSupportedForNetworking() const
{
	return true;
}

void UTINV_InventoryItem::SetItemManifest(const FTINV_ItemManifest& Manifest)
{
	ItemManifest = FInstancedStruct::Make<FTINV_ItemManifest>(Manifest);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
