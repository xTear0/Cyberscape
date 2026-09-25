// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "InventoryManagement/FastArray/TINV_FastArray.h"

#include "ToolMenusEditor.h"
#include "InventoryManagement/Components/TINV_InventoryComponent.h"
#include "Items/TINV_InventoryItem.h"
#include "Items/Components/TINV_ItemComponent.h"
#include "Tests/ToolMenusTestUtilities.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_FastArray.cpp_Functions
TArray<UTINV_InventoryItem*> FTINV_InventoryFastArray::GetAllItems() const
{
	TArray<UTINV_InventoryItem*> Results;
	Results.Reserve(Entries.Num());
	for (const auto& Entry : Entries)
	{
		if (!IsValid(Entry.Item)) continue;
		Results.Add(Entry.Item);
	}
	return Results;
}

void FTINV_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	UTINV_InventoryComponent* IC = Cast<UTINV_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return;
	for (int32 Index : RemovedIndices)
	{
		IC->OnItemRemoved.Broadcast(Entries[Index].Item);
	}
}

void FTINV_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	UTINV_InventoryComponent* IC = Cast<UTINV_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return;
	for (int32 Index : AddedIndices)
	{
		IC->OnItemAdded.Broadcast(Entries[Index].Item);
	}
}

UTINV_InventoryItem* FTINV_InventoryFastArray::AddEntry(UTINV_ItemComponent* ItemComponent)
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());
	UTINV_InventoryComponent* IC = Cast<UTINV_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return nullptr;

	FTINV_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = ItemComponent->GetItemManifest().Manifest(OwningActor);

	IC->AddRepSubObj(NewEntry.Item);
	MarkItemDirty(NewEntry);
	
	return NewEntry.Item;
}

UTINV_InventoryItem* FTINV_InventoryFastArray::AddEntry(UTINV_InventoryItem* Item)
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());

	FTINV_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = Item;
	MarkItemDirty(NewEntry);
	return Item;
}

void FTINV_InventoryFastArray::RemoveEntry(UTINV_InventoryItem* Item)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FTINV_InventoryEntry& Entry = *EntryIt;
		if (Entry.Item == Item)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
	}
}

UTINV_InventoryItem* FTINV_InventoryFastArray::FindFirstItemByTag(const FGameplayTag& Item)
{
	auto* FoundItem = Entries.FindByPredicate([Item](const FTINV_InventoryEntry& Entry)
	{
		return IsValid(Entry.Item) && Entry.Item->GetItemManifest().GetItemID().MatchesTagExact(Item);
	});
	return FoundItem ? FoundItem->Item : nullptr;
}
#pragma endregion
/*-------------------------------------------------------------------------*/