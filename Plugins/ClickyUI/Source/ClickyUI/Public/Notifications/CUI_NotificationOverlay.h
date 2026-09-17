// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "CUI_NotificationStack.h"
#include "Core/CUI_Widget.h"
#include "CUI_NotificationOverlay.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region CUI_NotificationOverlay.h_Class
UCLASS()
class CLICKYUI_API UCUI_NotificationOverlay : public UCUI_Widget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_NotificationStack> NotificationStack;
protected:

private:
};
#pragma endregion
/*-------------------------------------------------------------------------*/
