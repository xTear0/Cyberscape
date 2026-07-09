// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/OperatorReticle.h"
#include "Character/OperatorCharacter.h"
#include "Components/Image.h"
#include "Weapon/Weapon.h"
/*-------------------------------------------------------------------------*/


namespace Ammo
{
	const FName Rounds_Current = FName("Rounds_Current");
	const FName Rounds_Max = FName("Rounds_Max");
}

namespace Reticle
{
	const FName RoundedCornerScale = FName("RoundedCornerScale");
	const FName ShapeCutThickness = FName("ShapeCutThickness");
	const FName Inner_RGBA = FName("Inner_RGBA");
}



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region OperatorReticle.cpp_Functions
void UOperatorReticle::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Image_Reticle->SetRenderOpacity(0.f);
	Image_AmmoCounter->SetRenderOpacity(0.f);
	_BaseCornerScaleFactor_RoundFired = 0.f;
	_BaseShapeCutFactor_RoundFired = 0.f;
	_BaseCornerScaleFactor_Aiming =  0.f;
	_BaseShapeCutFactor_Aiming = 0.f;
	bAiming = false;
	bTargetingPlayer = false;
	
	GetOwningPlayer()->OnPossessedPawnChanged.AddDynamic(this, &ThisClass::OnPossessedPawnChanged);

	AOperatorCharacter* OperatorCharacter = Cast<AOperatorCharacter>(GetOwningPlayer()->GetPawn());
	if (!IsValid(OperatorCharacter)) return;

	UOperatorCombatComponent* CombatComponent = UOperatorCombatComponent::FindCombatComponent(OperatorCharacter);
	if (!IsValid(CombatComponent)) return;

	OnPossessedPawnChanged(nullptr, OperatorCharacter);

	if (OperatorCharacter->HasWeaponFirstReplicated())
	{
		AWeapon* Weapon = IPlayerInterface::Execute_GetCurrentWeapon(OperatorCharacter);
		if (IsValid(Weapon))
		{
			OnReticleChanged(Weapon->GetReticleDynamicMaterialInstance(), Weapon->ReticleParams, CombatComponent->bHitPlayer);
			OnAmmoCounterChanged(Weapon->GetAmmoCounterDynamicMaterialInstance(),
				Weapon->Ammo, Weapon->MagCapacity);
		}
	}
	else
	{
		OperatorCharacter->OnWeaponFirstReplicated.AddDynamic(this, &ThisClass::OnWeaponFirstReplicated);	
	}
	if (OperatorCharacter->HasAuthority())
	{
		AWeapon* Weapon = IPlayerInterface::Execute_GetCurrentWeapon(OperatorCharacter);
		if (IsValid(Weapon))
		{
			OnReticleChanged(Weapon->GetReticleDynamicMaterialInstance(), Weapon->ReticleParams, CombatComponent->bHitPlayer);
			OnAmmoCounterChanged(Weapon->GetAmmoCounterDynamicMaterialInstance(),
				Weapon->Ammo, Weapon->MagCapacity);
		}
	}
}

void UOperatorReticle::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	_BaseCornerScaleFactor_RoundFired = FMath::FInterpTo(
		_BaseCornerScaleFactor_RoundFired,
		0.f,
		InDeltaTime,
		CurrentReticleParams.RoundFiredInterpSpeed);

	_BaseShapeCutFactor_RoundFired = FMath::FInterpTo(
	_BaseShapeCutFactor_RoundFired,
	0.f,
	InDeltaTime,
	CurrentReticleParams.RoundFiredInterpSpeed);

	_BaseCornerScaleFactor_Aiming = FMath::FInterpTo(
		_BaseCornerScaleFactor_Aiming,
		bAiming ? CurrentReticleParams.ScaleFactor_Aiming : CurrentReticleParams.ScaleFactor_NotAiming,
		InDeltaTime,
		CurrentReticleParams.AimingInterpSpeed);

	_BaseShapeCutFactor_Aiming = FMath::FInterpTo(
		_BaseShapeCutFactor_Aiming,
		bAiming ? CurrentReticleParams.ShapeCutFactor_Aiming : CurrentReticleParams.ShapeCutFactor_NotAiming,
		InDeltaTime,
		CurrentReticleParams.AimingInterpSpeed);

	_BaseCornerScaleFactor_TargetingPlayer = FMath::FInterpTo(
		_BaseCornerScaleFactor_TargetingPlayer,
		bTargetingPlayer ? CurrentReticleParams.ScaleFactor_Targeting : CurrentReticleParams.ScaleFactor_NotTargeting,
		InDeltaTime,
		CurrentReticleParams.TargetingPlayerInterpSpeed);
	
	BaseCornerScaleFactor = _BaseCornerScaleFactor_RoundFired + _BaseCornerScaleFactor_Aiming + _BaseCornerScaleFactor_TargetingPlayer;
	BaseShapeCutFactor = _BaseShapeCutFactor_RoundFired + _BaseShapeCutFactor_Aiming;

	if (CurrentReticle_DynMatInst.IsValid())
	{
		CurrentReticle_DynMatInst->SetScalarParameterValue(Reticle::RoundedCornerScale, BaseCornerScaleFactor);
		CurrentReticle_DynMatInst->SetScalarParameterValue(Reticle::ShapeCutThickness, BaseShapeCutFactor);
	}
}

