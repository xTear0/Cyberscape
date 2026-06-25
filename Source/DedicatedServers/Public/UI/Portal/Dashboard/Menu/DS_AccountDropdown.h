// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "DS_MenuDropdown.h"
#include "Menus/Dropdown/CUI_Menu_Dropdown.h"
#include "DS_AccountDropdown.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UDS_LocalPlayerSubsystem;
class UDS_PortalManager;
enum class EDS_DelegateResponse : uint8;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_AccountDropdown.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_AccountDropdown : public UCUI_Menu_Dropdown
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_PortalManager> PortalManagerClass;

	UPROPERTY()
	TObjectPtr<UDS_PortalManager> PortalManager;
	
protected:
	virtual void NativeConstruct() override;

private:
	UDS_LocalPlayerSubsystem* GetLocalPlayerSubsystem() const;

	UFUNCTION() void ChangePasswordButton_OnClicked();
	UFUNCTION() void ChangeEmailButton_OnClicked();
	UFUNCTION() void ContactSupportButton_OnClicked();
	UFUNCTION() void SignOutButton_OnClicked();

	UFUNCTION()	void UpdateSignOutStatusMessage(
	const FString& Message,
	bool bShouldResetWidgets,
	EDS_DelegateResponse DelegateResponse);

	UFUNCTION() void StatusMessageSoundEvent(
		const FString& Message,
		bool bShouldResetWidgets,
		EDS_DelegateResponse DelegateResponse);

};
#pragma endregion
/*-------------------------------------------------------------------------*/