// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Types/TINV_EnumTypes.h"
#include "Types/TINV_StructTypes.h"
#include "TINV_ItemDataTable.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_ItemDataTable.h_Class
UCLASS()
class TECHYINV_API UTINV_ItemDataTable : public UDataAsset
{
	GENERATED_BODY()

public:
	// Shared data for any item. Returns nullptr if not found.
	const FTINV_ItemDataDefinition* GetDataByTag(const FGameplayTag& Tag) const;

	// Type-specific data, when you need the extra fields.
	const FTINV_ItemWeaponDataDefinition*     GetWeaponData(const FGameplayTag& Tag) const     { return ItemData_Weapons.Find(Tag); }
	const FTINV_ItemAttachmentDataDefinition* GetAttachmentData(const FGameplayTag& Tag) const { return ItemData_Attachments.Find(Tag); }
	const FTINV_ItemMaterialDataDefinition*   GetMaterialData(const FGameplayTag& Tag) const   { return ItemData_Materials.Find(Tag); }

private:
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory", meta=(Categories="CyberscapeItems.Weapon"))
	TMap<FGameplayTag, FTINV_ItemWeaponDataDefinition> ItemData_Weapons;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory", meta=(Categories="CyberscapeItems.Attachment"))
	TMap<FGameplayTag, FTINV_ItemAttachmentDataDefinition> ItemData_Attachments;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory", meta=(Categories="CyberscapeItems.Material"))
	TMap<FGameplayTag, FTINV_ItemMaterialDataDefinition> ItemData_Materials;

};
#pragma endregion
/*-------------------------------------------------------------------------*/
