// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
class CYBERSCAPE_API AOperatorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AOperatorCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	
private:

	void Input_CycleWeapon();
	void Input_FireWeapon_Pressed();
	void Input_FireWeapon_Released();
	void Input_ReloadWeapon();
	void Input_Aim_Pressed();
	void Input_Aim_Released();
	
	UPROPERTY(VisibleAnywhere, Category = "CYBERSCAPE|Mesh")
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	UPROPERTY(VisibleAnywhere, Category = "CYBERSCAPE|Combat")
	TObjectPtr<UOperatorCombatComponent> CombatComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "CYBERSCAPE|Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "CYBERSCAPE|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;
	
	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> CycleWeaponAction;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> FireWeaponAction;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> ReloadWeaponAction;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> AimWeaponAction;
};
#pragma endregion
/*-------------------------------------------------------------------------*/