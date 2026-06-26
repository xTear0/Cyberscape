// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OperatorCombatComponent.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region OperatorCombatComponent.h_Class
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CYBERSCAPE_API UOperatorCombatComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UOperatorCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Cycle to next weapon in inventory
	void Initiate_CycleWeapon();
	
	void Initiate_FireWeapon_Pressed();
	void Initiate_FireWeapon_Released();
	void Initiate_ReloadWeapon();
	void Initiate_Aim_Pressed();
	void Initiate_Aim_Released();
	
protected:
	
private:

};
#pragma endregion
/*-------------------------------------------------------------------------*/