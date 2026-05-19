// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DS_APITestHUD.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UDS_APITestOverlay;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ADS_APITestHUD.h_Class
UCLASS()
class DEDICATEDSERVERS_API ADS_APITestHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_APITestOverlay> APITestOverlayClass;

private:
	UPROPERTY()
	TObjectPtr<UDS_APITestOverlay> APITestOverlay;
};
#pragma endregion
/*-------------------------------------------------------------------------*/