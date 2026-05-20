// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/Spatial/Inv_SpatialInventory.h"
#include "IDetailTreeNode.h"
#include "Widgets/ItemDescription/Inv_ItemDescription.h"
#include "Widgets/Inventory/GridSlots/Inv_EquippedGridSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Inventory.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/WidgetSwitcher.h"
#include "Interfaces/Inv_AbilitySystemInterface.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "GameFramework/PlayerState.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Items/Inv_InventoryItem.h"
#include "Widgets/Inventory/Spatial/Inv_InventoryGrid.h"
#include "Widgets/Inventory/HoverItem/Inv_HoverItem.h"
#include "Widgets/Inventory/SlottedItems/Inv_EquippedSlottedItem.h"
#include "Widgets/Subsystems/AttributeHoverSubsystem.h"
#include "Widgets/ItemAttributeBreakdown/Inv_ItemAttributeBreakdown.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*  Functions                                                              */
/*-------------------------------------------------------------------------*/
#pragma region Inv_SpatialInventory.cpp_Functions
void UInv_SpatialInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Equippables->OnClicked.AddDynamic(this, &ThisClass::ShowEquippables);
	Button_Consumables->OnClicked.AddDynamic(this, &ThisClass::ShowConsumables);
	Button_Craftables->OnClicked.AddDynamic(this, &ThisClass::ShowCraftables);

	Grid_Equippables->SetOwningCanvas(CanvasPanel);
	Grid_Consumables->SetOwningCanvas(CanvasPanel);
	Grid_Craftables->SetOwningCanvas(CanvasPanel);
	
	ShowEquippables();

	WidgetTree->ForEachWidget([this](UWidget* Widget)
	{
		UInv_EquippedGridSlot* EquippedGridSlot = Cast<UInv_EquippedGridSlot>(Widget);
		if (IsValid(EquippedGridSlot))
		{
			EquippedGridSlots.Add(EquippedGridSlot);
			EquippedGridSlot->EquippedGridSlotClicked.AddDynamic(this, &ThisClass::EquippedGridSlotClicked);	
		}
	});

	BindToAttributeHoverSubsystem();
}

void UInv_SpatialInventory::EquippedGridSlotClicked(UInv_EquippedGridSlot* EquippedGridSlot,
	const FGameplayTag& EquipmentTypeTag)
{
	// Check to see if we can equip Hover Item.
	if (!CanEquipHoverItem(EquippedGridSlot, EquipmentTypeTag)) return;

	UInv_HoverItem* HoverItem = GetHoverItem();
	
	// Creates an Equipped Slotted Item and add it to the Equipped Grid Slot
	const float TileSize = UInv_InventoryStatics::GetInventoryWidget(GetOwningPlayer())->GetTileSize();
	UInv_EquippedSlottedItem* EquippedSlottedItem = EquippedGridSlot->OnItemEquipped(
		HoverItem->GetInventoryItem(),
		EquipmentTypeTag,
		TileSize
	);
	
	EquippedSlottedItem->OnEquippedSlottedItemClicked.AddDynamic(this, &ThisClass::EquippedSlottedItemClicked);
	
	// Inform server that we have equipped an item (potentially unequipping too).
	UInv_InventoryComponent* InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	check(IsValid(InventoryComponent));

	InventoryComponent->Server_EquipSlotClicked(HoverItem->GetInventoryItem(), nullptr);
	if (GetOwningPlayer()->GetNetMode() != NM_DedicatedServer)
	{
		InventoryComponent->OnItemEquipped.Broadcast(HoverItem->GetInventoryItem());
	}

	// Clear the Hover Item
	Grid_Equippables->ClearHoverItem();
}

