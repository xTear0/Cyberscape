// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "ItemData/TINV_ItemDataTable.h"
#include "Notifications/CUI_NotificationManager.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_ItemDataTable.cpp_Functions
const FTINV_ItemDataDefinition* UTINV_ItemDataTable::GetDataByTag(const FGameplayTag& Tag) const
{
	static const FGameplayTag WeaponTag     = FGameplayTag::RequestGameplayTag(TEXT("CyberscapeItems.Weapon"));
	static const FGameplayTag AttachmentTag = FGameplayTag::RequestGameplayTag(TEXT("CyberscapeItems.Attachment"));
	static const FGameplayTag MaterialTag   = FGameplayTag::RequestGameplayTag(TEXT("CyberscapeItems.Material"));

	const FTINV_ItemDataDefinition* Result = nullptr;

	if (Tag.MatchesTag(WeaponTag))          { Result = ItemData_Weapons.Find(Tag); }
	else if (Tag.MatchesTag(AttachmentTag)) { Result = ItemData_Attachments.Find(Tag); }
	else if (Tag.MatchesTag(MaterialTag))   { Result = ItemData_Materials.Find(Tag); }

	if (!Result)
	{
		UCUI_NotificationManager::PostError(this, NSLOCTEXT("Cyberscape", "InventoryItem", "Failed to find Item Data."), false);
	}
	return Result;
}

#pragma endregion
/*-------------------------------------------------------------------------*/
