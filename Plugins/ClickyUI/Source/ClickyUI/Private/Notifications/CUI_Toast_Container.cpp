// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Notifications/CUI_Toast_Container.h"
#include "Components/VerticalBox.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Toast_Container.cpp_Functions
void UCUI_Toast_Container::ShowToast(const FText& Message, ECUI_ToastType Type, float Duration)
{
	if (!ToastClass || !IsValid(VerticalBox_Toasts)) return;

	// Evict the oldest toast if at capacity
	if (ActiveToasts.Num() >= MaxToasts && ActiveToasts.Num() > 0)
	{
		UCUI_Toast* Oldest = ActiveToasts[0];
		if (IsValid(Oldest))
		{
			Oldest->Dismiss();
		}
	}

	UCUI_Toast* NewToast = CreateWidget<UCUI_Toast>(GetOwningPlayer(), ToastClass);
	if (!IsValid(NewToast)) return;

	NewToast->Initialize(Message, Type, Duration);

	NewToast->OnDismissed.AddDynamic(this, &UCUI_Toast_Container::HandleToastDismissed);

	VerticalBox_Toasts->AddChildToVerticalBox(NewToast);
	ActiveToasts.Add(NewToast);
}

void UCUI_Toast_Container::HandleToastDismissed()
{
	// After RemoveFromParent(), a toast's GetParent() returns nullptr — use that to identify which one finished.
	ActiveToasts.RemoveAll([](const TObjectPtr<UCUI_Toast>& T)
	{
		return !IsValid(T) || !IsValid(T->GetParent());
	});
}
#pragma endregion
/*-------------------------------------------------------------------------*/
