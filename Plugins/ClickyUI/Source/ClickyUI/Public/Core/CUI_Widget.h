// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "CUI_StyleAsset.h"
#include "Blueprint/UserWidget.h"
#include "CUI_Widget.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style")
	TObjectPtr<UCUI_StyleAsset> StyleAsset;
	
protected:
	virtual void NativePreConstruct() override;

};
#pragma endregion
/*-------------------------------------------------------------------------*/
