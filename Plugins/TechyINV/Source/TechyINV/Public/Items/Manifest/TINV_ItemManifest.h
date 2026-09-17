// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"
#include "TINV_ItemManifest.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTINV_InventoryItem;

USTRUCT()
struct TECHYINV_API FTINV_ItemManifest
{
    GENERATED_BODY()
    
public:    
    UTINV_InventoryItem* Manifest(UObject* NewOuter);
    FGameplayTag GetItemID() const { return ItemID; }
     
    
private:
    UPROPERTY(EditAnywhere, Category = "TECHY|Inventory", meta = (Categories="CyberscapeItems"))
    FGameplayTag ItemID;
    
};
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_ItemManifest.h_Class

#pragma endregion
/*-------------------------------------------------------------------------*/