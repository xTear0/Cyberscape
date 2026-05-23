// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Menus/Hamburger/CUI_Menu_Hamburger.h"

#include "Buttons/CUI_Button_Wide.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Core/CUI_StyleAsset.h"
#include "Menus/Hamburger/CUI_Menu_Hamburger_Expanded.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Menu_Hamburger.cpp_Functions
void UCUI_Menu_Hamburger::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (WidgetSwitcher && Menu_Collapsed)
	{
		WidgetSwitcher->SetActiveWidget(Menu_Collapsed);
	}
}

void UCUI_Menu_Hamburger::NativeConstruct()
{
	Super::NativeConstruct();

	HamburgerSelectionsAmount = Menu_Expanded->SelectionButtons.Num();

	Button_Hamburger->OnClicked.AddDynamic(this, &UCUI_Menu_Hamburger::ToggleDropdown);
	Menu_Expanded->FocusLostDelegate.AddDynamic(this, &UCUI_Menu_Hamburger::Collapse);
	Menu_Expanded->OnCollapsedAnimationFinished.AddDynamic(this, &UCUI_Menu_Hamburger::FinalizeCollapse);

	BindButtons();

	InitializeButtons();
	Button_Hamburger->SetText(Menu_Expanded->Button_Selection1->GetText());
}

void UCUI_Menu_Hamburger::FinalizeCollapse()
{
	WidgetSwitcher->SetActiveWidget(Menu_Collapsed);
}

void UCUI_Menu_Hamburger::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
	Collapse();
}

void UCUI_Menu_Hamburger::BindButtons()
{
	if (!Menu_Expanded) return;

	if (HamburgerSelectionsAmount >= 1 && IsValid(Menu_Expanded->Button_Selection1))
		Menu_Expanded->Button_Selection1->OnClicked.AddDynamic(this, &UCUI_Menu_Hamburger::OnBtn1Clicked);

	if (HamburgerSelectionsAmount >= 2 && IsValid(Menu_Expanded->Button_Selection2))
		Menu_Expanded->Button_Selection2->OnClicked.AddDynamic(this, &UCUI_Menu_Hamburger::OnBtn2Clicked);

	if (HamburgerSelectionsAmount >= 3 && IsValid(Menu_Expanded->Button_Selection3))
		Menu_Expanded->Button_Selection3->OnClicked.AddDynamic(this, &UCUI_Menu_Hamburger::OnBtn3Clicked);

	if (HamburgerSelectionsAmount >= 4 && IsValid(Menu_Expanded->Button_Selection4))
		Menu_Expanded->Button_Selection4->OnClicked.AddDynamic(this, &UCUI_Menu_Hamburger::OnBtn4Clicked);

	if (HamburgerSelectionsAmount >= 5 && IsValid(Menu_Expanded->Button_Selection5))
		Menu_Expanded->Button_Selection5->OnClicked.AddDynamic(this, &UCUI_Menu_Hamburger::OnBtn5Clicked);
}

void UCUI_Menu_Hamburger::ToggleDropdown()
{
	bIsExpanded ? Collapse() : Expand();
}

void UCUI_Menu_Hamburger::InitializeButtons()
{
	Menu_Expanded->Button_Selection1->SetText(HamburgerOptions[0]);
	if (IsValid(Menu_Expanded->Button_Selection2))
	{
		Menu_Expanded->Button_Selection2->SetText(HamburgerOptions[1]);
	}
	if (IsValid(Menu_Expanded->Button_Selection3))
	{
		Menu_Expanded->Button_Selection3->SetText(HamburgerOptions[2]);
	}
	if (IsValid(Menu_Expanded->Button_Selection4))
	{
		Menu_Expanded->Button_Selection4->SetText(HamburgerOptions[3]);
	}
	if (IsValid(Menu_Expanded->Button_Selection5))
	{
		Menu_Expanded->Button_Selection5->SetText(HamburgerOptions[4]);
	}
}

void UCUI_Menu_Hamburger::Expand()
{
	if (bIsExpanded) return;
	WidgetSwitcher->SetActiveWidget(Menu_Expanded);
	Menu_Expanded->ClearAnimations();
	Button_Hamburger->OverrideDisableAnimation = true;
	Button_Hamburger->SetIsButtonEnabled(false);
	bIsExpanded = true;
	Menu_Expanded->PlayExpandedAnimation();
}

void UCUI_Menu_Hamburger::Collapse()
{
	if (!bIsExpanded) return;

	bIsExpanded = false;
	Button_Hamburger->OverrideDisableAnimation = false;
	Button_Hamburger->SetIsButtonEnabled(true);

	Menu_Expanded->PlayCollapsedAnimation();
}

void UCUI_Menu_Hamburger::HandleSelectionButtonClicked(ECUI_Menu_Hamburger_Selection NewSelection)
{
	ActiveSelection = NewSelection;
	Collapse();
	UpdateActiveSelectionText(NewSelection);
	NativeOnSelectionChanged(NewSelection);
	OnSelectionChanged.Broadcast(NewSelection);
}

void UCUI_Menu_Hamburger::UpdateActiveSelectionText(ECUI_Menu_Hamburger_Selection NewSelection) const
{
	if (NewSelection == ECUI_Menu_Hamburger_Selection::Selection1)
	{
		const FText ActiveSelectionText = Menu_Expanded->Button_Selection1->GetText();
		Button_Hamburger->SetText(ActiveSelectionText);
	} else if (NewSelection == ECUI_Menu_Hamburger_Selection::Selection2)
	{
		const FText ActiveSelectionText = Menu_Expanded->Button_Selection2->GetText();
		Button_Hamburger->SetText(ActiveSelectionText);
	} else if (NewSelection == ECUI_Menu_Hamburger_Selection::Selection3)
	{
		const FText ActiveSelectionText = Menu_Expanded->Button_Selection3->GetText();
		Button_Hamburger->SetText(ActiveSelectionText);
	} else if (NewSelection == ECUI_Menu_Hamburger_Selection::Selection4)
	{
		const FText ActiveSelectionText = Menu_Expanded->Button_Selection4->GetText();
		Button_Hamburger->SetText(ActiveSelectionText);
	} else if (NewSelection == ECUI_Menu_Hamburger_Selection::Selection5)
	{
		const FText ActiveSelectionText = Menu_Expanded->Button_Selection5->GetText();
		Button_Hamburger->SetText(ActiveSelectionText);
	}
	// Add more as needed.
}
#pragma endregion
/*-------------------------------------------------------------------------*/
