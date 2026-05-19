// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/APITest/DS_APITestOverlay.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "UI/API/ListFleets/DS_FleetID.h"
#include "UI/API/ListFleets/DS_ListFleetsBox.h"
#include "UI/APITest/DS_APITestManager.h"
#include "UI/HTTP/DS_HTTPRequestTypes.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_APITestOverlay.cpp_Functions
void UDS_APITestOverlay::NativeConstruct()
{
	Super::NativeConstruct();
	
	check(APITestManagerClass)
	APITestManager = NewObject<UDS_APITestManager>(this, APITestManagerClass);

	check(ListFleetsBox)
	check(ListFleetsBox->Button_ListFleets)
	ListFleetsBox->Button_ListFleets->OnClicked.AddDynamic(
		this, &UDS_APITestOverlay::ListFleetsButtonClicked);
	
}

void UDS_APITestOverlay::ListFleetsButtonClicked()
{
	check(APITestManager)
	APITestManager->OnListFleetsResponseReceived.AddDynamic(this, &UDS_APITestOverlay::OnListFleetsResponseReceived);
	APITestManager->ListFleets();
	ListFleetsBox->Button_ListFleets->SetIsEnabled(false);
}

void UDS_APITestOverlay::OnListFleetsResponseReceived(const FDS_ListFleetsResponse& Response, bool bWasSuccessful)
{
	if (APITestManager->OnListFleetsResponseReceived.IsAlreadyBound(this, &UDS_APITestOverlay::OnListFleetsResponseReceived))
	{
		APITestManager->OnListFleetsResponseReceived.RemoveDynamic(this, &UDS_APITestOverlay::OnListFleetsResponseReceived);
	}
	ListFleetsBox->ScrollBox_ListFleets->ClearChildren();
	if (bWasSuccessful)
	{
		for (const FString& FleetId : Response.FleetIds)
		{
			UDS_FleetID* FleetIdWidget = CreateWidget<UDS_FleetID>(this, FleetIDWidgetClass);
			FleetIdWidget->TextBlock_FleetID->SetText(FText::FromString(FleetId));
			ListFleetsBox->ScrollBox_ListFleets->AddChild(FleetIdWidget);
		}
	} else
	{
		UDS_FleetID* FleetIdWidget = CreateWidget<UDS_FleetID>(this, FleetIDWidgetClass);
		FleetIdWidget->TextBlock_FleetID->SetText(FText::FromString("Something went wrong!"));
		ListFleetsBox->ScrollBox_ListFleets->AddChild(FleetIdWidget);
	}
	ListFleetsBox->Button_ListFleets->SetIsEnabled(true);
}
#pragma endregion
/*-------------------------------------------------------------------------*/