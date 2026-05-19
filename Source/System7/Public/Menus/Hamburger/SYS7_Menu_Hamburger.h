// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/SYS7_Widget.h"
#include "SYS7_Menu_Hamburger.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UWidgetSwitcher;
class USYS7_Button_Wide;
class UTextBlock;
class USYS7_Menu_Hamburger_Expanded;
class USYS7_StyleAsset;

UENUM(BlueprintType)
enum class ESYS7_Menu_Hamburger_Selection : uint8
{
	Selection1  UMETA(DisplayName = "Selection 1"),
	Selection2  UMETA(DisplayName = "Selection 2"),
	Selection3  UMETA(DisplayName = "Selection 3"),
	Selection4  UMETA(DisplayName = "Selection 4"),
	Selection5  UMETA(DisplayName = "Selection 5")
	// Add more as needed...
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSYS7_Menu_Hamburger_OnSelectionChanged,
	ESYS7_Menu_Hamburger_Selection, NewSelection);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_Menu_Hamburger.h_Class
UCLASS()
class SYSTEM7_API USYS7_Menu_Hamburger : public USYS7_Widget
{
	GENERATED_BODY()

public:
		UPROPERTY(EditDefaultsOnly, Category="Style")
		TObjectPtr<USYS7_StyleAsset> StyleAsset;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Menu Properties")
		TArray<FText> HamburgerOptions =
		{
			FText::FromString("Hamburger"),
			FText::FromString("Cheeseburger"),
			FText::FromString("Veggieburger")
		};
	
		/** Broadcasts whenever the user picks a new selection. Bind to this in subclasses or owning widgets. */
    	UPROPERTY(BlueprintAssignable, Category = "Hamburger Menu")
    	FSYS7_Menu_Hamburger_OnSelectionChanged OnSelectionChanged;
	
    	UPROPERTY(BlueprintReadOnly, Category = "Hamburger Menu")
    	ESYS7_Menu_Hamburger_Selection ActiveSelection;

		/* How many selection options do you want your menu to have? */
    	UPROPERTY(VisibleInstanceOnly, Category = "Hamburger Menu")
    	int32 HamburgerSelectionsAmount;
    
    	UPROPERTY(meta = (BindWidget))
    	TObjectPtr<USYS7_Button_Wide> Button_Hamburger;
    
    	UPROPERTY(meta = (BindWidget))
    	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

		/* This should be set to an empty widget. */
    	UPROPERTY(meta = (BindWidget))
    	TObjectPtr<USYS7_Widget> Menu_Collapsed;
    	
    	UPROPERTY(meta = (BindWidget))
    	TObjectPtr<USYS7_Menu_Hamburger_Expanded> Menu_Expanded;
    
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;
    	
	UFUNCTION(BlueprintNativeEvent, Category = "Hamburger Menu")
	void NativeOnSelectionChanged(ESYS7_Menu_Hamburger_Selection NewSelection);
    	
	virtual void NativeOnSelectionChanged_Implementation(ESYS7_Menu_Hamburger_Selection NewSelection) {};
	
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
    void UpdateActiveSelectionText(ESYS7_Menu_Hamburger_Selection NewSelection) const;

    UFUNCTION()	void HandleSelectionButtonClicked(ESYS7_Menu_Hamburger_Selection NewSelection);
    
    UFUNCTION() void OnBtn1Clicked() { HandleSelectionButtonClicked(ESYS7_Menu_Hamburger_Selection::Selection1); }
    UFUNCTION() void OnBtn2Clicked() { HandleSelectionButtonClicked(ESYS7_Menu_Hamburger_Selection::Selection2); }
    UFUNCTION() void OnBtn3Clicked() { HandleSelectionButtonClicked(ESYS7_Menu_Hamburger_Selection::Selection3); }
    UFUNCTION() void OnBtn4Clicked() { HandleSelectionButtonClicked(ESYS7_Menu_Hamburger_Selection::Selection4); }
    UFUNCTION() void OnBtn5Clicked() { HandleSelectionButtonClicked(ESYS7_Menu_Hamburger_Selection::Selection5); }
};
#pragma endregion
/*-------------------------------------------------------------------------*/