// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/SYS7_Widget.h"
#include "SYS7_EditableTextBox.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSYS7_OnEditableTextChangedEvent, const FText&, Text);
class UEditableTextBox;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_EditableTextBox.h_Class
UCLASS()
class SYSTEM7_API USYS7_EditableTextBox : public USYS7_Widget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintAssignable, Category = "SYS7_EditableText|Event")
	FSYS7_OnEditableTextChangedEvent OnTextChanged;
	
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