// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Types/CyberscapeTypes.h"
#include "OperatorCombatComponent.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UWeaponData;
class AWeapon;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReticleChanged,
	UMaterialInstanceDynamic*,
	ReticleDynMatInst,
	const FReticleParams&,
	ReticleParams,
	bool,
	bCurrentlyTargettingPlayer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAmmoCounterChanged,
	UMaterialInstanceDynamic*, AmmoCounterDynMatInst,
	int32, RoundsCurrent,
	int32, RoundsMax);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRoundFired, int32, RoundsCurrent, int32, RoundsMax, int32, RoundsInReserve);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAimingStatusChanged, bool, bIsAiming);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetingPlayerStatusChanged, bool, bIsTargeting);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCurrentWeaponReserveAmmoChanged, int32, RoundsInReserve, int32, RoundsInWeapon, UMaterialInterface*, WeaponIconMaterial);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region OperatorCombatComponent.h_Class
UCLASS()
class CYBERSCAPE_API UOperatorCombatComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UOperatorCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure, Category = "CYBERSCAPE|Combat")
	static UOperatorCombatComponent* FindCombatComponent(const AActor* Actor)
		{ return (IsValid(Actor) ? Actor->FindComponentByClass<UOperatorCombatComponent>() : nullptr ); }
	
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

	void InitializeWeaponWidgets() const; 

	UPROPERTY(BlueprintAssignable)
	FReticleChanged OnReticleChanged;

	UPROPERTY(BlueprintAssignable)
	FAmmoCounterChanged OnAmmoCounterChanged;

	UPROPERTY(BlueprintAssignable)
	FRoundFired OnRoundFired;
	
	UPROPERTY(BlueprintAssignable)
	FAimingStatusChanged OnAimingStatusChanged;

	UPROPERTY(BlueprintAssignable)
	FTargetingPlayerStatusChanged OnTargetingPlayerStatusChanged;

	UPROPERTY(BlueprintAssignable)
	FCurrentWeaponReserveAmmoChanged OnCurrentWeaponReserveAmmoChanged;
	
	bool bHitPlayer;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentReserveAmmo)
	int32 CurrentReserveAmmo;

	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "CYBERSCAPE|Weapon")
	float TraceLength;
private:
	
	TMap<FGameplayTag, int32> ReserveAmmo;
	
	bool bHitPlayerLastFrame;
	bool bTriggerPressed;
	FTimerHandle FireTimer;
	void FireTimerFinished();
	
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
	void Multicast_FireWeapon(const FHitResult& Hit, int32 AuthAmmo);

	UFUNCTION()
	void OnRep_CurrentReserveAmmo();
	
	void Local_Aim(bool bPressed);
	void Local_FireWeapon();
};
#pragma endregion
/*-------------------------------------------------------------------------*/