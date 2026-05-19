// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/SYS7_Widget.h"
#include "SYS7_Menu_Hamburger_Expanded.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class USYS7_Button_Wide;
class UScrollBox;
class UTextBlock;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSYS7_Menu_Hamburger_FocusLost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSYS7_Manu_Hamburger_OnCollapsedAnimationFinished);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_Menu_Hamburger.h_Class
UCLASS(Abstract)
class SYSTEM7_API USYS7_Menu_Hamburger_Expanded : public USYS7_Widget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	float DelayTime = 0.05f;

	UPROPERTY()
	FSYS7_Manu_Hamburger_OnCollapsedAnimationFinished OnCollapsedAnimationFinished;
	
	UPROPERTY()
	FSYS7_Menu_Hamburger_FocusLost FocusLostDelegate;
    
	UPROPERTY(BlueprintReadOnly, Category = "Hamburger Menu")
	TArray<TObjectPtr<USYS7_Button_Wide>> SelectionButtons;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ScrollBox_Selections;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_Button_Wide> Button_Selection1;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<USYS7_Button_Wide> Button_Selection2;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<USYS7_Button_Wide> Button_Selection3;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<USYS7_Button_Wide> Button_Selection4;
    
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<USYS7_Button_Wide> Button_Selection5;

	// Add more as needed, five should be enough. BindWidgetOptional, so you may use less if necessary, min 1.
	
	void PlayExpandedAnimation();
	void PlayCollapsedAnimation();
	void ClearAnimations();
	
	void ClearWidgetOpacity();
	
protected:

	virtual void NativeConstruct() override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;
    
	friend class USYS7_Menu_Hamburger;
    
};
#pragma endregion
/*-------------------------------------------------------------------------*/