void UInv_SpatialInventory::EquippedSlottedItemClicked(UInv_EquippedSlottedItem* EquippedSlottedItem)
{
	// Remove the Item Description
	UInv_InventoryStatics::ItemUnhovered(GetOwningPlayer());
	if (IsValid(GetHoverItem()) && GetHoverItem()->IsStackable()) return;
	
	// Get Item to Equip
	UInv_InventoryItem* ItemToEquip = IsValid(GetHoverItem()) ? GetHoverItem()->GetInventoryItem() : nullptr;
	// Get Item to Unequip
	UInv_InventoryItem* ItemToUnequip = EquippedSlottedItem->GetInventoryItem();
		
	// Get the Equipped Grid Slot holding this item
	UInv_EquippedGridSlot* EquippedGridSlot = FindSlotWithEquippedItem(ItemToUnequip);

	// If the ItemToEquip's Tag and the EquippedGridSlot's Tag do not match, return.
	if (ItemToEquip != nullptr && !CanSwapItems(
		ItemToEquip->GetItemManifest().GetItemType(),
		ItemToUnequip->GetItemManifest().GetItemType(),
		EquippedGridSlot->EquipmentSlotTag())) return;
	
	// Clear the equipped grid slot of the item (set its inventory item to nullptr)
	ClearSlotOfItem(EquippedGridSlot);
	
	// Remove the equipped slotted item from the equipped grid slot (unbind from the OnEquippedSlottedItemClicked)
	RemoveEquippedSlottedItem(EquippedSlottedItem);

	// Assign previously equipped item to the HoverItem
	Grid_Equippables->AssignHoverItem(ItemToUnequip);
	
	// Make a new equipped slotted item (for the item we held in HoverItem)
	MakeEquippedSlottedItem(EquippedSlottedItem, EquippedGridSlot, ItemToEquip);
	
	// Broadcast delegates for OnItemEquipped/OnItemUnequipped (from IC)
	BroadcastSlotClickedDelegates(ItemToEquip, ItemToUnequip);
}

FInv_SlotAvailabilityResult UInv_SpatialInventory::HasRoomForItem(UInv_ItemComponent* ItemComponent) const
{
	switch (UInv_InventoryStatics::GetItemCategoryFromItemComp(ItemComponent))
	{
	case EInv_ItemCategory::Equippable:
		return Grid_Equippables->HasRoomForItem(ItemComponent);
	case EInv_ItemCategory::Consumable:
		return Grid_Consumables->HasRoomForItem(ItemComponent);
	case EInv_ItemCategory::Craftable:
		return Grid_Craftables->HasRoomForItem(ItemComponent);
	default:
		UE_LOG(LogInventory, Error, TEXT("ItemComponent doesn't have a valid Item Category."))
		return FInv_SlotAvailabilityResult();
	}	
}

FReply UInv_SpatialInventory::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& MouseEvent)
{
	ActiveGrid->DropItem();
	return FReply::Handled();
}

void UInv_SpatialInventory::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (IsValid(ItemDescription))
	{
		SetItemDescriptionSizeAndPosition(ItemDescription, CanvasPanel);
	}

	if (IsValid(AttributeInspectBreakdown))
	{
		SetAttributeBreakdownSizeAndPosition(AttributeInspectBreakdown, CanvasPanel);
	}
}

void UInv_SpatialInventory::SetItemDescriptionSizeAndPosition(UInv_ItemDescription* Description, UCanvasPanel* Canvas) const
{
	UCanvasPanelSlot* ItemDescriptionCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(Description);
	if (!IsValid(ItemDescriptionCPS)) return;

	const FVector2D ItemDescriptionSize = Description->GetBoxSize();
	ItemDescriptionCPS->SetSize(ItemDescriptionSize);

	FVector2D ClampedPosition = UInv_WidgetUtils::GetClampedWidgetPosition(
		UInv_WidgetUtils::GetWidgetSize(Canvas),
		ItemDescriptionSize,
		UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer()));

	ItemDescriptionCPS->SetPosition(ClampedPosition);
}

void UInv_SpatialInventory::SetAttributeBreakdownSizeAndPosition(UInv_ItemAttributeBreakdown* AttributeBreakdown,
	UCanvasPanel* Canvas) const
{
	UCanvasPanelSlot* AttributeBreakdownCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(AttributeBreakdown);
	if (!IsValid(AttributeBreakdownCPS)) return;

	const FVector2D AttributeBreakdownSize = AttributeBreakdown->GetBoxSize();
	AttributeBreakdownCPS->SetSize(AttributeBreakdownSize);

	FVector2D ClampedPosition = UInv_WidgetUtils::GetClampedWidgetPosition(
		UInv_WidgetUtils::GetWidgetSize(Canvas),
		AttributeBreakdownSize,
		UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer()));

	AttributeBreakdownCPS->SetPosition(ClampedPosition);
}

