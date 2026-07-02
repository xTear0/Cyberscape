// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
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

	void AttachToOwningPawn() const;
	void WeaponTrace(FHitResult& OutHit, float TraceLength) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CYBERSCAPE|WeaponType")
	FGameplayTag WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CYBERSCAPE|Aiming")
	float AimFOV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CYBERSCAPE|Trace")
	float TraceRadius;

	void Local_Fire(const FVector& ImpactPoint,
		const FVector& ImpactNormal,
		TEnumAsByte<EPhysicalSurface> SurfaceType,
		bool bIsFirstPerson);
	
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
};
#pragma endregion
/*-------------------------------------------------------------------------*/