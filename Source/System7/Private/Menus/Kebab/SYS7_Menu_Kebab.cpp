// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/Kebab/SYS7_Menu_Kebab.h"

#include "Buttons/SYS7_Button_Square.h"

void USYS7_Menu_Kebab::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USYS7_Menu_Kebab::NativeConstruct()
{
	Super::NativeConstruct();
	
	BindButtons();

	ActiveSelection = ESYS7_Menu_Kebab_Selection::Selection1; // Default to selection 1 as the default selection.
	UpdateSelection(ESYS7_Menu_Kebab_Selection::None, ActiveSelection);
}

void USYS7_Menu_Kebab::BindButtons()
{
	if (IsValid(Button_Kebab1))
	{
		Button_Kebab1->OnClickedPostAnim.AddDynamic(this, &USYS7_Menu_Kebab::OnBtn1Clicked);
	}

	if (IsValid(Button_Kebab2))
	{
		Button_Kebab2->OnClickedPostAnim.AddDynamic(this, &USYS7_Menu_Kebab::OnBtn2Clicked);
	}
	
	if (IsValid(Button_Kebab3))
	{
		Button_Kebab3->OnClickedPostAnim.AddDynamic(this, &USYS7_Menu_Kebab::OnBtn3Clicked);
	}
}

void USYS7_Menu_Kebab::UpdateSelection(ESYS7_Menu_Kebab_Selection OldSelection, ESYS7_Menu_Kebab_Selection NewSelection)
{
	// Hide old selection border highlight.
	if (OldSelection == ESYS7_Menu_Kebab_Selection::Selection1)
	{
		Button_Kebab1->ShowButtonAsDeselected();
	}
	if (OldSelection == ESYS7_Menu_Kebab_Selection::Selection2)
	{
		Button_Kebab2->ShowButtonAsDeselected();
	}
	if (OldSelection == ESYS7_Menu_Kebab_Selection::Selection3)
	{
		Button_Kebab3->ShowButtonAsDeselected();
	}

	// Show new selection border highlight.
	if (NewSelection == ESYS7_Menu_Kebab_Selection::Selection1)
	{
		Button_Kebab1->ShowButtonAsSelected();
	}
	if (NewSelection == ESYS7_Menu_Kebab_Selection::Selection2)
	{
		Button_Kebab2->ShowButtonAsSelected();
	}
	if (NewSelection == ESYS7_Menu_Kebab_Selection::Selection3)
	{
		Button_Kebab3->ShowButtonAsSelected();
	}
	ActiveSelection = NewSelection;
}

void USYS7_Menu_Kebab::HandleSelectionButtonClicked(ESYS7_Menu_Kebab_Selection NewSelection)
{
	UpdateSelection(ActiveSelection, NewSelection);
	NativeOnSelectionChanged(NewSelection);
	OnSelectionChanged.Broadcast(NewSelection);
}
