// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "InventoryManagement/Components/TINV_InventoryComponent.h"

#include "ItemData/TINV_ItemDataTable.h"
#include "Items/TINV_InventoryItem.h"
#include "Items/Components/TINV_ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Notifications/CUI_NotificationManager.h"
#include "Widgets/Inventory/InventoryBase/TINV_InventoryBase.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryComponent.cpp_Functions
UTINV_InventoryComponent::UTINV_InventoryComponent() : InventoryList(this)
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
	bInventoryMenuOpen = false;
}

void UTINV_InventoryComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, InventoryList);
}

void UTINV_InventoryComponent::TryAddItem(UTINV_ItemComponent* ItemComponent)
{
	FTINV_SlotAvailabilityResult Result = InventoryMenu->HasRoomForItem(ItemComponent);

	UTINV_InventoryItem* FoundItem = InventoryList.FindFirstItemByTag(ItemComponent->GetItemManifest().GetItemID());
	Result.Item = FoundItem;
	
	if (Result.TotalRoomToFill == 0)
	{
		UCUI_NotificationManager::PostWarning(this, NSLOCTEXT("Cyberscape", "InventoryWarning", "Inventory Full."), true);
		return;
	}

	if (Result.Item.IsValid() && Result.bStackable)
	{
		// Add stacks to an item that already exists in the inventory. Just update stack count.
		// Not create a new item of this type.
		OnStackChange.Broadcast(Result);
		Server_AddStacksToItem(ItemComponent, Result.TotalRoomToFill, Result.Remainder);
	}
	else if (Result.TotalRoomToFill > 0)
	{
		// This item type does not exist in the inventory. Create a new one.
		Server_AddNewItem(ItemComponent, Result.TotalRoomToFill ? Result.TotalRoomToFill : 0);
	}
	
	// TODO: Actually add the item to the inventory.
}

void UTINV_InventoryComponent::GridTrySwapWithHotbar(const int32 HotbarIndex)
{
	if (!bInventoryMenuOpen) return;
	OnHotbarSwapRequested.Broadcast(HotbarIndex);
}

void UTINV_InventoryComponent::GridTryDropItem(const bool bDropAll)
{
	if (!bInventoryMenuOpen) return;
	OnDropRequested.Broadcast(bDropAll);
}

void UTINV_InventoryComponent::Server_AddNewItem_Implementation(
	UTINV_ItemComponent* ItemComponent, int32 StackCount)
{
	UTINV_InventoryItem* NewItem = InventoryList.AddEntry(ItemComponent);
	NewItem->SetTotalStackCount(StackCount);

	if (GetOwner()->GetNetMode() == NM_ListenServer || GetOwner()->GetNetMode() == NM_Standalone)
	{
		OnItemAdded.Broadcast(NewItem);
	}
	
	ItemComponent->PickedUp();
}

void UTINV_InventoryComponent::Server_AddStacksToItem_Implementation(
	UTINV_ItemComponent* ItemComponent,	int32 StackCount, int32 Remainder)
{
	const FGameplayTag& ItemTag = IsValid(ItemComponent) ? ItemComponent->GetItemManifest().GetItemID() : FGameplayTag::EmptyTag;
	UTINV_InventoryItem* Item = InventoryList.FindFirstItemByTag(ItemTag);
	if (!IsValid(Item)) return;

	Item->SetTotalStackCount(Item->GetTotalStackCount() + StackCount);

	if (Remainder == 0)
	{
		ItemComponent->PickedUp();
	}
	else
	{
		ItemComponent->GetItemManifestMutable().UpdateStackCount(Remainder);
	}
}


void UTINV_InventoryComponent::Server_DropItem_Implementation(UTINV_InventoryItem* Item, int32 StackCount)
{
	if (!IsValid(Item)) return;
	StackCount = FMath::Clamp(StackCount, 1, FMath::Max(1, Item->GetTotalStackCount()));
	
	const int32 NewStackCount = Item->GetTotalStackCount() - StackCount;
	if (NewStackCount <= 0)
	{
		InventoryList.RemoveEntry(Item);
	}
	else
	{
		Item->SetTotalStackCount(NewStackCount);
	}
	SpawnDroppedItem(Item, StackCount);
}

void UTINV_InventoryComponent::SpawnDroppedItem(UTINV_InventoryItem* Item, int32 StackCount)
{
	const APawn* OwningPawn = OwningController->GetPawn();
	FVector ForwardVector = OwningPawn->GetActorForwardVector();
	FVector SpawnLocation = OwningPawn->GetActorLocation() + ForwardVector * DroppedItemSpawnDistance;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FTINV_ItemManifest DropManifest = Item->GetItemManifest();
	DropManifest.UpdateStackCount(StackCount);

	const FTINV_ItemDataDefinition* ItemData = GetItemData(DropManifest);
	DropManifest.SpawnPickupActor(this, ItemData->ItemRespawnClass, SpawnLocation, SpawnRotation);
}

const FTINV_ItemDataDefinition* UTINV_InventoryComponent::GetItemData(const FTINV_ItemManifest& Manifest) const
{
	return ItemDataTable ? ItemDataTable->GetDataByTag(Manifest.GetItemID()) : nullptr;
}

void UTINV_InventoryComponent::ToggleInventoryMenu()
{
	if (bInventoryMenuOpen)
	{
		CloseInventoryMenu();
	}
	else
	{
		OpenInventoryMenu();
	}
}

void UTINV_InventoryComponent::AddRepSubObj(UObject* SubObj)
{
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && IsValid(SubObj))
	{
		AddReplicatedSubObject(SubObj);
	}
}

void UTINV_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	check(ItemDataTable)
	ConstructInventory();
}

void UTINV_InventoryComponent::ConstructInventory()
{
	OwningController = Cast<APlayerController>(GetOwner());
	checkf(OwningController.IsValid(), TEXT("Techy Inventory Component should have a Player Controller as Owner."));
	if (!OwningController->IsLocalController()) return;

	InventoryMenu = CreateWidget<UTINV_InventoryBase>(OwningController.Get(), InventoryMenuClass);
	InventoryMenu->AddToViewport();
	CloseInventoryMenu(true);
}

void UTINV_InventoryComponent::OpenInventoryMenu()
{
	if (!IsValid(InventoryMenu)) return;
	InventoryMenu->SetMenuOpen(true);
	bInventoryMenuOpen = true;

	if (!OwningController.IsValid()) return;
	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(InventoryMenu->TakeWidget());
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor(true);

	if (InventoryOpenSound)
	{
		UGameplayStatics::PlaySound2D(this, InventoryOpenSound);
	}
}

void UTINV_InventoryComponent::CloseInventoryMenu(bool Quiet)
{
	if (!IsValid(InventoryMenu)) return;
	InventoryMenu->SetMenuOpen(false, /*bInstant*/ Quiet);
	bInventoryMenuOpen = false;

	if (!OwningController.IsValid()) return;
	FInputModeGameOnly InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor(false);

	if (InventoryCloseSound && !Quiet)
	{
		UGameplayStatics::PlaySound2D(this, InventoryCloseSound);
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
