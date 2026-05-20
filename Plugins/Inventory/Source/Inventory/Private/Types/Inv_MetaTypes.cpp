// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Types/Inv_MetaTypes.h"
#include "Items/Manifest/Utils/Inv_MetaUtils.h"
/*-------------------------------------------------------------------------*/


void FInv_ItemMetaData::GenerateItemData()
{
	GenerateItemStars();
	GenerateItemSpecial();
	GenerateItemEnhancement();
	
	GenerateSecondaryAttributes();
}

void FInv_ItemMetaData::GenerateItemStars()
{
}

void FInv_ItemMetaData::GenerateItemSpecial()
{
}

void FInv_ItemMetaData::GenerateItemEnhancement()
{
}

void FInv_ItemMetaData::GenerateSecondaryAttributes()
{
	// 1. Identify all valid attributes.
	//UInv_MetaUtils::GetValidAttributeList();
}
