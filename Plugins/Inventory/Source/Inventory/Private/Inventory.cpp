// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Inventory.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Definitions	                                                       */
/*-------------------------------------------------------------------------*/
#define LOCTEXT_NAMESPACE "FInventoryModule"
DEFINE_LOG_CATEGORY(LogInventory);	
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inventory.cpp_Functions
void FInventoryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

}

void FInventoryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FInventoryModule, Inventory)
#pragma endregion
/*-------------------------------------------------------------------------*/