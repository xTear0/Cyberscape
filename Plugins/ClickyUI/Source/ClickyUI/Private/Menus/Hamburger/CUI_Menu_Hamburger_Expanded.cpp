// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Menus/Hamburger/CUI_Menu_Hamburger_Expanded.h"
#include "Buttons/CUI_Button_Wide.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Menu_Hamburger_Expanded.cpp_Functions
void UCUI_Menu_Hamburger_Expanded::PlayExpandedAnimation()
{
	if (DelayTime <= 0) return;

	for (int32 i = 0; i < SelectionButtons.Num(); i++)
	{
		UCUI_Button_Wide* Button = SelectionButtons[i];

		if (!IsValid(Button))
		{
			continue;
		}

		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;

		TimerDelegate.BindLambda([Button]()
		{
			if (IsValid(Button))
			{
				Button->PlayTransitionAnimation(false);
			}
		});

		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			TimerDelegate,
			DelayTime * (i + 1),
			false
		);
	}
}

void UCUI_Menu_Hamburger_Expanded::PlayCollapsedAnimation()
{
	if (DelayTime <= 0) return;

	const int32 ButtonCount = SelectionButtons.Num();

	for (int32 i = ButtonCount - 1; i >= 0; i--)
	{
		UCUI_Button_Wide* Button = SelectionButtons[i];

		if (!IsValid(Button)) continue;

		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;

		const int32 ReverseIndex = (ButtonCount - 1) - i;
		const bool bIsLastButton = (ReverseIndex == ButtonCount - 1);

		TimerDelegate.BindLambda([Button, bIsLastButton, this]()
		{
			if (IsValid(Button))
			{
				Button->PlayTransitionAnimation(true);
			}

			if (bIsLastButton)
			{
				OnCollapsedAnimationFinished.Broadcast();
			}
		});

		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			TimerDelegate,
			DelayTime * (ReverseIndex + 1),
			false
		);
	}
}

void UCUI_Menu_Hamburger_Expanded::ClearAnimations()
{
	for (int32 i = 0; i < SelectionButtons.Num(); i++)
	{
		UCUI_Button_Wide* Button = SelectionButtons[i];

		if (!IsValid(Button))
		{
			continue;
		}
		Button->ClearAnimations();
	}
}

void UCUI_Menu_Hamburger_Expanded::ClearWidgetOpacity()
{
	for (int32 i = 0; i < SelectionButtons.Num(); i++)
	{
		UCUI_Button_Wide* Button = SelectionButtons[i];

		if (!IsValid(Button))
		{
			continue;
		}
		Button->SetRenderOpacity(0.f);
	}
}

void UCUI_Menu_Hamburger_Expanded::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);

	SelectionButtons = { Button_Selection1 };

	if (IsValid(Button_Selection2))
	{
		SelectionButtons.Add(Button_Selection2);
	}
	if (IsValid(Button_Selection3))
	{
		SelectionButtons.Add(Button_Selection3);
	}
	if (IsValid(Button_Selection4))
	{
		SelectionButtons.Add(Button_Selection4);
	}
	if (IsValid(Button_Selection5))
	{
		SelectionButtons.Add(Button_Selection5);
	}
}

void UCUI_Menu_Hamburger_Expanded::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	FocusLostDelegate.Broadcast();
}
#pragma endregion
/*-------------------------------------------------------------------------*/
