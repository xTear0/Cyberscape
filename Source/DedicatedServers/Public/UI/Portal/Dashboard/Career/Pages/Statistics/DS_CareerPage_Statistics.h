// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_CareerPage_Statistics.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCUI_Menu_Hamburger;
class UWidgetSwitcher;
class UDS_Career_Statistics_FFA;
class UDS_Career_Statistics_Deathmatch;
class UDS_Career_Statistics_Domination;
enum class ECUI_Menu_Hamburger_Selection : uint8;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_CareerPage_Statistics.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_CareerPage_Statistics : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Menu_Hamburger> Menu_Hamburger;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> StatsPageSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDS_Career_Statistics_Domination> Page_Domination;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDS_Career_Statistics_FFA> Page_FFA;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDS_Career_Statistics_Deathmatch> Page_Deathmatch;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UFUNCTION() void SwitchToPage(ECUI_Menu_Hamburger_Selection PageSelection);
};
#pragma endregion
/*-------------------------------------------------------------------------*/