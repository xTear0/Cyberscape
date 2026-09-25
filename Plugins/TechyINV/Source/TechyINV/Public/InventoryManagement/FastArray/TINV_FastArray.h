// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "TINV_FastArray.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTINV_InventoryComponent;
class UTINV_InventoryItem;
class UTINV_ItemComponent;
struct FGameplayTag;

// A single entry in the Inventory.
USTRUCT(BlueprintType)
struct FTINV_InventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FTINV_InventoryEntry() {}

private:
	friend struct FTINV_InventoryFastArray;
	friend UTINV_InventoryComponent;
	
	UPROPERTY()
	TObjectPtr<UTINV_InventoryItem> Item = nullptr;
};

// List of Inventory Items.
USTRUCT(BlueprintType)
struct FTINV_InventoryFastArray : public FFastArraySerializer
{
	GENERATED_BODY()

	FTINV_InventoryFastArray() : OwnerComponent(nullptr) {}
	FTINV_InventoryFastArray(UActorComponent* InOwnerComponent) : OwnerComponent(InOwnerComponent) {}

	TArray<UTINV_InventoryItem*> GetAllItems() const;

	// FFastArraySerializer Contract:
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	// End of FFastArraySerializer Contract.

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FastArrayDeltaSerialize<FTINV_InventoryEntry, FTINV_InventoryFastArray>(Entries, DeltaParams, *this);	
	};

	UTINV_InventoryItem* AddEntry(UTINV_ItemComponent* ItemComponent);
	UTINV_InventoryItem* AddEntry(UTINV_InventoryItem* Item);
	void RemoveEntry(UTINV_InventoryItem* Item);
	UTINV_InventoryItem* FindFirstItemByTag(const FGameplayTag& Item);
	
private:
	friend UTINV_InventoryComponent;
	// Replicated list of Items.
	UPROPERTY()
	TArray<FTINV_InventoryEntry> Entries;
	
	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};

template<>
struct TStructOpsTypeTraits<FTINV_InventoryFastArray> : public TStructOpsTypeTraitsBase2<FTINV_InventoryFastArray>
{
	enum { WithNetDeltaSerializer = true };
};
/*-------------------------------------------------------------------------*/