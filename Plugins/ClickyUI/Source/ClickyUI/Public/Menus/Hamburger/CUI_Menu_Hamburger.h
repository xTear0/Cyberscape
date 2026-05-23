// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_Menu_Hamburger.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UWidgetSwitcher;
class UCUI_Button_Wide;
class UTextBlock;
class UCUI_Menu_Hamburger_Expanded;
class UCUI_StyleAsset;

UENUM(BlueprintType)
enum class ECUI_Menu_Hamburger_Selection : uint8
{
	Selection1  UMETA(DisplayName = "Selection 1"),
	Selection2  UMETA(DisplayName = "Selection 2"),
	Selection3  UMETA(DisplayName = "Selection 3"),
	Selection4  UMETA(DisplayName = "Selection 4"),
	Selection5  UMETA(DisplayName = "Selection 5")
	// Add more as needed...
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCUI_Menu_Hamburger_OnSelectionChanged,
	ECUI_Menu_Hamburger_Selection, NewSelection);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Menu_Hamburger.h_Class
UCLASS()
class CLICKYUI_API UCUI_Menu_Hamburger : public UCUI_Widget
{
	GENERATED_BODY()

public:
		UPROPERTY(EditDefaultsOnly, Category="Style")
		TObjectPtr<UCUI_StyleAsset> StyleAsset;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Menu Properties")
		TArray<FText> HamburgerOptions =
		{
			FText::FromString("Hamburger"),
			FText::FromString("Cheeseburger"),
			FText::FromString("Veggieburger")
		};

		/** Broadcasts whenever the user picks a new selection. Bind to this in subclasses or owning widgets. */
    	UPROPERTY(BlueprintAssignable, Category = "Hamburger Menu")
    	FCUI_Menu_Hamburger_OnSelectionChanged OnSelectionChanged;

    	UPROPERTY(BlueprintReadOnly, Category = "Hamburger Menu")
    	ECUI_Menu_Hamburger_Selection ActiveSelection;

		/* How many selection options do you want your menu to have? */
    	UPROPERTY(VisibleInstanceOnly, Category = "Hamburger Menu")
    	int32 HamburgerSelectionsAmount;

    	UPROPERTY(meta = (BindWidget))
    	TObjectPtr<UCUI_Button_Wide> Button_Hamburger;

    	UPROPERTY(meta = (BindWidget))
    	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

		/* This should be set to an empty widget. */
    	UPROPERTY(meta = (BindWidget))
    	TObjectPtr<UCUI_Widget> Menu_Collapsed;

    	UPROPERTY(meta = (BindWidget))
    	TObjectPtr<UCUI_Menu_Hamburger_Expanded> Menu_Expanded;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Hamburger Menu")
	void NativeOnSelectionChanged(ECUI_Menu_Hamburger_Selection NewSelection);

	virtual void NativeOnSelectionChanged_Implementation(ECUI_Menu_Hamburger_Selection NewSelection) {};

	UFUNCTION(BlueprintCallable, Category = "Hamburger Menu")
	void Expand();

	UFUNCTION(BlueprintCallable, Category = "Hamburger Menu")
	void Collapse();

	UFUNCTION(BlueprintPure, Category = "Hamburger Menu")
	bool IsExpanded() const { return bIsExpanded; }

	UFUNCTION()
	void FinalizeCollapse();

private:

    bool bIsExpanded = false;

    UFUNCTION()	void ToggleDropdown();

	void InitializeButtons();
    void BindButtons();
    void UpdateActiveSelectionText(ECUI_Menu_Hamburger_Selection NewSelection) const;

    UFUNCTION()	void HandleSelectionButtonClicked(ECUI_Menu_Hamburger_Selection NewSelection);

    UFUNCTION() void OnBtn1Clicked() { HandleSelectionButtonClicked(ECUI_Menu_Hamburger_Selection::Selection1); }
    UFUNCTION() void OnBtn2Clicked() { HandleSelectionButtonClicked(ECUI_Menu_Hamburger_Selection::Selection2); }
    UFUNCTION() void OnBtn3Clicked() { HandleSelectionButtonClicked(ECUI_Menu_Hamburger_Selection::Selection3); }
    UFUNCTION() void OnBtn4Clicked() { HandleSelectionButtonClicked(ECUI_Menu_Hamburger_Selection::Selection4); }
    UFUNCTION() void OnBtn5Clicked() { HandleSelectionButtonClicked(ECUI_Menu_Hamburger_Selection::Selection5); }
};
#pragma endregion
/*-------------------------------------------------------------------------*/
