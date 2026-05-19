// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/SYS7_Widget.h"
#include "SYS7_Menu_Kebab.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class USYS7_Button_Square;
class UImage;
class UDS_UITheme;

UENUM(BlueprintType)
enum class ESYS7_Menu_Kebab_Selection : uint8
{
	Selection1  UMETA(DisplayName = "Selection 1"),
	Selection2  UMETA(DisplayName = "Selection 2"),
	Selection3  UMETA(DisplayName = "Selection 3"),
	None UMETA(DisplayName = "Unselected")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSYS7_Menu_Kebab_OnSelectionChanged,
	ESYS7_Menu_Kebab_Selection, NewSelection);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_Menu_Kebab.h_Class
UCLASS()
class SYSTEM7_API USYS7_Menu_Kebab : public USYS7_Widget
{
	GENERATED_BODY()
public:
	/** Broadcasts whenever the user picks a new selection. Bind to this in subclasses or owning widgets. */
	UPROPERTY(BlueprintAssignable, Category = "Kebab Menu")
	FSYS7_Menu_Kebab_OnSelectionChanged OnSelectionChanged;
	
	UPROPERTY(BlueprintReadOnly, Category = "Kebab Menu")
	ESYS7_Menu_Kebab_Selection ActiveSelection = ESYS7_Menu_Kebab_Selection::Selection1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_Button_Square> Button_Kebab1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_Button_Square> Button_Kebab2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_Button_Square> Button_Kebab3;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	
	UFUNCTION(BlueprintNativeEvent, Category = "Kebab Menu")
	void NativeOnSelectionChanged(ESYS7_Menu_Kebab_Selection NewSelection);
	virtual void NativeOnSelectionChanged_Implementation(ESYS7_Menu_Kebab_Selection NewSelection) {};

private:
	void BindButtons();
	void UpdateSelection(ESYS7_Menu_Kebab_Selection OldSelection, ESYS7_Menu_Kebab_Selection NewSelection);

	UFUNCTION()	void HandleSelectionButtonClicked(ESYS7_Menu_Kebab_Selection NewSelection);
    
	UFUNCTION() void OnBtn1Clicked() { HandleSelectionButtonClicked(ESYS7_Menu_Kebab_Selection::Selection1); }
	UFUNCTION() void OnBtn2Clicked() { HandleSelectionButtonClicked(ESYS7_Menu_Kebab_Selection::Selection2); }
	UFUNCTION() void OnBtn3Clicked() { HandleSelectionButtonClicked(ESYS7_Menu_Kebab_Selection::Selection3); }
};
#pragma endregion
/*-------------------------------------------------------------------------*/