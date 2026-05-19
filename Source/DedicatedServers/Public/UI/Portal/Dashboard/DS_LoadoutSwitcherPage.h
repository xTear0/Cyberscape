// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_LoadoutSwitcherPage.generated.h"
/*-------------------------------------------------------------------------*/

/**
 * This class manages a player's active loadout. From here, you can view your weapons,
 * armor, and skill tree, as well as equip, upgrade, sell, and every other action you
 * would expect to use to manage your loadout. It inherently is a widget switcher
 * consisting of pages for each of those things.
 **/

/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UWidgetSwitcher;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_LoadoutSwitcherPage.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_LoadoutSwitcherPage : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> LoadoutSwitcher;

	
};
#pragma	endregion
/*-------------------------------------------------------------------------*/