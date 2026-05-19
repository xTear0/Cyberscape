// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_AccountDropdown_Expanded.generated.h"
/*-------------------------------------------------------------------------*/


class UDS_LocalPlayerSubsystem;
/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UButton;
class UTextBlock;
class UDS_UITheme;
enum class EDS_DelegateResponse : uint8;
class UDS_PortalManager;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_AccountDropdown_Expanded.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_AccountDropdown_Expanded : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_PortalManager> PortalManagerClass;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDS_UITheme> Theme_Asset;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_SignOut;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_SignOutButtonText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Email;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_SignOutStatusMessage;
	
	UPROPERTY() FSlateColor HoveredTextColor;
	UPROPERTY() FSlateColor UnhoveredTextColor;

	void ClearStatusMessageText() const;
		
protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	
	void SetStyleSignOutButtonTransparent() const;

	UFUNCTION()	void SignOutButton_Hover();
	UFUNCTION()	void SignOutButton_Unhover();
	UFUNCTION()	void SignOutButton_OnClicked();

	UFUNCTION()	void UpdateSignOutStatusMessage(
		const FString& Message,
		bool bShouldResetWidgets,
		EDS_DelegateResponse DelegateResponse);

	UFUNCTION() void StatusMessageSoundEvent(
		const FString& Message,
		bool bShouldResetWidgets,
		EDS_DelegateResponse DelegateResponse);

private:
	
	UPROPERTY()
	TObjectPtr<UDS_PortalManager> PortalManager;

	UDS_LocalPlayerSubsystem* GetLocalPlayerSubsystem();
};
#pragma endregion
/*-------------------------------------------------------------------------*/