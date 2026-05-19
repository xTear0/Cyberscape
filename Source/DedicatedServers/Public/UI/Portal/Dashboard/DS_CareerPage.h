// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menus/Kebab/SYS7_Menu_Kebab.h"
#include "DS_CareerPage.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UWidgetSwitcher;
class UDS_CareerPage_Statistics;
class UDS_CareerPage_Leaderboards;
class UDS_CareerPage_Achievements;
enum class EKebabWidgetSelection : uint8;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_CareerPage.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_CareerPage : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_Menu_Kebab> KebabMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> PageSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDS_CareerPage_Achievements> Page_Achievements;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDS_CareerPage_Leaderboards> Page_Leaderboards;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDS_CareerPage_Statistics> Page_Statistics;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SwitchToPage(ESYS7_Menu_Kebab_Selection PageSelection);
};
#pragma endregion
/*-------------------------------------------------------------------------*/