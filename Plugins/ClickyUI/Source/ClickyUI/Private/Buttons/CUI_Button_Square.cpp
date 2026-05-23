// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Buttons/CUI_Button_Square.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "Components/Image.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Button_Square.cpp_Functions
void UCUI_Button_Square::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensure(UE_Button))
	{
		UE_Button->OnClicked.AddDynamic(this,   &UCUI_Button_Square::HandleClicked);
		UE_Button->OnPressed.AddDynamic(this,   &UCUI_Button_Square::HandlePressed);
		UE_Button->OnReleased.AddDynamic(this,  &UCUI_Button_Square::HandleReleased);
		UE_Button->OnHovered.AddDynamic(this,   &UCUI_Button_Square::HandleHovered);
		UE_Button->OnUnhovered.AddDynamic(this, &UCUI_Button_Square::HandleUnhovered);

		// Animation Triggers
		UE_Button->OnClicked.AddDynamic(this,   &UCUI_Button_Square::OnClickedEvent);
		UE_Button->OnHovered.AddDynamic(this,   &UCUI_Button_Square::OnHoveredEvent);
		UE_Button->OnUnhovered.AddDynamic(this, &UCUI_Button_Square::OnUnhoveredEvent);
	}
}

void UCUI_Button_Square::NativeDestruct()
{
	if (IsValid(UE_Button))
	{
		UE_Button->OnClicked.RemoveAll(this);
		UE_Button->OnPressed.RemoveAll(this);
		UE_Button->OnReleased.RemoveAll(this);
		UE_Button->OnHovered.RemoveAll(this);
		UE_Button->OnUnhovered.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void UCUI_Button_Square::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(UE_Image))
	{
		UE_Image->SetBrushFromTexture(Image_Icon);
	}
}

void UCUI_Button_Square::OnHoveredEvent()
{
	if (IsValid(Anim_Hovered))
	{
		PlayAnimation(Anim_Hovered);
		GetWorld()->GetTimerManager().SetTimer(
			HoverPulseTimer,
			this,
			&ThisClass::PlayHoverAnimation,
			Anim_Hovered->GetEndTime(),
			true
		);
	}
}

void UCUI_Button_Square::OnUnhoveredEvent()
{
	GetWorld()->GetTimerManager().ClearTimer(HoverPulseTimer);
}

void UCUI_Button_Square::OnClickedEvent()
{
	if (IsValid(Anim_Clicked))
	{
		PlayAnimation(Anim_Clicked);
		GetWorld()->GetTimerManager().SetTimer(
			ClickPulseTimer,
			this,
			&ThisClass::PostAnimation,
			Anim_Clicked->GetEndTime(),
			false
		);
	}
}

void UCUI_Button_Square::OnIsEnabledEvent()
{

}

void UCUI_Button_Square::PlayHoverAnimation()
{
	if (IsValid(Anim_Hovered))
	{
		PlayAnimation(Anim_Hovered);
	}
}

void UCUI_Button_Square::PostAnimation()
{
	OnClickedPostAnim.Broadcast();
}

void UCUI_Button_Square::SetIsButtonEnabled(bool bInIsEnabled)
{

}

bool UCUI_Button_Square::GetIsButtonEnabled() const
{
	return UE_Button ? UE_Button->GetIsEnabled() : false;
}

void UCUI_Button_Square::ShowButtonAsSelected()
{
	if (IsValid(Anim_Selected))
	{
		PlayAnimation(Anim_Selected);
	}
}

void UCUI_Button_Square::ShowButtonAsDeselected()
{
	if (IsValid(Anim_Selected))
	{
		PlayAnimationReverse(Anim_Selected);
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
