// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/Dashboard/DS_CareerPage.h"
#include "Components/WidgetSwitcher.h"
#include "UI/Portal/Dashboard/Career/Pages/Achievements/DS_CareerPage_Achievements.h"
#include "UI/Portal/Dashboard/Career/Pages/Leaderboards/DS_CareerPage_Leaderboards.h"
#include "UI/Portal/Dashboard/Career/Pages/Statistics/DS_CareerPage_Statistics.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_CareerPage.cpp_Functions
void UDS_CareerPage::NativeConstruct()
{
	Super::NativeConstruct();

	KebabMenu->OnSelectionChanged.AddDynamic(this, &UDS_CareerPage::SwitchToPage);
}

void UDS_CareerPage::SwitchToPage(ESYS7_Menu_Kebab_Selection PageSelection)
{
	if (PageSelection == ESYS7_Menu_Kebab_Selection::Selection1)
	{
		PageSwitcher->SetActiveWidget(Page_Statistics);
	}
	else if (PageSelection == ESYS7_Menu_Kebab_Selection::Selection2)
	{
		PageSwitcher->SetActiveWidget(Page_Leaderboards);	
	}
	else
	{
		PageSwitcher->SetActiveWidget(Page_Achievements);
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
