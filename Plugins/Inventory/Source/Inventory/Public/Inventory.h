// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "Modules/ModuleManager.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Delcarations	                                                       */
/*-------------------------------------------------------------------------*/
DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Log, All);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inventory.h_Class
class FInventoryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
#pragma endregion
/*-------------------------------------------------------------------------*/