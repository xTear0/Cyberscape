// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_APITestOverlay.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UDS_ListFleetsBox;
class UDS_APITestManager;
class UDS_FleetID;
struct FDS_ListFleetsResponse;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ADS_APITestOverlay.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_APITestOverlay : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_APITestManager> APITestManagerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDS_FleetID> FleetIDWidgetClass;

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDS_ListFleetsBox> ListFleetsBox;

	UPROPERTY()
	TObjectPtr<UDS_APITestManager> APITestManager;

	UFUNCTION()
	void ListFleetsButtonClicked();

	UFUNCTION()
	void OnListFleetsResponseReceived(const FDS_ListFleetsResponse& Response, bool bWasSuccessful);
};
#pragma endregion
/*-------------------------------------------------------------------------*/