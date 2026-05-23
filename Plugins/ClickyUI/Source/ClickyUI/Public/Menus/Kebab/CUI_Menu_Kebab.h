// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_Menu_Kebab.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCUI_Button_Square;
class UImage;

UENUM(BlueprintType)
enum class ECUI_Menu_Kebab_Selection : uint8
{
	Selection1  UMETA(DisplayName = "Selection 1"),
	Selection2  UMETA(DisplayName = "Selection 2"),
	Selection3  UMETA(DisplayName = "Selection 3"),
	None UMETA(DisplayName = "Unselected")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCUI_Menu_Kebab_OnSelectionChanged,
	ECUI_Menu_Kebab_Selection, NewSelection);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Menu_Kebab.h_Class
UCLASS()
class CLICKYUI_API UCUI_Menu_Kebab : public UCUI_Widget
{
	GENERATED_BODY()

public:
	/** Broadcasts whenever the user picks a new selection. Bind to this in subclasses or owning widgets. */
	UPROPERTY(BlueprintAssignable, Category = "Kebab Menu")
	FCUI_Menu_Kebab_OnSelectionChanged OnSelectionChanged;

	UPROPERTY(BlueprintReadOnly, Category = "Kebab Menu")
	ECUI_Menu_Kebab_Selection ActiveSelection = ECUI_Menu_Kebab_Selection::Selection1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Square> Button_Kebab1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Square> Button_Kebab2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Square> Button_Kebab3;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Kebab Menu")
	void NativeOnSelectionChanged(ECUI_Menu_Kebab_Selection NewSelection);
	virtual void NativeOnSelectionChanged_Implementation(ECUI_Menu_Kebab_Selection NewSelection) {};

private:
	void BindButtons();
	void UpdateSelection(ECUI_Menu_Kebab_Selection OldSelection, ECUI_Menu_Kebab_Selection NewSelection);

	UFUNCTION()	void HandleSelectionButtonClicked(ECUI_Menu_Kebab_Selection NewSelection);

	UFUNCTION() void OnBtn1Clicked() { HandleSelectionButtonClicked(ECUI_Menu_Kebab_Selection::Selection1); }
	UFUNCTION() void OnBtn2Clicked() { HandleSelectionButtonClicked(ECUI_Menu_Kebab_Selection::Selection2); }
	UFUNCTION() void OnBtn3Clicked() { HandleSelectionButtonClicked(ECUI_Menu_Kebab_Selection::Selection3); }
};
#pragma endregion
/*-------------------------------------------------------------------------*/
