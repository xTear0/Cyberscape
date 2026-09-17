// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Interfaces/DS_HUDManagement.h"
#include "DS_PortalHUD.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UDS_SignInOverlay;
class UDS_DashboardOverlay;
class UCUI_NotificationOverlay;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_PortalHUD.h_Class
UCLASS()
class DEDICATEDSERVERS_API ADS_PortalHUD : public AHUD, public IDS_HUDManagement
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCUI_NotificationOverlay> NotificationOverlayClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_SignInOverlay> SignInOverlayClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_DashboardOverlay> DashboardOverlayClass;

	// IDS_HUDManagement Interface
	virtual void OnSignIn() override;
	virtual void OnSignOut() override;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TObjectPtr<UDS_SignInOverlay> SignInOverlay;
	
	UPROPERTY()
	TObjectPtr<UDS_DashboardOverlay> DashboardOverlay;

	UPROPERTY()
	TObjectPtr<UCUI_NotificationOverlay> NotificationOverlay;
};
#pragma endregion
/*-------------------------------------------------------------------------*/