// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Types/Inv_EnumTypes.h"
#include "Types/Inv_StructTypes.h"
#include "StructUtils/InstancedStruct.h"
#include "GameplayTagContainer.h"
#include "Types/Inv_MetaTypes.h"
#include "Inv_ItemManifest.generated.h"
/*-------------------------------------------------------------------------*/



// The Item Manifest contains all of the necessary data for creating
// a new Inventory Item.



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UInv_InventoryItem;
class UInv_ItemDataAsset;
class UInv_CompositeBase;
class UInv_ItemComponent;
struct FInv_ItemDefinition;
struct FInv_ItemFragment;

USTRUCT(BlueprintType)
struct INVENTORY_API FInv_ItemManifest
{
	GENERATED_BODY()

	/*-------------------------------------------------------------------------*/
	// The Philosophy for the Item Manifest
	// Contains an ID and Meta, absolutely no implicit data.
	/*-------------------------------------------------------------------------*/

public:
	FName GetItemID() const { return ID; }
	template<typename T>
		T* FindMetaData()
		{
			for (TInstancedStruct<FInv_ItemMeta>& Meta : MetaData)
			{
				if (T* TypedMeta = Meta.GetMutablePtr<T>())
				{
					return TypedMeta;
				}
			}
			return nullptr;
		}
	
	// void GenerateRequiredMetaData(); // <- Must perform a check against

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FName ID;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<TInstancedStruct<FInv_ItemMeta>> MetaData;
	
public:
	TArray<TInstancedStruct<FInv_ItemFragment>>& GetFragmentsMutable() { return DisplayFragments; }
	
	// Getters for Equipped Item Payload
	FText GetItemName() const { return ItemName; }
	FText GetItemDescription() const { return ItemDescription; }
	EInv_ItemStar GetItemStars() const { return ItemStars; }
	TArray<FInv_ItemAttributePair> GetItemAttributes() const { return ItemAttributesContainer; }
	TArray<FInv_ItemAbilityPair> GetItemAbilities() const { return ItemAbilitiesContainer; }

	UInv_InventoryItem* Manifest(UObject* NewOuter, UInv_ItemComponent* OwningComponent);
	EInv_ItemCategory GetItemCategory() const { return ItemCategory; }
	EInv_ItemRarity GetItemRarity() const { return ItemRarity; }
	EInv_ItemSpecialType GetItemSpecialType() const { return ItemSpecialType; }
	EInv_ItemEnhancement GetItemEnhancement() const { return ItemEnhancement; }
	int32 GetItemSellValue() const { return SellValue; }
	FGameplayTag GetItemType() const { return ItemType; }
	int32 GetItemAttributeValue(FGameplayTag AttributeTag) const;
	
	// Automatic Display Builder
	void ConstructManifestDisplayFragments();
	void EmptyManifestDisplayFragments();
	void AddExtraManifestDisplayFragments();
	void RefreshManifestDisplayFragments();

	// Adds each of the following to array of Display Fragments
	void TryMakeItemNameDisplayFragment();			// Text Fragment
	void TryMakeItemDescriptionDisplayFragment();	// Text Fragment
	void TryMakeItemStarsDisplayFragment();			// Enum Fragment
	void TryMakeItemTypeRarityDisplayFragment();	// Text Fragment
	void TryMakeItemSellValueDisplayFragment();		// Labeled Number Fragment
	void TryMakeItemIconDisplayFragment();			// Image Fragment
	void TryMakeItemGridDisplayFragment();			// Grid Fragment

	FVector2D GetIconDimensionsFromRatio(FIntPoint GridSize);
	
	// Create a reference back to the Owning Manifest for the Fragments.
	void ForEachFragmentSetOwningManifest(FInv_ItemManifest* InManifest); // Sets all Fragment Owning Manifest
	
	void AssimilateInventoryFragments(UInv_CompositeBase* Composite) const;

