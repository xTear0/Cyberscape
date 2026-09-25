// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Utils/TINV_WidgetUtils.h"

#include "Notifications/CUI_NotificationTypes.h"
#include "Types/TINV_StructTypes.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_WidgetUtils.cpp_Functions
int32 UTINV_WidgetUtils::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{	  
	return Position.X + Position.Y * Columns;
}

FIntPoint UTINV_WidgetUtils::GetPositionFromIndex(const int32 Index, const int32 Columns)
{
	return FIntPoint(Index % Columns, Index / Columns);
}

ECUI_ItemTier UTINV_WidgetUtils::GetCUIItemTier(const ETINV_ItemTier Tier)
{
	if (Tier == ETINV_ItemTier::Tier1)
	{
		return ECUI_ItemTier::Tier1;
	}
	else if (Tier == ETINV_ItemTier::Tier2)
	{
		return ECUI_ItemTier::Tier2;
	}
	else if (Tier == ETINV_ItemTier::Tier3)
	{
		return ECUI_ItemTier::Tier3;
	}
	else if (Tier == ETINV_ItemTier::Tier4)
	{
		return ECUI_ItemTier::Tier4;
	}
	else if (Tier == ETINV_ItemTier::Tier5)
	{
		return ECUI_ItemTier::Tier5;
	}
	else if (Tier == ETINV_ItemTier::Prem)
	{
		return ECUI_ItemTier::Prem;
	}
	return ECUI_ItemTier::None;
}

const TCHAR* UTINV_WidgetUtils::GetTierColorToken(const ETINV_ItemTier Tier)
{
	switch (Tier)
	{
	case ETINV_ItemTier::Tier1: return TEXT("Common_Accent");
	case ETINV_ItemTier::Tier2: return TEXT("Uncommon_Accent");
	case ETINV_ItemTier::Tier3: return TEXT("Rare_Accent");
	case ETINV_ItemTier::Tier4: return TEXT("Legendary_Accent");
	case ETINV_ItemTier::Tier5: return TEXT("Omega_Accent");
	case ETINV_ItemTier::Prem:  return TEXT("Premium_Accent");
	case ETINV_ItemTier::Scrap:
	default:                    return nullptr;
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
