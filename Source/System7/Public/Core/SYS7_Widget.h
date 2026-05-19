// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SYS7_Widget.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class USYS7_StyleAsset;
DECLARE_LOG_CATEGORY_EXTERN(LogSYS7, Log, All);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_Widget.h_Class
UCLASS()
class SYSTEM7_API USYS7_Widget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	void SanitizeWidgetBrushes(UWidget* Widget);
};
#pragma endregion
/*-------------------------------------------------------------------------*/