bool UInv_SpatialInventory::CanEquipHoverItem(UInv_EquippedGridSlot* EquippedGridSlot,
                                              const FGameplayTag& EquipmentTypeTag) const
{
	if (!IsValid(EquippedGridSlot) || EquippedGridSlot->GetInventoryItem().IsValid()) return false;

	UInv_HoverItem* HoverItem = GetHoverItem();
	if (!IsValid(HoverItem)) return false;

	UInv_InventoryItem* HeldItem = HoverItem->GetInventoryItem();
	return HasHoverItem()
		&& IsValid(HeldItem)
		&& !HoverItem->IsStackable()
		&& HeldItem->GetItemManifest().GetItemCategory() == EInv_ItemCategory::Equippable
		&& HeldItem->GetItemManifest().GetItemType().MatchesTag(EquipmentTypeTag);
}

UInv_EquippedGridSlot* UInv_SpatialInventory::FindSlotWithEquippedItem(UInv_InventoryItem* EquippedItem) const
{
	auto* FoundEquippedGridSlot = EquippedGridSlots.FindByPredicate([EquippedItem](const UInv_EquippedGridSlot* GridSlot)
	{
		return GridSlot->GetInventoryItem() == EquippedItem;
	});
	return FoundEquippedGridSlot ? *FoundEquippedGridSlot : nullptr; 
}

void UInv_SpatialInventory::ClearSlotOfItem(UInv_EquippedGridSlot* EquippedGridSlot)
{
	if (IsValid(EquippedGridSlot))
	{
		EquippedGridSlot->SetEquippedSlottedItem(nullptr);
		EquippedGridSlot->SetInventoryItem(nullptr);
	}
}

void UInv_SpatialInventory::RemoveEquippedSlottedItem(UInv_EquippedSlottedItem* EquippedSlottedItem)
{
	if (!IsValid(EquippedSlottedItem)) return;
	if (EquippedSlottedItem->OnEquippedSlottedItemClicked.IsAlreadyBound(this, &ThisClass::EquippedSlottedItemClicked))
	{
		EquippedSlottedItem->OnEquippedSlottedItemClicked.RemoveDynamic(this, &ThisClass::EquippedSlottedItemClicked);
	}
	EquippedSlottedItem->RemoveFromParent();
}

void UInv_SpatialInventory::MakeEquippedSlottedItem(UInv_EquippedSlottedItem* EquippedSlottedItem,
	UInv_EquippedGridSlot* EquippedGridSlot, UInv_InventoryItem* ItemToEquip)
{
	if (!IsValid(EquippedGridSlot)) return;

	UInv_EquippedSlottedItem* SlottedItem = EquippedGridSlot->OnItemEquipped(
		ItemToEquip,
		EquippedSlottedItem->GetEquipmentTypeTag(),
		UInv_InventoryStatics::GetInventoryWidget(GetOwningPlayer())->GetTileSize());
	if (IsValid(SlottedItem)) SlottedItem->OnEquippedSlottedItemClicked.AddDynamic(this, &ThisClass::EquippedSlottedItemClicked);

	EquippedGridSlot->SetEquippedSlottedItem(SlottedItem);
}

void UInv_SpatialInventory::BroadcastSlotClickedDelegates(UInv_InventoryItem* ItemToEquip,
	UInv_InventoryItem* ItemToUnequip) const
{
	UInv_InventoryComponent* InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	check(IsValid(InventoryComponent));
	InventoryComponent->Server_EquipSlotClicked(ItemToEquip, ItemToUnequip);

	if (GetOwningPlayer()->GetNetMode() != NM_DedicatedServer)
	{
		InventoryComponent->OnItemEquipped.Broadcast(ItemToEquip);
		InventoryComponent->OnItemUnequipped.Broadcast(ItemToUnequip);
	}
}

