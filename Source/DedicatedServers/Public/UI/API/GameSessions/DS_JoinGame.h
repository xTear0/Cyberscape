// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_JoinGame.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCUI_Button_Wide;
class UTextBlock;
class UDS_UITheme;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_JoinGame.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_JoinGame : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDS_UITheme> Theme_Asset;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Wide> Button_JoinGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_StatusMessage;

	UFUNCTION()
	void SetStatusMessage(const FString& StatusMessage, bool bShouldResetWidgets, EDS_DelegateResponse DelegateResponse);
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/