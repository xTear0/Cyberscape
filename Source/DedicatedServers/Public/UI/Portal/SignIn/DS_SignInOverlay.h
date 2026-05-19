// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "DS_AlreadyHaveCodePage.h"
#include "Blueprint/UserWidget.h"
#include "DS_SignInOverlay.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UDS_JoinGame;
class UDS_PortalManager;
class UWidgetSwitcher;
class UDS_SignInPage;
class UDS_SignUpPage;
class UDS_SignUpPageConfirmation;
class UDS_SignUpSuccess;
class UButton;
class UDS_UITheme;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_SignInOverlay.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_SignInOverlay : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_PortalManager> PortalManagerClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDS_UITheme> Theme_Asset;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UFUNCTION()
	void StatusMessageSoundEvent(const FString& Message, bool bShouldResetWidgets, EDS_DelegateResponse DelegateResponse);

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY()
	TObjectPtr<UDS_PortalManager> PortalManager;

	
	// Widget Switcher Subclasses
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UDS_SignInPage> SignInPage;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UDS_SignUpPage> SignUpPage;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UDS_SignUpPageConfirmation> SignUpPageConfirmation;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UDS_SignUpSuccess> SignUpSuccess;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UDS_AlreadyHaveCodePage> AlreadyHaveCodePage;
	
	UFUNCTION()
	void ShowSignInPage();

	UFUNCTION()
	void ShowSignUpPage();

	UFUNCTION()
	void ShowAlreadyHaveCodePage();
	
	UFUNCTION()
	void ShowSignUpPageConfirmation();
	
	UFUNCTION()
	void ShowSignUpSuccess();

	UFUNCTION()
	void SignInButtonClicked();

	UFUNCTION()
	void SignUpButtonClicked();

	UFUNCTION()
	void AuthConfirmButtonClicked();

	UFUNCTION()
	void AlreadyHaveCodeButtonClicked();
	
	UFUNCTION()
	void AlreadyHaveCodeConfirmButtonClicked();

	UFUNCTION()
	void ResendAuthCodeButtonClicked();

	UFUNCTION()
	void OnSignUpSucceeded();

	UFUNCTION()
	void OnAuthenticationSucceeded();
};
#pragma endregion
/*-------------------------------------------------------------------------*/