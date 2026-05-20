// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Fragments/Inv_ItemFragment.h"
#include "StructUtils/InstancedStruct.h"
#include "Types/Inv_EnumTypes.h"
#include "Types/Inv_StructTypes.h"
#include "Inv_ItemDataAsset.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
USTRUCT(BlueprintType)
struct FInv_ItemEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TObjectPtr<UTexture2D> ItemIcon{nullptr};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FIntPoint ItemSize{1, 1};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FText ItemName= FText::GetEmpty();;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FText ItemDescription= FText::GetEmpty();;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	EInv_ItemStar ItemStars{EInv_ItemStar::NoStars};
	
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
};
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemDataAsset.h_Class
UCLASS()
class INVENTORY_API UInv_ItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FInv_ItemEntry> Entries;
};
#pragma endregion
/*-------------------------------------------------------------------------*/