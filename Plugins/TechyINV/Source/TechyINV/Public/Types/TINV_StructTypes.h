#pragma once
#include "TINV_StructTypes.generated.h"


class UTINV_InventoryItem;

USTRUCT()
struct FTINV_SlotAvailability
{
	GENERATED_BODY()

	FTINV_SlotAvailability() {}
	FTINV_SlotAvailability(int32 ItemIndex, int32 Room, bool bHasItem) : Index(ItemIndex), AmountToFill(Room), bItemAtIndex(bHasItem) {}
	
	int32 Index{INDEX_NONE};
	int32 AmountToFill{0};
	bool bItemAtIndex{false}; 
};


USTRUCT()
struct FTINV_SlotAvailabilityResult
{
	GENERATED_BODY()

	FTINV_SlotAvailabilityResult() {}

	TWeakObjectPtr<UTINV_InventoryItem> Item;
	int32 TotalRoomToFill{0};
	int32 Remainder{0};
	bool bStackable{false};
	
	TArray<FTINV_SlotAvailability> SlotAvailabilities;
};