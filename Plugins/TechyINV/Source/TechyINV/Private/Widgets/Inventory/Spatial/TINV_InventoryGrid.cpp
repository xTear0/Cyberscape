// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/Spatial/TINV_InventoryGrid.h"
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

FTINV_SlotAvailabilityResult UTINV_InventoryGrid::HasRoomForItem(const FTINV_ItemManifest& Manifest)
{
	FTINV_SlotAvailabilityResult Result;
	Result.TotalRoomToFill = 1;

	FTINV_SlotAvailability SlotAvailability;
	SlotAvailability.AmountToFill = 1;
	SlotAvailability.Index = 0;
	Result.SlotAvailabilities.Add(MoveTemp(SlotAvailability));
	
	return Result;
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
		ItemData->ItemIcon);
	}
	
	if (const FTINV_ItemWeaponDataDefinition* WeaponData = ItemDataTable->GetWeaponData(ItemID))
	{
		int32 MaxAmmo = WeaponData->WeaponDefaults.WeaponBaseMaxAmmo;
		// ...
	}
	
	AddItemToIndicies(Result, Item);
}

void UTINV_InventoryGrid::AddItemToIndicies(const FTINV_SlotAvailabilityResult& Result, UTINV_InventoryItem* NewItem)
{
	// Get the Item Icon to display.
	// Create a widget to add to the grid.
	// Store the widgets in a container.
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
