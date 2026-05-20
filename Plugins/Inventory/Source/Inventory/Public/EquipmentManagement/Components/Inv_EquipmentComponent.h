// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inv_EquipmentComponent.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Delcarations	                                                       */
/*-------------------------------------------------------------------------*/
struct FGameplayTag;
class UInv_InventoryComponent;
class UInv_InventoryItem;
class APlayerController;
class USkeletalMeshComponent;
struct FInv_ItemManifest;
struct FInv_EquipmentFragment;
class AInv_EquipActor;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_EquipmentComponent.h_Class
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UInv_EquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	void SetOwningSkeletalMesh(USkeletalMeshComponent* OwningMesh);
	void SetIsProxy(bool bProxy) { bIsProxy = bProxy; }
	void InitializeOwner(APlayerController* PlayerController);
	
protected:

	virtual void BeginPlay() override;

private:

	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
	TWeakObjectPtr<APlayerController> OwningPlayerController;
	TWeakObjectPtr<USkeletalMeshComponent> OwningSkeletalMesh;

	UFUNCTION()
	void OnItemEquipped(UInv_InventoryItem* EquippedItem);

	UFUNCTION()
	void OnItemUnequipped(UInv_InventoryItem* UnequippedItem);

	void InitInventoryComponent();
	void InitPlayerController();

	void ClearWeaponSkeletalMesh() const;
	
	AInv_EquipActor* SpawnEquippedActor(FInv_EquipmentFragment* EquipmentFragment, const FInv_ItemManifest& Manifest, USkeletalMeshComponent* AttachMesh);

	UPROPERTY()
	TArray<TObjectPtr<AInv_EquipActor>> EquippedActors;

	AInv_EquipActor* FindEquippedActorByTag(const FGameplayTag& EquipmentTypeTag);
	void RemoveEquippedActorByTag(const FGameplayTag& EquipmentTypeTag, const bool IsWeapon);

	UFUNCTION()
	void OnPossessedPawnChange(APawn* OldPawn, APawn* NewPawn);

	bool bIsProxy{false};
};
#pragma endregion
/*-------------------------------------------------------------------------*/