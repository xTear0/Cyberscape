// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/Spatial/TINV_InventoryGrid.h"

#include "IDetailTreeNode.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "InventoryManagement/Components/TINV_InventoryComponent.h"
#include "InventoryManagement/Utils/TINV_InventoryStatics.h"
#include "ItemData/TINV_ItemDataTable.h"
#include "Items/TINV_InventoryItem.h"
#include "Items/Components/TINV_ItemComponent.h"
#include "Notifications/CUI_NotificationManager.h"
#include "Widgets/Inventory/TINV_SlottedItem.h"
#include "Widgets/Inventory/GridSlots/TINV_GridSlot.h"
#include "Widgets/Utils/TINV_WidgetUtils.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryGrid.cpp_Functions
void UTINV_InventoryGrid::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ConstructGrid();
	InventoryComponent = UTINV_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	InventoryComponent->OnItemAdded.AddDynamic(this, &ThisClass::AddItem);
}

FTINV_SlotAvailabilityResult UTINV_InventoryGrid::HasRoomForItem(const UTINV_ItemComponent* ItemComponent)
{
	return HasRoomForItem(ItemComponent->GetItemManifest());
}

FTINV_SlotAvailabilityResult UTINV_InventoryGrid::HasRoomForItem(const UTINV_InventoryItem* Item)
{
	return HasRoomForItem(Item->GetItemManifest());
}

FTINV_SlotAvailabilityResult UTINV_InventoryGrid::HasRoomForItem(const FTINV_ItemManifest& Manifest, const int32 StackAmount)
{
	FTINV_SlotAvailabilityResult Result;

	// Look up the item's data by its tag.
	const FTINV_ItemDataDefinition* ItemData = GetItemData(Manifest);
	if (!ItemData) return Result;

	const FGameplayTag ItemID = Manifest.GetItemID();

	// Determine if the item is stackable, and how much we need to place.
	Result.bStackable = ItemData->MaxStackSize > 1;
	const int32 MaxStackSize = Result.bStackable ? ItemData->MaxStackSize : 1;
	int32 AmountToFill = Result.bStackable ? FMath::Max(1, StackAmount) : 1;

	// Pass 1: check EVERY grid slot for a non-full stack of the same item and fill it first.
	if (Result.bStackable)
	{
		for (const UTINV_GridSlot* GridSlot : GridSlots)
		{
			if (AmountToFill <= 0) break;

			// Is this the same item?
			if (!IsSameItem(GridSlot, ItemID)) continue;

			// Is this stack already full?
			const int32 RoomInSlot = GetRoomInSlot(GridSlot, MaxStackSize);
			if (RoomInSlot <= 0) continue;

			// Fill as much of this stack as we can.
			AddSlotAvailability(Result, GridSlot, FMath::Min(RoomInSlot, AmountToFill), true, AmountToFill);
		}
	}

	// Pass 2: place the remainder into the first available empty slots.
	for (const UTINV_GridSlot* GridSlot : GridSlots)
	{
		if (AmountToFill <= 0) break;

		// Is this slot empty?
		if (!IsSlotEmpty(GridSlot)) continue;

		AddSlotAvailability(Result, GridSlot, FMath::Min(MaxStackSize, AmountToFill), false, AmountToFill);
	}

	// Whatever couldn't fit.
	Result.Remainder = AmountToFill;
	return Result;
}

bool UTINV_InventoryGrid::IsSlotEmpty(const UTINV_GridSlot* GridSlot) const
{
	return !GridSlot->GetInventoryItem().IsValid();
}

bool UTINV_InventoryGrid::IsSameItem(const UTINV_GridSlot* GridSlot, const FGameplayTag& ItemID) const
{
	const UTINV_InventoryItem* SlotItem = GridSlot->GetInventoryItem().Get();
	return IsValid(SlotItem) && SlotItem->GetItemManifest().GetItemID().MatchesTagExact(ItemID);
}

int32 UTINV_InventoryGrid::GetRoomInSlot(const UTINV_GridSlot* GridSlot, const int32 MaxStackSize) const
{
	return MaxStackSize - GridSlot->GetStackCount();
}

void UTINV_InventoryGrid::AddSlotAvailability(FTINV_SlotAvailabilityResult& Result, const UTINV_GridSlot* GridSlot,
	const int32 FillAmount, const bool bItemAtIndex, int32& AmountToFill) const
{
	Result.SlotAvailabilities.Emplace(FTINV_SlotAvailability{
		GridSlot->GetTileIndex(),
		Result.bStackable ? FillAmount : 0,
		bItemAtIndex
	});
	Result.TotalRoomToFill += FillAmount;
	AmountToFill -= FillAmount;
}

