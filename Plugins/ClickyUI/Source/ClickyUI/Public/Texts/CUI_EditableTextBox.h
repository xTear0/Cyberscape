// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_EditableTextBox.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCUI_OnEditableTextChangedEvent, const FText&, Text);
class UEditableTextBox;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_EditableTextBox.h_Class
UCLASS()
class CLICKYUI_API UCUI_EditableTextBox : public UCUI_Widget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "CUI_EditableText|Event")
	FCUI_OnEditableTextChangedEvent OnTextChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText HintText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Text is Password?"))
	bool bIsPassword = false;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> UE_EditableTextBox;

	void SetEditableTextHint(const FText& Text) const;
	void SetText(const FText& Text) const;
	FText GetText() const;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UFUNCTION()	void HandleTextChanged(const FText& Text);
};
#pragma endregion
/*-------------------------------------------------------------------------*/
