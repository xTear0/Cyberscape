// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/DS_EnumTypes.h"
#include "DS_AlreadyHaveCodePage.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCUI_EditableTextBox;
class UCUI_Button_Wide;
class UTextBlock;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_SignInPage.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_AlreadyHaveCodePage : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_EditableTextBox> TextBox_Username;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_EditableTextBox> TextBox_ConfirmationCode;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Wide> Button_ConfirmCode;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Wide> Button_ResendCode;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Wide> Button_Back;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBox_StatusMessage;
	void ClearTextBoxes() const;

	UFUNCTION()
	void UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets, EDS_DelegateResponse DelegateResponse);

protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void UpdateButtonStates(const FText& Text);
	
	bool IsValidUsername();
	bool IsSixDigitsEntered();
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/