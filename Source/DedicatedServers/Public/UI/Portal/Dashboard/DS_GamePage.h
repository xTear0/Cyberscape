// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_GamePage.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UWidgetSwitcher;
class UDS_GameSessionsManager;
class UDS_JoinGame;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_GamePage.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_GamePage : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDS_JoinGame> JoinGameWidget;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_GameSessionsManager> GameSessionsManagerClass;
	
protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION() void JoinGameButtonClicked();

	UPROPERTY()
	TObjectPtr<UDS_GameSessionsManager> GameSessionsManager;
};
#pragma endregion
/*-------------------------------------------------------------------------*/