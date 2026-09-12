// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "InventoryManagement/Components/TINV_InventoryComponent.h"

#include "Notifications/CUI_NotificationManager.h"
#include "Widgets/Inventory/InventoryBase/TINV_InventoryBase.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryComponent.cpp_Functions
UTINV_InventoryComponent::UTINV_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTINV_InventoryComponent::TryAddItem(UTINV_ItemComponent* ItemComponent)
{
	NoRoomInInventory.Broadcast();
	
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	if (UCUI_NotificationManager* Notifs = UCUI_NotificationManager::Get(PC))
	{
		Notifs->PostWarning(
			NSLOCTEXT("TechyInventory", "InventoryWarning", "Inventory full."),
			nullptr,
			-1.f,
			TEXT("Warn.InventoryFull"));
	}
}

void UTINV_InventoryComponent::ToggleInventoryMenu()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	if (UCUI_NotificationManager* Notifs = UCUI_NotificationManager::Get(PC))
	{
		Notifs->PostError(
			NSLOCTEXT("TechyInventory", "Test", "Inventory Toggled."),
			nullptr,
			-1.f,
			TEXT("Error.InventoryOpen"));
	}
	
	if (bInventoryMenuOpen)
	{
		CloseInventoryMenu();
	}
	else
	{
		OpenInventoryMenu();
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
	CloseInventoryMenu();
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
}

void UTINV_InventoryComponent::CloseInventoryMenu()
{
	if (!IsValid(InventoryMenu)) return;
	InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
	bInventoryMenuOpen = false;

	if (!OwningController.IsValid()) return;
	FInputModeGameOnly InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor(false);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
