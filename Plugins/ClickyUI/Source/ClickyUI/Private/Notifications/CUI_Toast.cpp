// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Notifications/CUI_Toast.h"
#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Toast.cpp_Functions
void UCUI_Toast::Initialize(const FText& Message, ECUI_ToastType Type, float Duration)
{
	ToastType = Type;
	DisplayDuration = FMath::Max(Duration, 0.5f);

	if (IsValid(TextBlock_Message))
	{
		TextBlock_Message->SetText(Message);
	}
}

void UCUI_Toast::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(Anim_Show))
	{
		PlayAnimation(Anim_Show);
	}

	GetWorld()->GetTimerManager().SetTimer(
		DisplayTimer,
		this,
		&UCUI_Toast::BeginDismiss,
		DisplayDuration,
		false
	);
}

void UCUI_Toast::Dismiss()
{
	GetWorld()->GetTimerManager().ClearTimer(DisplayTimer);
	BeginDismiss();
}

void UCUI_Toast::BeginDismiss()
{
	if (IsValid(Anim_Dismiss))
	{
		PlayAnimation(Anim_Dismiss);

		GetWorld()->GetTimerManager().SetTimer(
			DismissAnimTimer,
			this,
			&UCUI_Toast::FinalizeDismiss,
			Anim_Dismiss->GetEndTime(),
			false
		);
	}
	else
	{
		FinalizeDismiss();
	}
}

void UCUI_Toast::FinalizeDismiss()
{
	OnDismissed.Broadcast();
	RemoveFromParent();
}
#pragma endregion
/*-------------------------------------------------------------------------*/
