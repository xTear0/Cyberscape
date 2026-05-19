// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/APITest/DS_APITestHUD.h"
#include "UI/APITest/DS_APITestOverlay.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_APITestHUD.cpp_Functions
void ADS_APITestHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetOwningPlayerController();
	if (IsValid(PlayerController) && APITestOverlayClass)
	{
		APITestOverlay = CreateWidget<UDS_APITestOverlay>(PlayerController, APITestOverlayClass);
		APITestOverlay->AddToViewport();
	}
	
}
#pragma endregion
/*-------------------------------------------------------------------------*/
