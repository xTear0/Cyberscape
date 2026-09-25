// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "InventoryManagement/Components/TINV_InventoryComponent.h"
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
		Server_AddStacksToItem(ItemComponent, Result.TotalRoomToFill, Result.Remainder);
	}
	else if (Result.TotalRoomToFill > 0)
	{
		// This item type does not exist in the inventory. Create a new one.
		Server_AddNewItem(ItemComponent, Result.TotalRoomToFill ? Result.TotalRoomToFill : 0);
	}
	
	// TODO: Actually add the item to the inventory.
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
	
	// TODO: Tell the item component to destroy its owning actor.
}

void UTINV_InventoryComponent::Server_AddStacksToItem_Implementation(
	UTINV_ItemComponent* ItemComponent,	int32 StackCount, int32 Remainder)
{
	const FGameplayTag& ItemTag = IsValid(ItemComponent) ? ItemComponent->GetItemManifest().GetItemID() : FGameplayTag::EmptyTag;
	UTINV_InventoryItem* Item = InventoryList.FindFirstItemByTag(ItemTag);
	if (!IsValid(Item)) return;

	Item->SetTotalStackCount(Item->GetTotalStackCount() + Remainder);

	// TODO: Destroy Item if Remainder == 0.
	// Otherwise, update the stack count of the item on the ground.
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
	InventoryMenu->SetVisibility(ESlateVisibility::Visible);
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
	InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
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
