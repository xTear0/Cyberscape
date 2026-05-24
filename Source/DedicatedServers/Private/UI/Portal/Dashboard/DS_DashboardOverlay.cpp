// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/Dashboard/DS_DashboardOverlay.h"
#include "Buttons/CUI_Button_Wide.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "UI/Portal/Dashboard/DS_CareerPage.h"
#include "UI/Portal/Dashboard/DS_GamePage.h"
#include "UI/Portal/Dashboard/DS_LoadoutSwitcherPage.h"
#include "UI/Portal/Dashboard/Career/DS_CareerInfoButton.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_DashboardOverlay.cpp_Functions
void UDS_DashboardOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	// The Button is a component of the CareerWidget class.
	Button_CareerWidget->Button_Career->OnClicked.AddDynamic(this, &UDS_DashboardOverlay::ShowCareerPage);
	Button_Play->OnClicked.AddDynamic(this, &UDS_DashboardOverlay::ShowGamePage);
	Button_Home->OnClicked.AddDynamic(this, &UDS_DashboardOverlay::ShowGamePage);
	
	ShowGamePage();
}

void UDS_DashboardOverlay::ShowGamePage()
{
	DashboardSwitcher->SetActiveWidget(Page_Game);
}

void UDS_DashboardOverlay::ShowCareerPage()
{
	DashboardSwitcher->SetActiveWidget(Page_Career);
}

void UDS_DashboardOverlay::ShowLoadoutSwitcherPage()
{
	DashboardSwitcher->SetActiveWidget(Page_LoadoutSwitcher);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
