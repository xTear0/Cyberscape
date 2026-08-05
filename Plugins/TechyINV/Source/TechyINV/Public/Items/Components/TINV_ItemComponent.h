// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TINV_ItemComponent.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_ItemComponent.h_Class
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class TECHYINV_API UTINV_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UTINV_ItemComponent();
	FString GetPickupMessageData() const { return PickupMessage; }

protected:


private:

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	FString PickupMessage;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
