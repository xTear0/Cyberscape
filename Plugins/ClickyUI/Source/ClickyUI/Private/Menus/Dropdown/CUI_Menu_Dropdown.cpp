// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Menus/Dropdown/CUI_Menu_Dropdown.h"

#include "Buttons/CUI_Button_Wide.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Menus/Dropdown/CUI_Menu_Dropdown_Expanded.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Menu_Dropdown.cpp_Functions
void UCUI_Menu_Dropdown::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (WidgetSwitcher && Menu_Collapsed)
	{
		WidgetSwitcher->SetActiveWidget(Menu_Collapsed);
	}

	if (IsValid(Image_Arrow))
	{
		Image_Arrow->SetBrush(Arrow_Down);
	}

	if (IsValid(Button_ToggleDropdown) && !DropdownLabel.IsEmpty())
	{
		Button_ToggleDropdown->SetText(DropdownLabel);
	}

	if (IsValid(Menu_Expanded) && !ExpandedTitle.IsEmpty())
	{
		Menu_Expanded->OptionsTitle = ExpandedTitle;
		if (IsValid(Menu_Expanded->TextBlock_OptionsTitle))
		{
			Menu_Expanded->TextBlock_OptionsTitle->SetText(ExpandedTitle);
			Menu_Expanded->TextBlock_OptionsTitle->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}

void UCUI_Menu_Dropdown::NativeConstruct()
{
	Super::NativeConstruct();

	Button_ToggleDropdown->OnClicked.AddDynamic(this, &UCUI_Menu_Dropdown::ToggleDropdown);
	Menu_Expanded->FocusLostDelegate.AddDynamic(this, &UCUI_Menu_Dropdown::Collapse);

	BindOptions();
	InitializeOptions();

	if (!DropdownLabel.IsEmpty())
	{
		Button_ToggleDropdown->SetText(DropdownLabel);
	}

	if (!ExpandedTitle.IsEmpty())
	{
		Menu_Expanded->OptionsTitle = ExpandedTitle;
		if (IsValid(Menu_Expanded->TextBlock_OptionsTitle))
		{
			Menu_Expanded->TextBlock_OptionsTitle->SetText(ExpandedTitle);
			Menu_Expanded->TextBlock_OptionsTitle->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}

void UCUI_Menu_Dropdown::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
	Collapse();
}

void UCUI_Menu_Dropdown::BindOptions()
{
	if (!Menu_Expanded) return;

	const int32 NumButtons = Menu_Expanded->OptionButtons.Num();

	if (NumButtons >= 1 && IsValid(Menu_Expanded->Button_Option1))
		Menu_Expanded->Button_Option1->OnClicked.AddDynamic(this, &UCUI_Menu_Dropdown::OnOpt1Clicked);

	if (NumButtons >= 2 && IsValid(Menu_Expanded->Button_Option2))
		Menu_Expanded->Button_Option2->OnClicked.AddDynamic(this, &UCUI_Menu_Dropdown::OnOpt2Clicked);

	if (NumButtons >= 3 && IsValid(Menu_Expanded->Button_Option3))
		Menu_Expanded->Button_Option3->OnClicked.AddDynamic(this, &UCUI_Menu_Dropdown::OnOpt3Clicked);

	if (NumButtons >= 4 && IsValid(Menu_Expanded->Button_Option4))
		Menu_Expanded->Button_Option4->OnClicked.AddDynamic(this, &UCUI_Menu_Dropdown::OnOpt4Clicked);

	if (NumButtons >= 5 && IsValid(Menu_Expanded->Button_Option5))
		Menu_Expanded->Button_Option5->OnClicked.AddDynamic(this, &UCUI_Menu_Dropdown::OnOpt5Clicked);
}

void UCUI_Menu_Dropdown::InitializeOptions()
{
	for (int32 i = 0; i < Menu_Expanded->OptionButtons.Num(); i++)
	{
		UCUI_Button_Wide* Button = Menu_Expanded->OptionButtons[i];
		if (IsValid(Button) && DropdownOptions.IsValidIndex(i))
		{
			Button->SetText(DropdownOptions[i]);
		}
	}
}

void UCUI_Menu_Dropdown::ToggleDropdown()
{
	bIsExpanded ? Collapse() : Expand();
}

void UCUI_Menu_Dropdown::Expand()
{
	if (bIsExpanded) return;

	WidgetSwitcher->SetActiveWidget(Menu_Expanded);
	bIsExpanded = true;

	if (IsValid(Image_Arrow)) Image_Arrow->SetBrush(Arrow_Up);
}

void UCUI_Menu_Dropdown::Collapse()
{
	if (!bIsExpanded) return;

	WidgetSwitcher->SetActiveWidget(Menu_Collapsed);
	bIsExpanded = false;

	if (IsValid(Image_Arrow)) Image_Arrow->SetBrush(Arrow_Down);
}

void UCUI_Menu_Dropdown::HandleOptionSelected(int32 Index)
{
	if (!DropdownOptions.IsValidIndex(Index)) return;

	ActiveIndex = Index;
	Collapse();
	OnSelectionChanged.Broadcast(Index, DropdownOptions[Index]);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
