// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Types/CyberscapeTypes.h"
#include "Weapon.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
UENUM(BlueprintType)
enum class EFireType : uint8
{
	Auto UMETA(DisplayName = "Automatic"),
	SemiAuto UMETA(DisplayName = "SemiAutomatic"),
};

class UMaterialInterface;
class UMaterialInstanceDynamic;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Weapon.h_Class
UCLASS()
class CYBERSCAPE_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

	virtual void OnRep_Instigator() override;
	
	USkeletalMeshComponent* GetMesh1P() const;
	USkeletalMeshComponent* GetMesh3P() const;

	UMaterialInstanceDynamic* GetReticleDynamicMaterialInstance();
	UMaterialInstanceDynamic* GetAmmoCounterDynamicMaterialInstance();

	void AttachToOwningPawn() const;
	void WeaponTrace(FHitResult& OutHit, float TraceLength) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CYBERSCAPE|WeaponType")
	FGameplayTag WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CYBERSCAPE|Aiming")
	float AimFOV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CYBERSCAPE|Trace")
	float TraceRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CYBERSCAPE|FireType")
	EFireType FireType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CYBERSCAPE|FireType")
	float FireTime;

	UPROPERTY(EditDefaultsOnly, Category = "CYBERSCAPE|Reticle")
	FReticleParams ReticleParams;
	
	void Local_Fire(const FVector& ImpactPoint,
		const FVector& ImpactNormal,
		TEnumAsByte<EPhysicalSurface> SurfaceType,
		bool bIsFirstPerson);

	void Auth_Fire();
	void Rep_Fire(int32 AuthAmmo);

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Ammo")
	int32 MagCapacity;
	
	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Ammo")
	int32 Ammo;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Ammo")
	int32 StartingCarriedAmmo;
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void FireEffects(const FVector& ImpactPoint,
		const FVector& ImpactNormal,
		EPhysicalSurface ImpactSurfaceType,	
		bool bIsFirstPerson);

	// Weapon Mesh: 1st Person View
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CYBERSCAPE|Weapon")
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	// Weapon Mesh: 3rd Pers
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CYBERSCAPE|Weapon")
	TObjectPtr<USkeletalMeshComponent> Mesh3P;
	
private:

	void SetMeshVisibility(APawn* OwningPawn) const;

	int32 Sequence;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Weapon")
	TObjectPtr<UMaterialInterface> ReticleMaterial;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Weapon")
	TObjectPtr<UMaterialInterface> AmmoCounterMaterial;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynMatInst_Reticle;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynMatInst_AmmoCounter;

	
};
#pragma endregion
/*-------------------------------------------------------------------------*/