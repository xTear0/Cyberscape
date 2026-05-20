// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Widgets/ItemDescription/Inv_ItemDescription.h"
#include "Inv_ItemComponent.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemComponent.h_Class
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UInv_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInv_ItemComponent();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	void InitItemManifest(FInv_ItemManifest CopyOfManifest);
	FInv_ItemManifest GetItemManifest() const { return ItemManifest; }
	FString  GetPickupMessage() const { return PickupMessage; }
	void PickedUp();

	void SetManifest(FInv_ItemManifest NewManifest) { ItemManifest = NewManifest; };
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OnPickedUp();
	
private:
	UPROPERTY(Replicated, EditAnywhere, Category = "Inventory")
	FInv_ItemManifest ItemManifest;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FString PickupMessage;
};
#pragma endregion
/*-------------------------------------------------------------------------*/