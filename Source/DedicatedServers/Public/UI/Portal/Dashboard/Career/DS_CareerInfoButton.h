// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_CareerInfoButton.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UButton;
class UImage;
class UDS_CareerXPBar;
class UTextBlock;
class UDS_CareerCurrency;
/*-------------------------------------------------------------------------*/

/*
 *	This UButton Subclass contains some unique properties that become
 *	clear in the Dashboard. For one, this is a miniature version of
 *	the career page itself, showing the player's name, class icon, the
 *	player's rank or title, the player's reputation badge, the player's
 *	currency, and of course the player's XP progress bar. Clicking on
 *	the widget will bring up the career page.
 */

/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_CareerInfoButton.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_CareerInfoButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget)) UButton* Button_Career;			// The Button that covers the whole widget.
	UPROPERTY(meta = (BindWidget)) UImage* Image_Class;				// The Player's Class Image.
	UPROPERTY(meta = (BindWidget)) UDS_CareerXPBar* CareerXPBar;	// The Player's XP Bar + XP amount.
	UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlock_Title;		// The Player's Title / Rank.
	UPROPERTY(meta = (BindWidget)) UDS_CareerCurrency* CareerCurrency;	// The Player's Credits and Platinum.
		
};
#pragma endregion
/*-------------------------------------------------------------------------*/