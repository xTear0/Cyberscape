// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/DS_EnumTypes.h"
#include "DS_SignUpPageConfirmation.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class USYS7_EditableTextBox;
class USYS7_Button_Wide;
class UTextBlock;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_SignUpPageConfirmation.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_SignUpPageConfirmation : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_EditableTextBox> TextBox_ConfirmationCode;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_Button_Wide> Button_Confirm;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_Button_Wide> Button_Back;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBox_StatusMessage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBox_Destination;

	void ClearTextBoxes() const;

	UFUNCTION()
	void UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets, EDS_DelegateResponse DelegateResponse);

protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void UpdateConfirmButtonState(const FText& Text);
};
#pragma endregion
/*-------------------------------------------------------------------------*/