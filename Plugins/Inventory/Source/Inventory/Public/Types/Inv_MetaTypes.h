// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "Inv_EnumTypes.h"
#include "Inv_StructTypes.h"
#include "Inv_MetaTypes.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*  Declarations										                   */
/*-------------------------------------------------------------------------*/
USTRUCT(BlueprintType)
struct FInv_ItemMeta // Base Struct
{
	GENERATED_BODY()
	FInv_ItemMeta() = default;

public: 
	void SetItemID(const FName InItemID) { ItemID = InItemID; }
	FName GetItemID() const { return ItemID; }

protected:
	UPROPERTY()
	FName ItemID;
};

USTRUCT(BlueprintType)
struct FInv_ItemMint : public FInv_ItemMeta
{
	GENERATED_BODY()
	/*-------------------------------------------------------------------------------*/
	/*  Meta-Usage Information														 */
	/*-------------------------------------------------------------------------------*/
	 /* This meta-type contains the edition the item, as well as the timestamp it was
	 created, and who got it. I.e. "Edition #13, 10/24/2025 @ 10:30:01, xTear" */
	/*-------------------------------------------------------------------------------*/
public:
	void SetTimeCreated(FDateTime InTime) { TimeCreated = InTime; }
	FDateTime GetTimeCreated() const { return TimeCreated; }
	FString GetTimeAsFormattedString() const { return TimeCreated.ToString(TEXT("%m/%d/%Y @ %H:%M:%S")); }
	FString GetMintAsFormattedString() const 
	{ 
		FString TimeString = TimeCreated.ToString(TEXT("%m/%d/%Y @ %H:%M:%S"));
		return FString::Printf(TEXT("%s, %s"), *TimeString, *SourcePlayer);
	}
	
private:
	FDateTime TimeCreated;
	FString SourcePlayer;
};

USTRUCT(BlueprintType)
struct FInv_ItemOrigin : public FInv_ItemMeta
{
	GENERATED_BODY()
	/*-------------------------------------------------------------------------------*/
	/*  Meta-Usage Information														 */
	/*-------------------------------------------------------------------------------*/
	/* This meta-type contains information for how the item was created. Was the item
	 * awarded from an event? Given by a specific admin as compensation? Even contains
	 * room for extra information as embedded text. I.e. "Dungeon Loot" or
	 * "Compensation from wipe, Added by [Admin] xTear, Notes: See bug report #233" */
	/*-------------------------------------------------------------------------------*/
public:
	void SetItemOrigin(EInv_ItemOriginSource Origin) { ItemOrigin = Origin; }
	void SetItemOriginNotes(FString OriginNotes) { ItemOriginNotes = OriginNotes; } // Highly irregular, but if you want, it's here. Required for administrative items.
	EInv_ItemOriginSource GetItemOrigin() const { return ItemOrigin; }
	
private:
	EInv_ItemOriginSource ItemOrigin = EInv_ItemOriginSource::Unknown; // Leaving this unset will cause an automatic wipe.
	FString ItemOriginNotes;
	
};

USTRUCT(BlueprintType)
struct FInv_ItemMetaData : public FInv_ItemMeta
{
	GENERATED_BODY()
	/*-------------------------------------------------------------------------------*/
	/*  Meta-Usage Information														 */
	/*-------------------------------------------------------------------------------*/
	/* A generated struct of this MetaType will contain all the data
	associated with having this item in the world. That includes:
		1. Item Stars
		2. Item Special Type
		3. Item Enhancement
		4. Item Secondary Attributes
		5. Item Upgrade Level
	*/
	/*-------------------------------------------------------------------------------*/
public:
	// TODO: Getters, Setters, Initialize item information from LootTable, etc.
	EInv_ItemStar GetItemStars() const { return ItemStars; }
	EInv_ItemSpecialType GetSpecialType() const { return ItemSpecialType; }
	EInv_ItemEnhancement GetEnhancement() const { return ItemEnhancement; }
	TMap<int, FInv_SecondaryAttributeKey> GetSecondaryAttributes() const { return SecondaryAttributes; }
	
	void GenerateItemData(/* Include a loot table */);
	
	
private:

	// Helpers
	void GenerateItemStars();	
	void GenerateItemSpecial();
	void GenerateItemEnhancement();
	void GenerateSecondaryAttributes();
	
	EInv_ItemStar ItemStars = EInv_ItemStar::NoStars;
	EInv_ItemSpecialType ItemSpecialType = EInv_ItemSpecialType::None;
	EInv_ItemEnhancement ItemEnhancement = EInv_ItemEnhancement::None;

	TMap<int, FInv_SecondaryAttributeKey> SecondaryAttributes;
	
};
/*-------------------------------------------------------------------------*/