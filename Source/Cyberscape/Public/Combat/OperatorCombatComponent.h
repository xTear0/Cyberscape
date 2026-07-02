// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OperatorCombatComponent.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UWeaponData;
class AWeapon;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region OperatorCombatComponent.h_Class
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CYBERSCAPE_API UOperatorCombatComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UOperatorCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Cycle to next weapon in inventory
	void Initiate_CycleWeapon();
	
	void Initiate_FireWeapon_Pressed();
	void Initiate_FireWeapon_Released();
	void Initiate_ReloadWeapon();
	void Initiate_Aim_Pressed();
	void Initiate_Aim_Released();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CYBERSCAPE|Weapon")
	TObjectPtr<UWeaponData> WeaponData;

	void Equip(AWeapon* Weapon);
	void SpawnInventory();
	void DestroyInventory();

	UPROPERTY(BlueprintReadOnly, Replicated)
	bool bAiming;

	UPROPERTY(Transient, BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentWeapon)
	TObjectPtr<AWeapon> CurrentWeapon;
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "CYBERSCAPE|Weapon")
	float TraceLength;
private:

	UFUNCTION()
	void OnRep_CurrentWeapon(AWeapon* LastWeapon);

	UPROPERTY(Transient, Replicated)
	TArray<AWeapon*> Inventory;
	
	UPROPERTY(EditDefaultsOnly, Category = "CYBERSCAPE|Weapon")
	TArray<TSubclassOf<AWeapon>> DefaultWeaponClasses;
	
	AWeapon* SpawnWeapon(TSubclassOf<AWeapon> WeaponClass) const;

	UFUNCTION(Server, Reliable)
	void Server_Aim(bool bPressed);

	UFUNCTION(Server, Reliable)
	void Server_FireWeapon(const FHitResult& Hit);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_FireWeapon(const FHitResult& Hit);

	void Local_Aim(bool bPressed);
	void Local_FireWeapon();
};
#pragma endregion
/*-------------------------------------------------------------------------*/