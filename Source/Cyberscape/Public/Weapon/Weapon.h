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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CYBERSCAPE|WeaponType")
	FGameplayTag WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CYBERSCAPE|Aiming")
	float AimFOV;
	
protected:

	virtual void BeginPlay() override;


private:

	// Weapon Mesh: 1st Person View
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	// Weapon Mesh: 3rd Pers
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh3P;

	void SetMeshVisibility(APawn* OwningPawn) const;
};
#pragma endregion
/*-------------------------------------------------------------------------*/