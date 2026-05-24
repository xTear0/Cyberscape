// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/DS_EnumTypes.h"
#include "DS_SignInPage.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UButton;
class UTextBlock;
class USoundBase;
class UCUI_Button_Wide;
class UCUI_EditableTextBox;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_SignInPage.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_SignInPage : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_EditableTextBox> TextBox_Username;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_EditableTextBox> TextBox_Password;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Wide> Button_SignIn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Wide> Button_SignUp;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCUI_Button_Wide> Button_Quit;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBox_StatusMessage;
	
	UFUNCTION()
	void UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets, EDS_DelegateResponse DelegateResponse);

	UFUNCTION()
	void UpdateSignInButtonState(const FText& Text);

	UFUNCTION()
	void ClearTextBoxes();

private:
	bool IsValidUsername();
	bool IsValidPassword();
};
#pragma endregion
/*-------------------------------------------------------------------------*/