bool UInv_SpatialInventory::CanSwapItems(FGameplayTag ItemToEquipTag, FGameplayTag ItemToUnequipTag,
	FGameplayTag EquippedGridSlotTag) const
{
	if (ItemToEquipTag.IsValid() && ItemToUnequipTag.IsValid() && EquippedGridSlotTag.IsValid())
	{
		if (ItemToEquipTag.MatchesTag(EquippedGridSlotTag) && ItemToUnequipTag.MatchesTag(EquippedGridSlotTag)) return true;
	}
	return false;
}

void UInv_SpatialInventory::OnItemHovered(UInv_InventoryItem* Item)
{
	const auto& Manifest = Item->GetItemManifest();
	EInv_ItemRarity Rarity = Manifest.GetItemRarity();
	UInv_ItemDescription* DescriptionWidget = GetItemDescription();
	DescriptionWidget->SetVisibility(ESlateVisibility::Collapsed);

	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(DescriptionTimer);
	FTimerDelegate DescriptionTimerDelegate;


	// This is where we create a timer that binds the Item Description to the Hovered Item's Manifest.
	DescriptionTimerDelegate.BindLambda( [this, &Manifest, Rarity, DescriptionWidget] ()
	{
		FInv_ItemData InData;

		// TODO: Instead, search Meta for this information.
		InData.Rarity = Manifest.GetItemRarity();
		InData.Enhancement = Manifest.GetItemEnhancement();
		InData.SpecialType = Manifest.GetItemSpecialType();
		GetItemDescription(InData, true)->SetVisibility(ESlateVisibility::HitTestInvisible);

		// TODO: Here is where we take all of the Display Fragments and actually display them.
		Manifest.AssimilateInventoryFragments(DescriptionWidget);
	});

	GetOwningPlayer()->GetWorldTimerManager().SetTimer(DescriptionTimer, DescriptionTimerDelegate, DescriptionTimerDelay, false);
}

void UInv_SpatialInventory::OnItemUnhovered()
{
	GetItemDescription()->SetVisibility(ESlateVisibility::Collapsed);
	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(DescriptionTimer);
}

void UInv_SpatialInventory::OnAttributeHovered(bool bShow, FGameplayTag AttributeTag, FHoverInspectResult BreakdownInfo)
{
	if (bShow)
	{
		UInv_ItemAttributeBreakdown* AttributeBreakdownWidget = GetAttributeBreakdown();
		AttributeBreakdownWidget->SetVisibility(ESlateVisibility::Collapsed);
		AttributeBreakdownWidget->SetAttributeTag(AttributeTag);
		AttributeBreakdownWidget->SetItemAttributeBreakdownData(BreakdownInfo);

		GetOwningPlayer()->GetWorldTimerManager().ClearTimer(AttributeBreakdownTimer);
		FTimerDelegate AttributeBreakdownTimerDelegate;
		AttributeBreakdownTimerDelegate.BindLambda( [this, &AttributeBreakdownWidget, BreakdownInfo]()
		{
			GetAttributeBreakdown()->SetVisibility(ESlateVisibility::HitTestInvisible);
		});
		GetOwningPlayer()->GetWorldTimerManager().SetTimer(AttributeBreakdownTimer, AttributeBreakdownTimerDelegate, AttributeInspectionTimerDelay, false);
	}
	else
	{
		GetAttributeBreakdown()->ClearAllEntries();
		GetAttributeBreakdown()->SetVisibility(ESlateVisibility::Collapsed);
		GetOwningPlayer()->GetWorldTimerManager().ClearTimer(AttributeBreakdownTimer);
	}
}

bool UInv_SpatialInventory::HasHoverItem() const
{
	if (Grid_Equippables->HasHoverItem()) return true;
	if (Grid_Consumables->HasHoverItem()) return true;
	if (Grid_Craftables->HasHoverItem()) return true;
	return false;
}

UInv_HoverItem* UInv_SpatialInventory::GetHoverItem() const
{
	if (!ActiveGrid.IsValid()) return nullptr;

	return ActiveGrid->GetHoverItem();
}

float UInv_SpatialInventory::GetTileSize() const
{
	return Grid_Equippables->GetTileSize();
}

