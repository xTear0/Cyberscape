// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_Button_Checkbox.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCUI_Button_Checkbox_OnCheckStateChangedEvent, bool, bIsChecked);
class UCheckBox;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Button_Checkbox.h_Class
UCLASS()
class CLICKYUI_API UCUI_Button_Checkbox : public UCUI_Widget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
	FCUI_Button_Checkbox_OnCheckStateChangedEvent OnCheckStateChanged;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> UE_CheckBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CUI_Button|Defaults")
	bool bDefaultChecked = false;

	UFUNCTION(BlueprintCallable, Category = "CUI_Button")
	void SetChecked(bool bInChecked);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CUI_Button")
	bool IsChecked() const;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UFUNCTION() void HandleCheckStateChanged(bool bIsCheckedNew);
};
#pragma endregion
/*-------------------------------------------------------------------------*/
