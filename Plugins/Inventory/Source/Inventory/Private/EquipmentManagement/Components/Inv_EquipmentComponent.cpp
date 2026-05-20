// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "EquipmentManagement/Components/Inv_EquipmentComponent.h"
#include "EquipmentManagement/EquipActor/Inv_EquipActor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Items/Inv_InventoryItem.h"
#include "Items/Fragments/Inv_ItemFragment.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions			                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_EquipmentComponent.cpp_Functions
void UInv_EquipmentComponent::SetOwningSkeletalMesh(USkeletalMeshComponent* OwningMesh)
{
	OwningSkeletalMesh = OwningMesh;
}

void UInv_EquipmentComponent::InitializeOwner(APlayerController* PlayerController)
{
	if (IsValid(PlayerController))
	{
		OwningPlayerController = PlayerController;
	}
	InitInventoryComponent();
}

void UInv_EquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	InitPlayerController();
}

void UInv_EquipmentComponent::InitPlayerController()
{
	if (OwningPlayerController = Cast<APlayerController>(GetOwner()); OwningPlayerController.IsValid())
	{
		if (ACharacter* OwningCharacter = Cast<ACharacter>(OwningPlayerController->GetPawn()); IsValid(OwningCharacter))
		{
			OnPossessedPawnChange(nullptr, OwningCharacter);
		} else
		{
			OwningPlayerController->OnPossessedPawnChanged.AddDynamic(this, &ThisClass::UInv_EquipmentComponent::OnPossessedPawnChange);
		}
	}	
}

void UInv_EquipmentComponent::ClearWeaponSkeletalMesh() const
{
	UActorComponent* BindWeaponComponent = OwningSkeletalMesh->GetOwner()->FindComponentByTag(USkeletalMeshComponent::StaticClass(), FName("BindWeapon"));
	if (BindWeaponComponent) 
	{
		if (USkeletalMeshComponent* BindWeaponSKM = Cast<USkeletalMeshComponent>(BindWeaponComponent))
		{
			BindWeaponSKM->SetSkeletalMesh(nullptr);
			BindWeaponSKM->SetVisibility(false);
		}
	}
}

void UInv_EquipmentComponent::OnPossessedPawnChange(APawn* OldPawn, APawn* NewPawn)
{
	if (ACharacter* OwningCharacter = Cast<ACharacter>(OwningPlayerController->GetPawn()); IsValid(OwningCharacter))
	{
		OwningSkeletalMesh = OwningCharacter->GetMesh();
	}
	InitInventoryComponent();
}

void UInv_EquipmentComponent::InitInventoryComponent()
{
	InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(OwningPlayerController.Get());
	if (!InventoryComponent.IsValid()) return;

	if (!InventoryComponent->OnItemEquipped.IsAlreadyBound(this, &ThisClass::OnItemEquipped))
	{
		InventoryComponent->OnItemEquipped.AddDynamic(this, &ThisClass::OnItemEquipped);
	}

	if (!InventoryComponent->OnItemUnequipped.IsAlreadyBound(this, &ThisClass::OnItemUnequipped))
	{
		InventoryComponent->OnItemUnequipped.AddDynamic(this, &ThisClass::OnItemUnequipped);
	}
}

AInv_EquipActor* UInv_EquipmentComponent::SpawnEquippedActor(FInv_EquipmentFragment* EquipmentFragment,
                                                             const FInv_ItemManifest& Manifest, USkeletalMeshComponent* AttachMesh)
{
	AInv_EquipActor* SpawnedEquipActor = EquipmentFragment->SpawnAttachedActor(AttachMesh, bIsProxy);
	SpawnedEquipActor->SetEquipmentType(EquipmentFragment->GetEquipmentType());
	SpawnedEquipActor->SetOwner(GetOwner());
	EquipmentFragment->SetEquippedActor(SpawnedEquipActor);
	return SpawnedEquipActor;
}

AInv_EquipActor* UInv_EquipmentComponent::FindEquippedActorByTag(const FGameplayTag& EquipmentTypeTag)
{
	auto FoundActor = EquippedActors.FindByPredicate([&EquipmentTypeTag](const AInv_EquipActor* EquippedActor)
	{
		return EquippedActor->GetEquipmentType().MatchesTagExact(EquipmentTypeTag);
	});
	return FoundActor ? *FoundActor : nullptr;
}

void UInv_EquipmentComponent::RemoveEquippedActorByTag(const FGameplayTag& EquipmentTypeTag, const bool IsWeapon)
{
	if (AInv_EquipActor* EquippedActor = FindEquippedActorByTag(EquipmentTypeTag))
	{
		EquippedActors.Remove(EquippedActor);
		if (IsWeapon) ClearWeaponSkeletalMesh();
		EquippedActor->Destroy();
	}
}

void UInv_EquipmentComponent::OnItemEquipped(UInv_InventoryItem* EquippedItem)
{
	if (!IsValid(EquippedItem)) return;
	if (!OwningPlayerController->HasAuthority()) return;

	FInv_ItemManifest& ItemManifest = EquippedItem->GetItemManifestMutable();
	FInv_EquipmentFragment* EquipmentFragment = ItemManifest.GetFragmentOfTypeMutable<FInv_EquipmentFragment>();
	if (!EquipmentFragment) return;

	if (!bIsProxy) EquipmentFragment->OnEquip(OwningPlayerController.Get());
	if (!OwningSkeletalMesh.IsValid()) return;
	AInv_EquipActor* SpawnedEquipActor = SpawnEquippedActor(EquipmentFragment, ItemManifest, OwningSkeletalMesh.Get());

	EquippedActors.Add(SpawnedEquipActor);
}

void UInv_EquipmentComponent::OnItemUnequipped(UInv_InventoryItem* UnequippedItem)
{
	if (!IsValid(UnequippedItem)) return;
	if (!OwningPlayerController->HasAuthority()) return;
	
	FInv_ItemManifest& ItemManifest = UnequippedItem->GetItemManifestMutable();
	FInv_EquipmentFragment* EquipmentFragment = ItemManifest.GetFragmentOfTypeMutable<FInv_EquipmentFragment>();
	if (!EquipmentFragment) return;

	if (!bIsProxy) EquipmentFragment->OnUnequip(OwningPlayerController.Get());
	RemoveEquippedActorByTag(EquipmentFragment->GetEquipmentType(), EquipmentFragment->GetIsWeapon());
}
#pragma endregion
/*-------------------------------------------------------------------------*/
