// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/Dashboard/Career/Pages/Statistics/DS_CareerPage_Statistics.h"
#include "Components/WidgetSwitcher.h"
#include "DedicatedServers/Public/UI/Portal/Dashboard/Career/Pages/Statistics/InternalPages/DS_Career_Statistics_Deathmatch.h"
#include "DedicatedServers/Public/UI/Portal/Dashboard/Career/Pages/Statistics/InternalPages/DS_Career_Statistics_FFA.h"
#include "Menus/Hamburger/CUI_Menu_Hamburger.h"
#include "UI/Portal/Dashboard/Career/Pages/Statistics/InternalPages/DS_Career_Statistics_Domination.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_CareerPage_Statistics.cpp_Functions
void UDS_CareerPage_Statistics::NativeConstruct()
{
	Super::NativeConstruct();
	
	Menu_Hamburger->OnSelectionChanged.AddDynamic(this, &UDS_CareerPage_Statistics::SwitchToPage);
}

void UDS_CareerPage_Statistics::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UDS_CareerPage_Statistics::SwitchToPage(ECUI_Menu_Hamburger_Selection PageSelection)
{
	if (PageSelection == ECUI_Menu_Hamburger_Selection::Selection1)
	{
		StatsPageSwitcher->SetActiveWidget(Page_Domination);
	} else if (PageSelection == ECUI_Menu_Hamburger_Selection::Selection2)
	{
		StatsPageSwitcher->SetActiveWidget(Page_FFA);
	} else if (PageSelection == ECUI_Menu_Hamburger_Selection::Selection3)
	{
		StatsPageSwitcher->SetActiveWidget(Page_Deathmatch);
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/