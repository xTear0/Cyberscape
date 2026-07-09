// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/CyberscapeTypes.h"
#include "OperatorReticle.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UImage;
class UMaterialInstanceDynamic;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region OperatorReticle.h_Class
UCLASS()
class CYBERSCAPE_API UOperatorReticle : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Reticle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_AmmoCounter;

private:

	TWeakObjectPtr<UMaterialInstanceDynamic> CurrentReticle_DynMatInst;
	TWeakObjectPtr<UMaterialInstanceDynamic> CurrentAmmoCounter_DynMatInst;
	FReticleParams CurrentReticleParams;
	
	float BaseCornerScaleFactor;
	float BaseShapeCutFactor;
	float _BaseCornerScaleFactor_RoundFired;
	float _BaseShapeCutFactor_RoundFired;
	float _BaseCornerScaleFactor_Aiming;
	float _BaseShapeCutFactor_Aiming;
	float _BaseCornerScaleFactor_TargetingPlayer;
	bool bAiming;
	bool bTargetingPlayer;
		
	UFUNCTION()
	void OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);

	UFUNCTION()
	void OnWeaponFirstReplicated(AWeapon* Weapon, bool bIsTargetingPlayer);

	UFUNCTION()
	void OnReticleChanged(UMaterialInstanceDynamic* ReticleDynMatInst, const FReticleParams& ReticleParams, bool bCurrentlyTargetingPlayer);

	UFUNCTION()
	void OnAmmoCounterChanged(UMaterialInstanceDynamic* AmmoCounterDynMatInst, int32 RoundsCurrent, int32 RoundsMax);

	UFUNCTION()
	void OnRoundFired(int32 RoundsCurrent, int32 RoundsMax, int32 RoundsInReserve);

	UFUNCTION()
	void OnAimingStatusChanged(bool IsAiming);

	UFUNCTION()
	void OnTargetingPlayerStatusChanged(bool IsTargetingPlayer);
};
#pragma endregion
/*-------------------------------------------------------------------------*/
