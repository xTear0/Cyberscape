// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TINV_InventoryStatics.generated.h"
/*-------------------------------------------------------------------------*/


class UTINV_ItemComponent;
/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTINV_InventoryComponent;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryStatics.h_Class
UCLASS()
class TECHYINV_API UTINV_InventoryStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "TECHY|Inventory")
	static UTINV_InventoryComponent* GetInventoryComponent(const APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category = "TECHY|Inventory")
	static FGameplayTag GetItemIDFromItemComp(UTINV_ItemComponent* ItemComp);

protected:

private:
};
#pragma endregion
/*-------------------------------------------------------------------------*/
