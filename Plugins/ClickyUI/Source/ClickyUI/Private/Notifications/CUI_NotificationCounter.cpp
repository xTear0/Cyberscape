// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Notifications/CUI_NotificationCounter.h"
#include "Components/TextBlock.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region CUI_NotificationCounter.cpp_Functions
void UCUI_NotificationCounter::SetCount(const int32 StackCount)
{
	Count = StackCount;

	CurrentCount->SetText(FText::Format(
		NSLOCTEXT("ClickyUI", "NotifCounterFormat", "{0}{1}{2}"),
		Prefix, FText::AsNumber(Count), Suffix));

	OnCountUpdated();
}
#pragma endregion
/*-------------------------------------------------------------------------*/