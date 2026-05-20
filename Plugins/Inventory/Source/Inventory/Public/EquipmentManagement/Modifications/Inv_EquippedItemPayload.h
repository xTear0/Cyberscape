// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Inv_EquippedItemPayload.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
USTRUCT()
struct FInv_EquippedItemPayload
{
	GENERATED_BODY()
	// This struct is designed to be sent to the Attribute Modification Handler. It will be responsible for several things,
	
	// 1. It will keep track of the item's name and rarity color.
	FName ItemName;
	FLinearColor ItemColor{FLinearColor::FromSRGBColor(FColor::FromHex("856758FF"))};
	
	// 2. It will contain an array of the attribute changes this item is responsible for.
	TArray<FInv_ItemAttributePair> ItemAttributesContainer;
	
	// 3. It will contain an array of the ability changes this item is responsible for, as well as their types and effects.
	TArray<FInv_ItemAbilityPair> ItemAbilitiesContainer;
	
	// 4. It will contain an ID for removal later.
	FGuid PayloadID;
	
	/*----------------------------------------------------------------*/
	FInv_EquippedItemPayload() : PayloadID(FGuid::NewGuid()) {}
	/*----------------------------------------------------------------*/

	static FInv_EquippedItemPayload Create(
		const FName& InItemName = NAME_None,
		const FLinearColor& InItemColor = FLinearColor::FromSRGBColor(FColor::FromHex("856758FF")),
		const TArray<FInv_ItemAttributePair>& InItemAttributesContainer = TArray<FInv_ItemAttributePair>(),
		const TArray<FInv_ItemAbilityPair>& InItemAbilitiesContainer = TArray<FInv_ItemAbilityPair>())
	{
		FInv_EquippedItemPayload Payload; 
		Payload.ItemName = InItemName;
		Payload.ItemColor = InItemColor;
		Payload.ItemAttributesContainer = InItemAttributesContainer;
		Payload.ItemAbilitiesContainer = InItemAbilitiesContainer;
		return Payload;
	}
};
/*-------------------------------------------------------------------------*/