// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Lobby/DS_LobbyPlayerBox.h"
#include "UI/Lobby/DS_PlayerLabel.h"
#include "Components/ScrollBox.h"
#include "Game/DS_GameState.h"
#include "Lobby/DS_LobbyState.h"
#include "Lobby/DS_LobbyPlayerInfo.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_LobbyPlayerBox.cpp_Functions
void UDS_LobbyPlayerBox::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ADS_GameState* DS_GameState = GetWorld()->GetGameState<ADS_GameState>();
	if (!IsValid(DS_GameState)) return;

	if (IsValid(DS_GameState->LobbyState))
	{
		OnLobbyStateInitialized(DS_GameState->LobbyState);
	}
	else
	{
		DS_GameState->OnLobbyStateInitialized.AddDynamic(this, &UDS_LobbyPlayerBox::OnLobbyStateInitialized);
	}
}

void UDS_LobbyPlayerBox::UpdatePlayerInfo(ADS_LobbyState* LobbyState)
{
	ScrollBox_PlayerInfo->ClearChildren();
	for (const FDS_LobbyPlayerInfo& PlayerInfo : LobbyState->GetPlayers())
	{
		CreateAndAddPlayerLabel(PlayerInfo);
	}
}

void UDS_LobbyPlayerBox::OnLobbyStateInitialized(ADS_LobbyState* LobbyState)
{
	if (!IsValid(LobbyState)) return;

	LobbyState->OnPlayerInfoAdded.AddDynamic(this, &UDS_LobbyPlayerBox::CreateAndAddPlayerLabel);
	LobbyState->OnPlayerInfoRemoved.AddDynamic(this, &UDS_LobbyPlayerBox::OnPlayerRemoved);
	UpdatePlayerInfo(LobbyState);
}

void UDS_LobbyPlayerBox::CreateAndAddPlayerLabel(const FDS_LobbyPlayerInfo& LobbyPlayerInfo)
{
	if (FindPlayerLabel(LobbyPlayerInfo.Username)) return;
	
	UDS_PlayerLabel* PlayerLabel = CreateWidget<UDS_PlayerLabel>(this, PlayerLabelClass);
	if (!IsValid(PlayerLabel)) return;

	PlayerLabel->SetUsername(LobbyPlayerInfo.Username);
	ScrollBox_PlayerInfo->AddChild(PlayerLabel);
}

void UDS_LobbyPlayerBox::OnPlayerRemoved(const FDS_LobbyPlayerInfo& LobbyPlayerInfo)
{
	if (UDS_PlayerLabel* PlayerLabel = FindPlayerLabel(LobbyPlayerInfo.Username))
	{
		ScrollBox_PlayerInfo->RemoveChild(PlayerLabel);
	}
}

UDS_PlayerLabel* UDS_LobbyPlayerBox::FindPlayerLabel(const FString& Username)
{
	for (UWidget* Child : ScrollBox_PlayerInfo->GetAllChildren())
	{
		UDS_PlayerLabel* PlayerLabel = Cast<UDS_PlayerLabel>(Child);
		if (IsValid(PlayerLabel) && PlayerLabel->GetUsername() == Username)
		{
			return PlayerLabel;
		}
	}
	return nullptr;
}
#pragma endregion
/*-------------------------------------------------------------------------*/
 