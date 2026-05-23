// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_Menu_Hamburger_Expanded.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCUI_Button_Wide;
class UScrollBox;
class UTextBlock;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Menu_Hamburger_FocusLost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Menu_Hamburger_OnCollapsedAnimationFinished);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Menu_Hamburger_Expanded.h_Class
UCLASS(Abstract)
class CLICKYUI_API UCUI_Menu_Hamburger_Expanded : public UCUI_Widget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	float DelayTime = 0.05f;

	UPROPERTY()
	FCUI_Menu_Hamburger_OnCollapsedAnimationFinished OnCollapsedAnimationFinished;

	UPROPERTY()
	FCUI_Menu_Hamburger_FocusLost FocusLostDelegate;

	UPROPERTY(BlueprintReadOnly, Category = "Hamburger Menu")
	TArray<TObjectPtr<UCUI_Button_Wide>> SelectionButtons;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ScrollBox_Selections;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Wide> Button_Selection1;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCUI_Button_Wide> Button_Selection2;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCUI_Button_Wide> Button_Selection3;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCUI_Button_Wide> Button_Selection4;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCUI_Button_Wide> Button_Selection5;

	// Add more as needed, five should be enough. BindWidgetOptional, so you may use less if necessary, min 1.

	void PlayExpandedAnimation();
	void PlayCollapsedAnimation();
	void ClearAnimations();

	void ClearWidgetOpacity();

protected:

	virtual void NativeConstruct() override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;

	friend class UCUI_Menu_Hamburger;

};
#pragma endregion
/*-------------------------------------------------------------------------*/
