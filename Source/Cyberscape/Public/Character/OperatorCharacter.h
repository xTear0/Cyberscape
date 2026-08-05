// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Combat/OperatorCombatComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerInterface.h"
#include "Types/CyberscapeTypes.h"
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
class AWeapon;
class AOperatorPlayerController;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponFirstReplicated, AWeapon*, Weapon, bool, bTargetingPlayer);
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
	virtual void OnRep_PlayerState() override;
	virtual void NotifyControllerChanged() override;
	
	/**	Player Interface: **/
	virtual FName GetWeaponAttachmentPoint_Implementation(const FGameplayTag& WeaponType) const override;
	virtual USkeletalMeshComponent* GetMesh1P_Implementation() const override;
	virtual USkeletalMeshComponent* GetMesh3P_Implementation() const override;
	virtual void WeaponReplicated_Implementation() override;
	virtual AWeapon* GetCurrentWeapon_Implementation() override;
	virtual int32 GetReserveAmmo_Implementation() const override;
	/** ~Player Interface **/

	UFUNCTION(BlueprintCallable)
	FRotator GetFixedAimRotation() const;
	
	UFUNCTION(BlueprintCallable)
	bool HasCurrentWeapon() const;

	UPROPERTY(BlueprintReadOnly, Category = "CYBERSCAPE|FABRIK")
	FTransform FABRIK_SocketTransform;

	UPROPERTY(BlueprintAssignable)
	FWeaponFirstReplicated OnWeaponFirstReplicated;
	
	bool HasWeaponFirstReplicated() const { return bWeaponFirstReplicated; }

	UFUNCTION(BlueprintCallable, Category = "CYBERSCAPE|Combat")
	void ReleaseCombatInput();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
	void CalculateFABRIKSocketTransform();
	void CalculateTurnInPlaceParameters(float DeltaTime);
	void TurnInPlace(float DeltaTime);

	bool bWeaponFirstReplicated;
	FRotator StartingAimRotation;
	float InterpAO_Yaw;

	UPROPERTY(BlueprintReadOnly, Category = "CYBERSCAPE|TurnInPlace")
	ETurningInPlace TurningStatus;

	UPROPERTY(BlueprintReadOnly, Category = "CYBERSCAPE|TurnInPlace")
	float AO_Yaw;

	UPROPERTY(BlueprintReadOnly, Category = "CYBERSCAPE|Strafing")
	float MovementOffsetYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CYBERSCAPE|Combat")
	TObjectPtr<UOperatorCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CYBERSCAPE|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CYBERSCAPE|Aiming")
	float DefaultFOV;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnAim(bool bIsAiming);
	
private:

	TWeakObjectPtr<AOperatorPlayerController> LocalPlayerController;
	
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