void UTINV_InventoryGrid::AddItem(UTINV_InventoryItem* Item)
{
	check(ItemDataTable);
	FTINV_SlotAvailabilityResult Result = HasRoomForItem(Item);
	FTINV_ItemManifest& ItemManifest = Item->GetItemManifestMutable();
	FGameplayTag ItemID = ItemManifest.GetItemID();

	if (const FTINV_ItemDataDefinition* ItemData = ItemDataTable->GetDataByTag(ItemID))
	{
		UCUI_NotificationManager::PostItem(this,
	FText::Format(NSLOCTEXT("Cyberscape", "InventoryItem", "{0}"),
		ItemData->ItemName),
		true,
		ItemData->ItemIcon,
		UTINV_WidgetUtils::GetCUIItemTier(ItemData->ItemTier));
		
	}
	
	if (const FTINV_ItemWeaponDataDefinition* WeaponData = ItemDataTable->GetWeaponData(ItemID))
	{
		int32 MaxAmmo = WeaponData->WeaponDefaults.WeaponBaseMaxAmmo;
		// ...
	}
	
	AddItemToIndicies(Result, Item);
}

const FTINV_ItemDataDefinition* UTINV_InventoryGrid::GetItemData(const FTINV_ItemManifest& Manifest) const
{
	return ItemDataTable ? ItemDataTable->GetDataByTag(Manifest.GetItemID()) : nullptr;
}

void UTINV_InventoryGrid::AddItemToIndicies(const FTINV_SlotAvailabilityResult& Result, UTINV_InventoryItem* NewItem)
{
	for (const auto& Availability : Result.SlotAvailabilities)
	{
		AddItemAtIndex(NewItem, Availability.Index, Result.bStackable, Availability.AmountToFill);
		UpdateGridSlots(NewItem, Availability.Index, Result.bStackable, Availability.AmountToFill);
	}
	
}

void UTINV_InventoryGrid::AddItemAtIndex(UTINV_InventoryItem* Item, const int32 Index, const bool bStackable,
	const int32 StackAmount)
{
	// Get the Item Icon to display.
	UTexture2D* ItemIcon = nullptr;
	ETINV_ItemTier ItemTier = ETINV_ItemTier::Scrap;
	
	if (const FTINV_ItemDataDefinition* ItemData = ItemDataTable->GetDataByTag(Item->GetItemManifest().GetItemID()))
	{
		ItemIcon = ItemData->ItemIcon;
		ItemTier = ItemData->ItemTier;
	}

	// Create a slotted item.
	UTINV_SlottedItem* SlottedItem = CreateWidget<UTINV_SlottedItem>(GetOwningPlayer(), SlottedItemClass);
	SlottedItem->SetInventoryItem(Item);
	SlottedItem->LoadIcon(ItemIcon, ItemTier);
	SlottedItem->SetGridIndex(Index);
	SlottedItem->SetIsStackable(bStackable);
	const int32 StackUpdateAmount = bStackable ? StackAmount : 0;
	SlottedItem->UpdateStackCount(StackUpdateAmount);

	// Add the slotted item to the canvas panel.
	AddSlottedItemToCanvas(Index, SlottedItem);
	
	// Store the widgets in a container.
	SlottedItems.Add(Index, SlottedItem);
}

void UTINV_InventoryGrid::AddSlottedItemToCanvas(const int32 Index, UTINV_SlottedItem* SlottedItem) const
{
	CanvasPanel->AddChildToCanvas(SlottedItem);
	UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(SlottedItem);
	const FVector2D Size(TileSize);
	CanvasSlot->SetSize(Size);
	const FVector2D DrawPos = UTINV_WidgetUtils::GetPositionFromIndex(Index, Columns) * TileSize;
	CanvasSlot->SetPosition(DrawPos);
}

void UTINV_InventoryGrid::UpdateGridSlots(UTINV_InventoryItem* NewItem, const int32 Index, bool bStackableItem, const int32 StackAmount)
{
	check(GridSlots.IsValidIndex(Index));

	if (bStackableItem)
	{
		GridSlots[Index]->SetStackCount(StackAmount);	
	}
	
	UTINV_GridSlot* GridSlot = GridSlots[Index];
	
	ETINV_ItemTier ItemTier = ETINV_ItemTier::Scrap;
	
	if (const FTINV_ItemDataDefinition* ItemData = ItemDataTable->GetDataByTag(NewItem->GetItemManifest().GetItemID()))
	{
		ItemTier = ItemData->ItemTier;
	}

	GridSlot->SetInventoryItem(NewItem);
	GridSlot->SetOccupiedTexture(ItemTier);
}

bool UTINV_InventoryGrid::IsIndexClaimed(const TSet<int32>& CheckedIndicies, const int32 Index) const
{
	return CheckedIndicies.Contains(Index);
}



void UTINV_InventoryGrid::ConstructGrid()
{
	GridSlots.Reserve(Rows * Columns);

	for (int32 j = 0; j < Rows; j++)
	{
		for (int32 i = 0; i < Columns; i++)
		{
			UTINV_GridSlot* GridSlot = CreateWidget<UTINV_GridSlot>(this, GridSlotClass);
			CanvasPanel->AddChild(GridSlot);

			const FIntPoint TilePosition = FIntPoint(i, j);
			
			GridSlot->SetTileIndex(UTINV_WidgetUtils::GetIndexFromPosition(TilePosition, Columns));

			UCanvasPanelSlot* GridCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridSlot);
			GridCPS->SetSize(FVector2D(TileSize));
			GridCPS->SetPosition(TilePosition * TileSize);

			GridSlots.Add(GridSlot);
		}
	}
}

#pragma endregion
/*-------------------------------------------------------------------------*/
