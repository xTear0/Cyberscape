// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUI_Widget.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCUI_StyleAsset;
DECLARE_LOG_CATEGORY_EXTERN(LogCUI, Log, All);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Widget.h_Class
UCLASS()
class CLICKYUI_API UCUI_Widget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	void SanitizeWidgetBrushes(UWidget* Widget);
};
#pragma endregion
/*-------------------------------------------------------------------------*/