FInv_ItemData UInv_SpatialInventory::MakeItemData(UInv_InventoryItem* InventoryItem)
{
	FInv_ItemData Data;
	Data.Rarity = InventoryItem->GetItemManifestMutable().GetItemRarity();
	Data.Enhancement = InventoryItem->GetItemManifestMutable().GetItemEnhancement();
	Data.SpecialType = InventoryItem->GetItemManifestMutable().GetItemSpecialType();
	return Data;
}

FInv_ItemData UInv_SpatialInventory::MakeEmptyItemData()
{
	FInv_ItemData Data;
	Data.Rarity = EInv_ItemRarity::Common;
	Data.Enhancement = EInv_ItemEnhancement::None;
	Data.SpecialType = EInv_ItemSpecialType::None;
	return Data;
}

UInv_ItemDescription* UInv_SpatialInventory::GetItemDescription(const FInv_ItemData& InData, bool UseRarity)
{
	if (!IsValid(ItemDescription))
	{
		ItemDescription = CreateWidget<UInv_ItemDescription>(GetOwningPlayer(), ItemDescriptionClass);
		
		CanvasPanel->AddChild(ItemDescription);
	}
	// Assign Rarity Image Background
	if (UseRarity)
	{
		ItemDescription->SetItemData(InData);
	}
	return ItemDescription;
}

UInv_ItemAttributeBreakdown* UInv_SpatialInventory::GetAttributeBreakdown()
{
	if (!IsValid(AttributeInspectBreakdown))
	{
		AttributeInspectBreakdown = CreateWidget<UInv_ItemAttributeBreakdown>(GetOwningPlayer(), AttributeInspectionClass);

		CanvasPanel->AddChild(AttributeInspectBreakdown);
	}
	return AttributeInspectBreakdown;
}



void UInv_SpatialInventory::ShowEquippables()
{
	SetActiveGrid(Grid_Equippables, Background_Equippables, Button_Equippables);
}

void UInv_SpatialInventory::ShowConsumables()
{
	SetActiveGrid(Grid_Consumables, Background_Consumables, Button_Consumables);
}

void UInv_SpatialInventory::ShowCraftables()
{
	SetActiveGrid(Grid_Craftables, Background_Craftables, Button_Craftables);
}

void UInv_SpatialInventory::DisableButton(UButton* Button)
{
	Button_Equippables->SetIsEnabled(true);
	Button_Consumables->SetIsEnabled(true);
	Button_Craftables->SetIsEnabled(true);
	Button->SetIsEnabled(false);
}

void UInv_SpatialInventory::SetActiveGrid(UInv_InventoryGrid* Grid, UWidget* Background, UButton* Button)
{
	if (ActiveGrid.IsValid())
	{
		ActiveGrid->HideCursor();
		ActiveGrid->OnHide();
	}
	ActiveGrid = Grid;
	if (ActiveGrid.IsValid()) ActiveGrid->ShowCursor();
	DisableButton(Button);
	GridSwitcher->SetActiveWidget(Grid);
	BackgroundSwitcher->SetActiveWidget(Background);
}

void UInv_SpatialInventory::BindToAttributeHoverSubsystem()
{
	AttributeHoverSubsystem = UAttributeHoverSubsystem::Get(this);
	if (AttributeHoverSubsystem)
	{
		AttributeHoverSubsystem->OnAttributeHoverChanged.AddDynamic(this, &UInv_SpatialInventory::OnGlobalAttributeHover);
	}
}

void UInv_SpatialInventory::OnGlobalAttributeHover(bool bShow, FGameplayTag AttributeTag)
{
	FHoverInspectResult HoverInspectResult;
    
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		if (APawn* PlayerPawn = PlayerController->GetPawn())
		{
			if (APlayerState* PlayerState = PlayerPawn->GetPlayerState())
			{
				if (IInv_AbilitySystemInterface* AbilityInterface = Cast<IInv_AbilitySystemInterface>(PlayerState))
				{
					if (UInv_AttributeModificationHandler* AttributeHandler = AbilityInterface->GetAttributeModificationHandlerForInventory())
					{
						HoverInspectResult = AttributeHandler->HoverInspectAttribute(AttributeTag);
					}
				}
			}
		}
	}
	OnAttributeHovered(bShow, AttributeTag, HoverInspectResult);
}
#pragma endregion
/*-------------------------------------------------------------------------*/