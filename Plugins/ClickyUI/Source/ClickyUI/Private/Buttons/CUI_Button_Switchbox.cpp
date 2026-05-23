// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Buttons/CUI_Button_Switchbox.h"

#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Button_Switchbox.cpp_Functions
void UCUI_Button_Switchbox::NativePreConstruct()
{
	Super::NativePreConstruct();

	bIsOn = bDefaultOn;
}

void UCUI_Button_Switchbox::NativeConstruct()
{
	Super::NativeConstruct();

	bIsOn = bDefaultOn;

	if (ensure(UE_Button))
	{
		UE_Button->OnClicked.AddDynamic(this, &UCUI_Button_Switchbox::HandleClicked);
	}

	PlayStateAnimation();
}

void UCUI_Button_Switchbox::NativeDestruct()
{
	if (IsValid(UE_Button))
	{
		UE_Button->OnClicked.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void UCUI_Button_Switchbox::SetIsOn(bool bInIsOn)
{
	if (bIsOn == bInIsOn) return;

	bIsOn = bInIsOn;
	PlayStateAnimation();
	OnToggled.Broadcast(bIsOn);
}

void UCUI_Button_Switchbox::PlayStateAnimation()
{
	if (bIsOn)
	{
		if (IsValid(Anim_TurnOn))  PlayAnimation(Anim_TurnOn);
	}
	else
	{
		if (IsValid(Anim_TurnOff)) PlayAnimation(Anim_TurnOff);
	}
}

void UCUI_Button_Switchbox::HandleClicked()
{
	SetIsOn(!bIsOn);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
