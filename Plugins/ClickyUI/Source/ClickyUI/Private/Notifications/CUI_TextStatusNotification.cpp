// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Notifications/CUI_TextStatusNotification.h"
#include "Components/TextBlock.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region CUI_TextStatusNotification.cpp_Functions
void UCUI_TextStatusNotification::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	Text_Message->SetText(FText::GetEmpty());
	MessageHide();
}

void UCUI_TextStatusNotification::SetMessage(const FText& Message)
{
	Text_Message->SetText(Message);

	if (!bIsMessageActive)
	{
		MessageShow();	
	}
	bIsMessageActive = true;

	GetWorld()->GetTimerManager().SetTimer(MessageTimerHandle, [this]()
	{
		MessageHide();
		bIsMessageActive = false;
	}, MessageLifetime, false);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
