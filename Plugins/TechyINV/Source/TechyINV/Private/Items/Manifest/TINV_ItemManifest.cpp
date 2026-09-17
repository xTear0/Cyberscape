// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Items/Manifest/TINV_ItemManifest.h"

#include "Items/TINV_InventoryItem.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryComponent.cpp_Functions
UTINV_InventoryItem* FTINV_ItemManifest::Manifest(UObject* NewOuter)
{
	UTINV_InventoryItem* Item = NewObject<UTINV_InventoryItem>(NewOuter, UTINV_InventoryItem::StaticClass());
	Item->SetItemManifest(*this);

	return Item;
}
#pragma endregion
/*-------------------------------------------------------------------------*/