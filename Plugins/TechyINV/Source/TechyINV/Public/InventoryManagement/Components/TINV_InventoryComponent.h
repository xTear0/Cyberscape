// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagement/FastArray/TINV_FastArray.h"
#include "TINV_InventoryComponent.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTINV_InventoryItem;
class UTINV_InventoryBase;
class UTINV_ItemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTINVItemChange, UTINV_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTINVNoRoomInInventory);
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
	UTINV_InventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "TECHY|Inventory")
	void TryAddItem(UTINV_ItemComponent* ItemComponent);

	UFUNCTION(Server, Reliable)
	void Server_AddNewItem(UTINV_ItemComponent* ItemComponent, int32 StackCount);

	UFUNCTION(Server, Reliable)
	void Server_AddStacksToItem(UTINV_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder);
	
	void ToggleInventoryMenu();
	bool IsInventoryOpen() const { return bInventoryMenuOpen; }

	void AddRepSubObj(UObject* SubObj);

	FTINVItemChange OnItemAdded;
	FTINVItemChange OnItemRemoved;
	FTINVNoRoomInInventory NoRoomInInventory;
	
protected:
	virtual void BeginPlay() override;

private:

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
	void CloseInventoryMenu();
};
#pragma endregion
/*-------------------------------------------------------------------------*/
