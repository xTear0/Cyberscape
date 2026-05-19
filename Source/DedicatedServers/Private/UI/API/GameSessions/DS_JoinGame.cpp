// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/API/GameSessions/DS_JoinGame.h"

#include "Buttons/SYS7_Button_Wide.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Data/Themes/DS_UITheme.h"
#include "Kismet/GameplayStatics.h"
#include "Types/DS_EnumTypes.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_JoinGame.cpp_Functions
void UDS_JoinGame::SetStatusMessage(const FString& StatusMessage, bool bShouldResetWidgets,
	EDS_DelegateResponse DelegateResponse)
{
	TextBlock_StatusMessage->SetText(FText::FromString(StatusMessage));

	if (bShouldResetWidgets)
	{
		Button_JoinGame->SetIsEnabled(true);
	}

	if (DelegateResponse == EDS_DelegateResponse::ResponseError)
	{
		if (Theme_Asset->SFX_Error)
		{
			UGameplayStatics::PlaySound2D(this, Theme_Asset->SFX_Error);
		}
	}
	
	if (DelegateResponse == EDS_DelegateResponse::ResponseSuccess)
	{
		if (Theme_Asset->SFX_Success)
		{
			UGameplayStatics::PlaySound2D(this, Theme_Asset->SFX_Success);
		}
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/

