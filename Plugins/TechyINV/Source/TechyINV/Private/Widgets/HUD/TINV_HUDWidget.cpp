// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/HUD/TINV_HUDWidget.h"
#include "InventoryManagement/Components/TINV_InventoryComponent.h"
#include "InventoryManagement/Utils/TINV_InventoryStatics.h"
#include "Notifications/CUI_NotificationManager.h"
#include "Notifications/CUI_TextStatusNotification.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_HUDWidget.cpp_Functions
void UTINV_HUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UTINV_InventoryComponent* InventoryComponent = UTINV_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	if (IsValid(InventoryComponent))
	{
		// Do stuff
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/

