// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Items/Manifest/TINV_ItemManifest.h"
#include "TINV_InventoryItem.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_InventoryItem.h_Class
UCLASS

()
class TECHYINV_API UTINV_InventoryItem : public UObject
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override;
	
	void SetItemManifest(const FTINV_ItemManifest& Manifest);
	const FTINV_ItemManifest& GetItemManifest() const { return ItemManifest.Get<FTINV_ItemManifest>(); }
	FTINV_ItemManifest& GetItemManifestMutable() { return ItemManifest.GetMutable<FTINV_ItemManifest>(); }
	
private:

	UPROPERTY(VisibleAnywhere, meta = (BaseStruct = "/Script/TechyINV.TINV_ItemManifest"), Replicated)
	FInstancedStruct ItemManifest;
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/
