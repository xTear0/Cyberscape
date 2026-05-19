// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_DashboardOverlay.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UWidgetSwitcher;
class UDS_GamePage;
class UDS_CareerPage;
class UDS_LoadoutSwitcherPage;
class USYS7_Button_Wide;
class UDS_CareerInfoButton;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_DashboardOverlay.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_DashboardOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UWidgetSwitcher> DashboardSwitcher;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<USYS7_Button_Wide> Button_Home;							// TODO: Switches to the Character Selector
	UPROPERTY(meta = (BindWidget)) TObjectPtr<USYS7_Button_Wide> Button_Play;							// Switches to the Game Page.
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UDS_CareerInfoButton> Button_CareerWidget;	// Switches to the Career Page.
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UDS_GamePage> Page_Game;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UDS_CareerPage> Page_Career;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UDS_LoadoutSwitcherPage> Page_LoadoutSwitcher;


protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION() void ShowGamePage();
	UFUNCTION() void ShowCareerPage();
	UFUNCTION() void ShowLoadoutSwitcherPage();
};
#pragma endregion
/*-------------------------------------------------------------------------*/