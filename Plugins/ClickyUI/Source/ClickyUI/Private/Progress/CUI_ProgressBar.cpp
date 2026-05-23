// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Progress/CUI_ProgressBar.h"

#include "Animation/WidgetAnimation.h"
#include "Components/ProgressBar.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_ProgressBar.cpp_Functions
void UCUI_ProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(UE_ProgressBar))
	{
		UE_ProgressBar->SetPercent(DefaultPercent);
	}
}

void UCUI_ProgressBar::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(UE_ProgressBar))
	{
		UE_ProgressBar->SetPercent(DefaultPercent);
	}

	ApplyMode();
}

void UCUI_ProgressBar::SetPercent(float InPercent)
{
	if (IsValid(UE_ProgressBar))
	{
		UE_ProgressBar->SetPercent(FMath::Clamp(InPercent, 0.0f, 1.0f));
	}
}

float UCUI_ProgressBar::GetPercent() const
{
	return UE_ProgressBar ? UE_ProgressBar->GetPercent() : 0.0f;
}

void UCUI_ProgressBar::SetMode(ECUI_ProgressBarMode InMode)
{
	Mode = InMode;
	ApplyMode();
}

void UCUI_ProgressBar::ApplyMode()
{
	if (Mode == ECUI_ProgressBarMode::Indeterminate)
	{
		if (IsValid(Anim_Indeterminate))
		{
			PlayAnimation(Anim_Indeterminate, 0.f, 0, EUMGSequencePlayMode::Forward, 1.f, false);
		}
	}
	else
	{
		if (IsValid(Anim_Indeterminate))
		{
			StopAnimation(Anim_Indeterminate);
		}
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
