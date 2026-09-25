// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Manifest/TINV_ItemManifest.h"
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
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	FTINV_ItemManifest GetItemManifest() const { return ItemManifest; }

protected:


private:

	UPROPERTY(Replicated, EditAnywhere, Category = "TECHY|Inventory")
	FTINV_ItemManifest ItemManifest;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
