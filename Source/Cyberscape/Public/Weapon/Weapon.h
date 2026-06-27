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

	USkeletalMeshComponent* GetMesh1P() const;
	USkeletalMeshComponent* GetMesh3P() const;
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|WeaponType")
	FGameplayTag WeaponType;
private:

	// Weapon Mesh: 1st Person View
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	// Weapon Mesh: 3rd Pers
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh3P;
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/