// Copyright xTear Studios
/*-------------------------------------------------------------------------*/

#include "Widgets/Inventory/Spatial/TINV_SpatialInventory.h"

#include "Items/Components/TINV_ItemComponent.h"
#include "Widgets/Inventory/Spatial/TINV_InventoryGrid.h"

/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_SpatialInventory.cpp_Functions
FTINV_SlotAvailabilityResult UTINV_SpatialInventory::HasRoomForItem(UTINV_ItemComponent* ItemComponent) const
{
	return InventoryGrid->HasRoomForItem(ItemComponent);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