void UOperatorReticle::OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	// Unbind from Delegates on the OldPawn,
	UOperatorCombatComponent* OldPawnCombat = UOperatorCombatComponent::FindCombatComponent(OldPawn);
	if (IsValid(OldPawnCombat))
	{
		OldPawnCombat->OnReticleChanged.RemoveDynamic(this, &ThisClass::OnReticleChanged);
		OldPawnCombat->OnAmmoCounterChanged.RemoveDynamic(this, &ThisClass::OnAmmoCounterChanged);
		OldPawnCombat->OnRoundFired.RemoveDynamic(this, &ThisClass::OnRoundFired);
		OldPawnCombat->OnAimingStatusChanged.RemoveDynamic(this, &ThisClass::OnAimingStatusChanged);
		OldPawnCombat->OnTargetingPlayerStatusChanged.RemoveDynamic(this, &ThisClass::OnTargetingPlayerStatusChanged);
	}
	// Bind to Delegates on the Operator Combat Component
	UOperatorCombatComponent* NewPawnCombat = UOperatorCombatComponent::FindCombatComponent(NewPawn);
	if (IsValid(NewPawnCombat))
	{
		Image_Reticle->SetRenderOpacity(1.f);
		Image_AmmoCounter->SetRenderOpacity(1.f);
		NewPawnCombat->OnReticleChanged.AddDynamic(this, &ThisClass::OnReticleChanged);
		NewPawnCombat->OnAmmoCounterChanged.AddDynamic(this, &ThisClass::OnAmmoCounterChanged);
		NewPawnCombat->OnRoundFired.AddDynamic(this, &ThisClass::OnRoundFired);
		NewPawnCombat->OnAimingStatusChanged.AddDynamic(this, &ThisClass::OnAimingStatusChanged);
		NewPawnCombat->OnTargetingPlayerStatusChanged.AddDynamic(this, &ThisClass::OnTargetingPlayerStatusChanged);
	}
}

void UOperatorReticle::OnWeaponFirstReplicated(AWeapon* Weapon, bool bIsTargetingPlayer)
{	
	// Get Dynamic Material Instances from the Weapon.
	OnReticleChanged(Weapon->GetReticleDynamicMaterialInstance(), Weapon->ReticleParams, bIsTargetingPlayer);
	OnAmmoCounterChanged(Weapon->GetAmmoCounterDynamicMaterialInstance(),	
		Weapon->Ammo, Weapon->MagCapacity);
}

void UOperatorReticle::OnReticleChanged(UMaterialInstanceDynamic* ReticleDynMatInst, const FReticleParams& ReticleParams, bool bCurrentlyTargetingPlayer)
{
	// Set the Material on the actual reticle widget to the dyn mat inst
	CurrentReticleParams = ReticleParams;
	CurrentReticle_DynMatInst = ReticleDynMatInst;
	FSlateBrush Brush;
	Brush.SetResourceObject(ReticleDynMatInst);
	if (IsValid(Image_Reticle))
	{
		 Image_Reticle->SetBrush(Brush);
	}

	OnTargetingPlayerStatusChanged(bCurrentlyTargetingPlayer);
}

void UOperatorReticle::OnAmmoCounterChanged(UMaterialInstanceDynamic* AmmoCounterDynMatInst, int32 RoundsCurrent,
	int32 RoundsMax)
{
	// Set the Material on the actual ammo counter widget to the dyn mat inst
	CurrentAmmoCounter_DynMatInst = AmmoCounterDynMatInst;
	CurrentAmmoCounter_DynMatInst->SetScalarParameterValue(Ammo::Rounds_Current, RoundsCurrent);
	CurrentAmmoCounter_DynMatInst->SetScalarParameterValue(Ammo::Rounds_Max, RoundsMax);
	
	FSlateBrush Brush;
	Brush.SetResourceObject(AmmoCounterDynMatInst);
	if (IsValid(Image_AmmoCounter))
	{
		Image_AmmoCounter->SetBrush(Brush);
	}
}

void UOperatorReticle::OnRoundFired(int32 RoundsCurrent, int32 RoundsMax, int32 RoundsInReserve)
{
	_BaseCornerScaleFactor_RoundFired += CurrentReticleParams.ScaleFactor_RoundFired;
	_BaseShapeCutFactor_RoundFired += CurrentReticleParams.ShapeCutFactor_RoundFired;
	if (CurrentAmmoCounter_DynMatInst.IsValid())
	{
		CurrentAmmoCounter_DynMatInst->SetScalarParameterValue(Ammo::Rounds_Current, RoundsCurrent);
		CurrentAmmoCounter_DynMatInst->SetScalarParameterValue(Ammo::Rounds_Max, RoundsMax);
	}
}

void UOperatorReticle::OnAimingStatusChanged(bool IsAiming)
{
	bAiming = IsAiming;
}

void UOperatorReticle::OnTargetingPlayerStatusChanged(bool IsTargetingPlayer)
{
	bTargetingPlayer = IsTargetingPlayer;
	if (CurrentReticle_DynMatInst.IsValid())
	{
		// TODO: Unhardcode this and add to theme
		FLinearColor ReticleColor = bTargetingPlayer ? FLinearColor::Red : FLinearColor::White;
		CurrentReticle_DynMatInst->SetVectorParameterValue(Reticle::Inner_RGBA, ReticleColor);
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/

