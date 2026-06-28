// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Combat/OperatorCombatComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerInterface.h"
#include "OperatorCharacter.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UInputMappingContext;
class USkeletalMeshComponent;
class UOperatorCombatComponent;
class UInputAction;
struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region OperatorCharacter.h_Class
UCLASS()
class CYBERSCAPE_API AOperatorCharacter : public ACharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	AOperatorCharacter();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	
	/**	Player Interface: **/
	virtual FName GetWeaponAttachmentPoint_Implementation(const FGameplayTag& WeaponType) const override;
	virtual USkeletalMeshComponent* GetMesh1P_Implementation() const override;
	virtual USkeletalMeshComponent* GetMesh3P_Implementation() const override;
	/** ~Player Interface **/

	UFUNCTION(BlueprintCallable)
	FRotator GetFixedAimRotation() const;

	UPROPERTY(BlueprintReadOnly, Category = "CYBERSCAPE|FABRIK")
	FTransform FABRIK_SocketTransform;
	
protected:
	virtual void BeginPlay() override;
	void CalculateFABRIKSocketTransform();
	virtual void BeginDestroy() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CYBERSCAPE|Combat")
	TObjectPtr<UOperatorCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CYBERSCAPE|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CYBERSCAPE|Aiming")
	float DefaultFOV;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnAim(bool bIsAiming);
	
private:
	
	void Input_CycleWeapon();
	void Input_FireWeapon_Pressed();
	void Input_FireWeapon_Released();
	void Input_ReloadWeapon();
	void Input_Aim_Pressed();
	void Input_Aim_Released();
	
	UPROPERTY(VisibleAnywhere, Category = "CYBERSCAPE|Mesh")
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	
	UPROPERTY(VisibleAnywhere, Category = "CYBERSCAPE|Camera")
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> CycleWeaponAction;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> FireWeaponAction;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> ReloadWeaponAction;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> AimWeaponAction;
};

inline void AOperatorCharacter::BeginDestroy()
{
	Super::BeginDestroy();
	if (IsValid(CombatComponent))
	{
		CombatComponent->DestroyInventory();
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/