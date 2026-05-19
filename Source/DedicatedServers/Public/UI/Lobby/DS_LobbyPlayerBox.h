// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_LobbyPlayerBox.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UScrollBox;
class UDS_PlayerLabel;
class ADS_LobbyState;
struct FDS_LobbyPlayerInfo;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_LobbyPlayerBox.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_LobbyPlayerBox : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ScrollBox_PlayerInfo;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_PlayerLabel> PlayerLabelClass;

protected:
	virtual void NativeOnInitialized() override;
	void UpdatePlayerInfo(ADS_LobbyState* LobbyState);
	
	UFUNCTION()
	void OnLobbyStateInitialized(ADS_LobbyState* LobbyState);
	
	UFUNCTION()
	void CreateAndAddPlayerLabel(const FDS_LobbyPlayerInfo& LobbyPlayerInfo);

	UFUNCTION()
	void OnPlayerRemoved(const FDS_LobbyPlayerInfo& LobbyPlayerInfo);

private:
	UDS_PlayerLabel* FindPlayerLabel(const FString& Username);
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/