	template<typename T> requires std::derived_from<T, FInv_ItemFragment>
	const T* GetFragmentOfTypeWithTag(const FGameplayTag& FragmentTag) const;

	template<typename T> requires std::derived_from<T, FInv_ItemFragment>
	const T* GetFragmentOfType() const;

	template<typename T> requires std::derived_from<T, FInv_ItemFragment>
	T* GetFragmentOfTypeMutable();

	template<typename T> requires std::derived_from<T, FInv_ItemFragment>
	TArray<const T*> GetAllFragmentsOfType() const;
	
	// Item Manifest can Spawn PickUp Actor:
	void SpawnPickupActor(const UObject* WorldContextObject, const FVector& SpawnLocation, const FRotator& SpawnRotation);
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FText ItemID = FText();
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 EntryIndex = INDEX_NONE;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TObjectPtr<UTexture2D> ItemIcon{nullptr};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FIntPoint ItemSize{1, 1};	
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FText ItemName= FText();

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FText ItemDescription= FText();

	UPROPERTY(EditAnywhere, Category = "Inventory")
	EInv_ItemStar ItemStars{EInv_ItemStar::NoStars};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	EInv_ItemSpecialType ItemSpecialType{EInv_ItemSpecialType::None};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	EInv_ItemEnhancement ItemEnhancement{EInv_ItemEnhancement::None};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FInv_ItemAttributePair> ItemAttributesContainer;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FInv_ItemAbilityPair> ItemAbilitiesContainer;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	EInv_ItemRarity ItemRarity{EInv_ItemRarity::Common};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	EInv_ItemCategory ItemCategory{EInv_ItemCategory::None};

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Categories="TOTUItems"))
	FGameplayTag ItemType;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 SellValue = 0;

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FInv_ItemFragment>> ExtraFragments;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<AActor> PickupActorClass;

	UPROPERTY()
	TArray<TInstancedStruct<FInv_ItemFragment>> DisplayFragments;
	
	FInv_ItemDefinition GetItemDefinition(FName ItemID);
};
/*-------------------------------------------------------------------------*/

template<typename T> requires std::derived_from<T, FInv_ItemFragment>
const T* FInv_ItemManifest::GetFragmentOfTypeWithTag(const FGameplayTag& FragmentTag) const
{
	for (const TInstancedStruct<FInv_ItemFragment>& Fragment : DisplayFragments)
	{
		if (const T* FragmentPtr = Fragment.GetPtr<T>())
		{
			if (!FragmentPtr->GetFragmentTag().MatchesTagExact(FragmentTag)) continue;
			return FragmentPtr;
		}
	}
	return nullptr;
}

template <typename T> requires std::derived_from<T, FInv_ItemFragment>
const T* FInv_ItemManifest::GetFragmentOfType() const
{
	for (const TInstancedStruct<FInv_ItemFragment>& Fragment : DisplayFragments)
	{
		if (const T* FragmentPtr = Fragment.GetPtr<T>())
		{
			return FragmentPtr;
		}
	}
	return nullptr;
}

template <typename T> requires std::derived_from<T, FInv_ItemFragment>
T* FInv_ItemManifest::GetFragmentOfTypeMutable()
{
	for (TInstancedStruct<FInv_ItemFragment>& Fragment : DisplayFragments)
	{
		if (T* FragmentPtr = Fragment.GetMutablePtr<T>())
		{
			return FragmentPtr;
		}
	}
	return nullptr;
}

template <typename T> requires std::derived_from<T, FInv_ItemFragment>
TArray<const T*> FInv_ItemManifest::GetAllFragmentsOfType() const
{
	TArray<const T*> Result;
	for (const TInstancedStruct<FInv_ItemFragment>& Fragment : DisplayFragments)
	{
		if (const T* FragmentPtr = Fragment.GetPtr<T>())
		{
			Result.Add(FragmentPtr);
		}
	}
	return Result;
}
