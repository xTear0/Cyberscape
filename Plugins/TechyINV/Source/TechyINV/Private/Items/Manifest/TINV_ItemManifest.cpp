// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Items/Manifest/TINV_ItemManifest.h"
#include "Items/TINV_InventoryItem.h"
#include "Items/Components/TINV_ItemComponent.h"
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

void FTINV_ItemManifest::SpawnPickupActor(
	const UObject* WorldContextObject,
	const TSubclassOf<AActor>& ItemRespawnClass,
	const FVector& SpawnLocation,
	const FRotator& SpawnRotation) const
{
	if (!IsValid(ItemRespawnClass) || !IsValid(WorldContextObject)) return;
	AActor* SpawnedActor = WorldContextObject->GetWorld()->SpawnActor<AActor>(ItemRespawnClass, SpawnLocation, SpawnRotation);
	if (!IsValid(SpawnedActor)) return;

	// Set the Item Manifest & StackCount.
	UTINV_ItemComponent* ItemComp = SpawnedActor->FindComponentByClass<UTINV_ItemComponent>();
	check(ItemComp);
	ItemComp->InitItemManifest(*this);
}
#pragma endregion
/*-------------------------------------------------------------------------*/