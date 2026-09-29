// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagement/FastArray/TINV_FastArray.h"
#include "Items/Manifest/TINV_ItemManifest.h"
#include "Types/TINV_StructTypes.h"
#include "TINV_InventoryComponent.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTINV_InventoryItem;
class UTINV_InventoryBase;
class UTINV_ItemComponent;
struct FTINV_SlotAvailabilityResult;
class UTINV_ItemDataTable;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTINVItemChange, UTINV_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTINVNoRoomInInventory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTINV_StackChange, const FTINV_SlotAvailabilityResult&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTINV_DropRequest, bool, bDropAll);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTINV_HotbarSwapRequest, int32, HotbarIndex);
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryComponent.h_Class
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class TECHYINV_API UTINV_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="TECHY|Inventory")
	void CloseInventoryMenu(bool Quiet = false);
	
	UTINV_InventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "TECHY|Inventory")
	void TryAddItem(UTINV_ItemComponent* ItemComponent);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "TECHY|Inventory")
	void GridTryDropItem(bool bDropAll);

	UFUNCTION(Server, Reliable)
	void Server_AddNewItem(UTINV_ItemComponent* ItemComponent, int32 StackCount);

	UFUNCTION(Server, Reliable)
	void Server_AddStacksToItem(UTINV_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder);

	UFUNCTION(Server, Reliable)
	void Server_DropItem(UTINV_InventoryItem* Item, int32 StackCount);
	
	void ToggleInventoryMenu();
	bool IsInventoryOpen() const { return bInventoryMenuOpen; }

	void AddRepSubObj(UObject* SubObj);

	FTINVItemChange OnItemAdded;
	FTINVItemChange OnItemRemoved;
	FTINVNoRoomInInventory NoRoomInInventory;
	FTINV_StackChange OnStackChange;
	FTINV_DropRequest OnDropRequested;

	void GridTrySwapWithHotbar(int32 HotbarIndex);
	FTINV_HotbarSwapRequest OnHotbarSwapRequested;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory")
	TObjectPtr<UTINV_ItemDataTable> ItemDataTable;
	
	UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory")
	TObjectPtr<USoundBase> InventoryOpenSound;

	UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory")
	TObjectPtr<USoundBase> InventoryCloseSound;
	
	TWeakObjectPtr<APlayerController> OwningController;
	
	void ConstructInventory();

	UPROPERTY(Replicated)
	FTINV_InventoryFastArray InventoryList;
	
	UPROPERTY()
	TObjectPtr<UTINV_InventoryBase> InventoryMenu;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TSubclassOf<UTINV_InventoryBase> InventoryMenuClass;

	bool bInventoryMenuOpen;
	void OpenInventoryMenu();

	void SpawnDroppedItem(UTINV_InventoryItem* Item, int32 StackCount);
	const FTINV_ItemDataDefinition* GetItemData(const FTINV_ItemManifest& Manifest) const;

	float DroppedItemSpawnDistance{100.f};
};
#pragma endregion
/*-------------------------------------------------------------------------*/
