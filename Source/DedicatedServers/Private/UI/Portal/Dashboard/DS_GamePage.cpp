// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/Dashboard/DS_GamePage.h"

#include "Buttons/SYS7_Button_Wide.h"
#include "UI/GameSessions/DS_GameSessionsManager.h"
#include "Components/Button.h"
#include "UI/API/GameSessions/DS_JoinGame.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_GamePage.cpp_Functions
void UDS_GamePage::NativeConstruct()
{
	Super::NativeConstruct();

	GameSessionsManager = NewObject<UDS_GameSessionsManager>(this, GameSessionsManagerClass);
	GameSessionsManager->BroadcastJoinGameSessionMessage.AddDynamic(JoinGameWidget, &UDS_JoinGame::SetStatusMessage);
	
	JoinGameWidget->Button_JoinGame->OnClicked.AddDynamic(this, &UDS_GamePage::JoinGameButtonClicked);
}

void UDS_GamePage::JoinGameButtonClicked()
{
	JoinGameWidget->Button_JoinGame->SetIsEnabled(false);
	GameSessionsManager->JoinGameSession();
}
#pragma endregion
/*-------------------------------------------------------------------------*/