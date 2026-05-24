// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Menus/Dropdown/CUI_Menu_Dropdown_Expanded.h"
#include "Buttons/CUI_Button_Wide.h"
#include "Components/TextBlock.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Menu_Dropdown_Expanded.cpp_Functions
void UCUI_Menu_Dropdown_Expanded::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(TextBlock_OptionsTitle))
	{
		TextBlock_OptionsTitle->SetText(OptionsTitle);
		TextBlock_OptionsTitle->SetVisibility(OptionsTitle.IsEmpty() ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);
	}
}

void UCUI_Menu_Dropdown_Expanded::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);

	OptionButtons = { Button_Option1 };

	if (IsValid(Button_Option2)) OptionButtons.Add(Button_Option2);
	if (IsValid(Button_Option3)) OptionButtons.Add(Button_Option3);
	if (IsValid(Button_Option4)) OptionButtons.Add(Button_Option4);
	if (IsValid(Button_Option5)) OptionButtons.Add(Button_Option5);
}

void UCUI_Menu_Dropdown_Expanded::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	FocusLostDelegate.Broadcast();
}
#pragma endregion
/*-------------------------------------------------------------------------*/
