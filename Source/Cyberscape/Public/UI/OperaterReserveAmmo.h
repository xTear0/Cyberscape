// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OperaterReserveAmmo.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;
class UImage;
class AWeapon;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region OperaterReserveAmmo.h_Class
UCLASS()
class CYBERSCAPE_API UOperaterReserveAmmo : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_WeaponIcon;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Ammo;
private:
	
	UFUNCTION()
	void OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);

	UFUNCTION()
	void OnCurrentReserveAmmoChanged(int32 RoundsInReserve, int32 RoundsInWeapon);

	UFUNCTION()
	void OnRoundFired(int32 RoundsCurrent, int32 RoundsMax, int32 RoundsInReserve);

	UFUNCTION()
	void OnWeaponFirstReplicated(AWeapon* Weapon, bool bTargetingPlayer);
};
#pragma endregion
/*-------------------------------------------------------------------------*/
