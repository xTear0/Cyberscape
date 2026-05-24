// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_Menu_Dropdown_Expanded.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCUI_Button_Wide;
class UScrollBox;
class UTextBlock;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Menu_Dropdown_FocusLost);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Menu_Dropdown_Expanded.h_Class
UCLASS(Abstract)
class CLICKYUI_API UCUI_Menu_Dropdown_Expanded : public UCUI_Widget
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FCUI_Menu_Dropdown_FocusLost FocusLostDelegate;

	UPROPERTY(BlueprintReadOnly, Category = "Dropdown")
	TArray<TObjectPtr<UCUI_Button_Wide>> OptionButtons;

	/* Optional section/category label shown above the options list (e.g. "Account Management"). */
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> TextBlock_OptionsTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropdown")
	FText OptionsTitle = FText::GetEmpty();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ScrollBox_Options;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Wide> Button_Option1;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCUI_Button_Wide> Button_Option2;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCUI_Button_Wide> Button_Option3;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCUI_Button_Wide> Button_Option4;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCUI_Button_Wide> Button_Option5;

	// Add more as needed, five should be enough. BindWidgetOptional, so you may use less if necessary, min 1.

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;

	friend class UCUI_Menu_Dropdown;

};
#pragma endregion
/*-------------------------------------------------------------------------*/
