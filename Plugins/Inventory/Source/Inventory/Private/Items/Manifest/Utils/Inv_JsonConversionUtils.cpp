// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Items/Manifest/Utils/Inv_JsonConversionUtils.h"
#include "Items/Inv_ItemDataAsset.h"
/*-------------------------------------------------------------------------*/


FInv_ItemDefinition UInv_JsonConversionUtils::GetItemDefinition(FName ItemID)
{
	FString FilePath = TEXT("Data/ItemConfig.json");
	bool bAbsolutePath = false;
	/*bool bSuccess;
	bool bFound;*/
	FString ErrorMessage;
	
	/*// Load items from the file...
	FEasyJsonObjectV2 JsonObject = UEasyJsonParserV2BlueprintLibrary::LoadJsonFromFile(FilePath, bAbsolutePath, bSuccess, ErrorMessage);
	if (!bSuccess) UE_LOG(LogTemp, Error, TEXT("Failed to load JSON: %s"), *ErrorMessage);
	
	// Get an Items array...
	TArray<FEasyJsonObjectV2> ItemsArray = JsonObject.ReadObjects("Items", bFound);
	if (!bFound) UE_LOG(LogTemp, Error, TEXT("Failed to load Items."));
	
	// Iterate over the array...
	for (FEasyJsonObjectV2& ItemObj : ItemsArray)
	{
		if (FName(*ItemObj.ReadString(TEXT("ID"))) == ItemID)
		{
			FInv_ItemDefinition ItemDef;
			ItemDef.ID = FName(*ItemObj.ReadString(TEXT("ID")));
			ItemDef.IconID = FName(*ItemObj.ReadString(TEXT("IconID")));
			ItemDef.ItemName = ItemObj.ReadString(TEXT("Name"));
			ItemDef.ItemDescription = ItemObj.ReadString(TEXT("Description"));
			ItemDef.ItemRarity = UInv_JsonConversionUtils::GetRarityEnumFromString(ItemObj.ReadString(TEXT("Rarity")));
			ItemDef.SellValueBase = ItemObj.ReadInt(TEXT("SellValueBase"));
			ItemDef.MaxStackSize = ItemObj.ReadInt(TEXT("MaxStackSize"));
			ItemDef.Durability = ItemObj.ReadInt(TEXT("Durability"));
			//ItemDef.ItemType = UInv_JsonConversionUtils::GetGameplayTagFromString(ItemObj.ReadString(TEXT("ItemType")));

			return ItemDef; // Return result.
		}
	}*/
	UE_LOG(LogTemp, Error, TEXT("Failed to find the definition for Item: %s."), *ItemID.ToString());
	FInv_ItemDefinition ItemDef;
	return ItemDef; 
}

EInv_ItemRarity UInv_JsonConversionUtils::GetRarityEnumFromString(FString RarityString)
{
	if (RarityString == "Supreme")
	{
		return EInv_ItemRarity::Supreme;
	}
	else if (RarityString == "Mythical")
	{
		return EInv_ItemRarity::Mythical;
	}
	else if (RarityString == "Legendary")
	{
		return EInv_ItemRarity::Legendary;
	}
	else if (RarityString == "Epic")
	{
		return EInv_ItemRarity::Epic;
	}
	else if (RarityString == "Rare")
	{
		return EInv_ItemRarity::Rare;
	}
	else if (RarityString == "Uncommon")
	{
		return EInv_ItemRarity::Uncommon;
	}
	else if (RarityString == "Common")
	{
		return EInv_ItemRarity::Common;
	}
	return EInv_ItemRarity::Common;
}

FGameplayTag UInv_JsonConversionUtils::GetGameplayTagFromString(FString GameplayTagString)
{
	return FGameplayTag::RequestGameplayTag(FName(*GameplayTagString));
}
