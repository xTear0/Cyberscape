// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_Button_Switchbox.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCUI_Button_Switchbox_OnToggledEvent, bool, bIsOn);
class UButton;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Button_Switchbox.h_Class
UCLASS()
class CLICKYUI_API UCUI_Button_Switchbox : public UCUI_Widget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
	FCUI_Button_Switchbox_OnToggledEvent OnToggled;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> UE_Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CUI_Button|Defaults")
	bool bDefaultOn = false;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* Anim_TurnOn;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* Anim_TurnOff;

	UFUNCTION(BlueprintCallable, Category = "CUI_Button")
	void SetIsOn(bool bInIsOn);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CUI_Button")
	bool GetIsOn() const { return bIsOn; }

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	bool bIsOn = false;

	void PlayStateAnimation();

	UFUNCTION() void HandleClicked();
};
#pragma endregion
/*-------------------------------------------------------------------------*/
