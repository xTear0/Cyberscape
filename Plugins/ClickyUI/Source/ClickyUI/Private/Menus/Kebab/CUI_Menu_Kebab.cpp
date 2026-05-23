// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Menus/Kebab/CUI_Menu_Kebab.h"

#include "Buttons/CUI_Button_Square.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Menu_Kebab.cpp_Functions
void UCUI_Menu_Kebab::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCUI_Menu_Kebab::NativeConstruct()
{
	Super::NativeConstruct();

	BindButtons();

	ActiveSelection = ECUI_Menu_Kebab_Selection::Selection1; // Default to selection 1 as the default selection.
	UpdateSelection(ECUI_Menu_Kebab_Selection::None, ActiveSelection);
}

void UCUI_Menu_Kebab::BindButtons()
{
	if (IsValid(Button_Kebab1))
	{
		Button_Kebab1->OnClickedPostAnim.AddDynamic(this, &UCUI_Menu_Kebab::OnBtn1Clicked);
	}

	if (IsValid(Button_Kebab2))
	{
		Button_Kebab2->OnClickedPostAnim.AddDynamic(this, &UCUI_Menu_Kebab::OnBtn2Clicked);
	}

	if (IsValid(Button_Kebab3))
	{
		Button_Kebab3->OnClickedPostAnim.AddDynamic(this, &UCUI_Menu_Kebab::OnBtn3Clicked);
	}
}

void UCUI_Menu_Kebab::UpdateSelection(ECUI_Menu_Kebab_Selection OldSelection, ECUI_Menu_Kebab_Selection NewSelection)
{
	// Hide old selection border highlight.
	if (OldSelection == ECUI_Menu_Kebab_Selection::Selection1)
	{
		Button_Kebab1->ShowButtonAsDeselected();
	}
	if (OldSelection == ECUI_Menu_Kebab_Selection::Selection2)
	{
		Button_Kebab2->ShowButtonAsDeselected();
	}
	if (OldSelection == ECUI_Menu_Kebab_Selection::Selection3)
	{
		Button_Kebab3->ShowButtonAsDeselected();
	}

	// Show new selection border highlight.
	if (NewSelection == ECUI_Menu_Kebab_Selection::Selection1)
	{
		Button_Kebab1->ShowButtonAsSelected();
	}
	if (NewSelection == ECUI_Menu_Kebab_Selection::Selection2)
	{
		Button_Kebab2->ShowButtonAsSelected();
	}
	if (NewSelection == ECUI_Menu_Kebab_Selection::Selection3)
	{
		Button_Kebab3->ShowButtonAsSelected();
	}
	ActiveSelection = NewSelection;
}

void UCUI_Menu_Kebab::HandleSelectionButtonClicked(ECUI_Menu_Kebab_Selection NewSelection)
{
	UpdateSelection(ActiveSelection, NewSelection);
	NativeOnSelectionChanged(NewSelection);
	OnSelectionChanged.Broadcast(NewSelection);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
