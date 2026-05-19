// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/DS_EnumTypes.h"
#include "DS_SignUpPage.generated.h"
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
#pragma region DS_SignUpPage.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_SignUpPage : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_EditableTextBox> TextBox_Username;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_EditableTextBox> TextBox_Password;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_EditableTextBox> TextBox_ConfirmPassword;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_EditableTextBox> TextBox_Email;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_Button_Wide> Button_SignUp;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_Button_Wide> Button_AlreadyHaveCode;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USYS7_Button_Wide> Button_Back;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBox_StatusMessage;

	UFUNCTION()
	void UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets, EDS_DelegateResponse DelegateResponse);
	
	UFUNCTION()
	void ClearTextBoxes() const;
	
protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void UpdateSignUpButtonState(const FText& Text);

	bool IsValidEmail();
	bool IsValidUsername();
	bool IsStrongPassword();

};
#pragma endregion
/*-------------------------------------------------------------------------*/