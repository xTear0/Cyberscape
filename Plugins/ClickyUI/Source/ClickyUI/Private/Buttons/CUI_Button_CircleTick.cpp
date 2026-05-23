// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Buttons/CUI_Button_CircleTick.h"
#include "Components/CheckBox.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Button_CircleTick.cpp_Functions
void UCUI_Button_CircleTick::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(UE_CheckBox))
	{
		UE_CheckBox->SetIsChecked(bDefaultChecked);
	}
}

void UCUI_Button_CircleTick::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensure(UE_CheckBox))
	{
		UE_CheckBox->SetIsChecked(bDefaultChecked);
		UE_CheckBox->OnCheckStateChanged.AddDynamic(this, &UCUI_Button_CircleTick::HandleCheckStateChanged);
	}
}

void UCUI_Button_CircleTick::NativeDestruct()
{
	if (IsValid(UE_CheckBox))
	{
		UE_CheckBox->OnCheckStateChanged.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void UCUI_Button_CircleTick::SetChecked(bool bInChecked)
{
	if (IsValid(UE_CheckBox))
	{
		UE_CheckBox->SetIsChecked(bInChecked);
		OnCheckStateChanged.Broadcast(bInChecked);
	}
}

bool UCUI_Button_CircleTick::IsChecked() const
{
	return UE_CheckBox ? UE_CheckBox->IsChecked() : false;
}

void UCUI_Button_CircleTick::HandleCheckStateChanged(bool bIsCheckedNew)
{
	OnCheckStateChanged.Broadcast(bIsCheckedNew);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
