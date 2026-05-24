// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_Menu_Dropdown.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCUI_Button_Wide;
class UWidgetSwitcher;
class UImage;
class UCUI_Menu_Dropdown_Expanded;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCUI_Menu_Dropdown_OnSelectionChangedEvent,
	int32, Index, const FText&, SelectedText);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Menu_Dropdown.h_Class
UCLASS()
class CLICKYUI_API UCUI_Menu_Dropdown : public UCUI_Widget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropdown Properties")
	FText DropdownLabel = FText::GetEmpty();

	/* Overrides the OptionsTitle on the expanded widget. Has no effect if left empty. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropdown Properties")
	FText ExpandedTitle = FText::GetEmpty();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropdown Properties")
	TArray<FText> DropdownOptions =
	{
		FText::FromString("Option 1"),
		FText::FromString("Option 2"),
		FText::FromString("Option 3")
	};

	/** Broadcasts whenever the user picks a new option. */
	UPROPERTY(BlueprintAssignable, Category = "Dropdown")
	FCUI_Menu_Dropdown_OnSelectionChangedEvent OnSelectionChanged;

	UPROPERTY(BlueprintReadOnly, Category = "Dropdown")
	int32 ActiveIndex = 0;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Wide> Button_ToggleDropdown;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	/* This should be set to an empty widget. */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Widget> Menu_Collapsed;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Menu_Dropdown_Expanded> Menu_Expanded;

	/* Optional arrow image — set Arrow_Up / Arrow_Down brushes to flip it on expand. */
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UImage> Image_Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropdown|Visuals")
	FSlateBrush Arrow_Up;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropdown|Visuals")
	FSlateBrush Arrow_Down;

	UFUNCTION(BlueprintCallable, Category = "Dropdown")
	void Expand();

	UFUNCTION(BlueprintCallable, Category = "Dropdown")
	void Collapse();

	UFUNCTION(BlueprintPure, Category = "Dropdown")
	bool IsExpanded() const { return bIsExpanded; }

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;

private:

	bool bIsExpanded = false;

	UFUNCTION() void ToggleDropdown();

	void BindOptions();
	void InitializeOptions();
	void HandleOptionSelected(int32 Index);

	UFUNCTION() void OnOpt1Clicked() { HandleOptionSelected(0); }
	UFUNCTION() void OnOpt2Clicked() { HandleOptionSelected(1); }
	UFUNCTION() void OnOpt3Clicked() { HandleOptionSelected(2); }
	UFUNCTION() void OnOpt4Clicked() { HandleOptionSelected(3); }
	UFUNCTION() void OnOpt5Clicked() { HandleOptionSelected(4); }
};
#pragma endregion
/*-------------------------------------------------------------------------*/
