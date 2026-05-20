// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inv_ProxyMesh.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Delcarations	                                                       */
/*-------------------------------------------------------------------------*/
class UInv_EquipmentComponent;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ProxyMesh.h_Class
UCLASS()
class INVENTORY_API AInv_ProxyMesh : public AActor
{
	GENERATED_BODY()

public:
	AInv_ProxyMesh();

	USkeletalMeshComponent* GetProxyMesh() const { return Mesh; };

protected:
	virtual void BeginPlay() override;

	
private:

	// This is the mesh on the Player-Controller Character
	TWeakObjectPtr<USkeletalMeshComponent> SourceMesh;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInv_EquipmentComponent> EquipmentComponent;

	// Proxy Mesh seen in the Inventory Menu
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UAnimInstance> AnimClass;

	FTimerHandle TimerForNextTick;
	void DelayedInitializedOwner();
	void DelayedInitialization();
};
#pragma endregion
/*-------------------------------------------------------------------------*/