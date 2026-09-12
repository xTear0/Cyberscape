// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Notifications/CUI_Notification.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Notifications/CUI_NotificationCounter.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region CUI_Notification.cpp_Functions
void UCUI_Notification::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Text_Message->SetText(FText::GetEmpty());
}

void UCUI_Notification::SetNotification(const FCUIActiveNotification& Entry)
{
	const bool bIsRefresh = CurrentEntry.Id == Entry.Id;
	CurrentEntry = Entry;

	Text_Message->SetText(Entry.Payload.Message);

	// Icon override / per-type styling / counter handled Blueprint-side.
	OnNotificationSet(Entry);

	Counter->SetCount(CurrentEntry.Count);
	
	if (!bIsRefresh)
	{
		NotificationShow();
	}
}

void UCUI_Notification::NotifyHideFinished()
{
	OnHideFinished.ExecuteIfBound(this);
}
#pragma endregion
/*-------------------------------------------------------------------------*/