#pragma once
#include "TINV_EnumTypes.h"
#include "TINV_StructTypes.generated.h"


class UImage;
enum class ETINV_ItemTier : uint8;
enum class ETINV_WeaponDamageType : uint8;
enum class ETINV_WeaponFireType : uint8;
class UTINV_InventoryItem;
class UTINV_InventoryGrid;


USTRUCT()
struct FTINV_SlotAvailability
{
	GENERATED_BODY()

	FTINV_SlotAvailability() {}
	FTINV_SlotAvailability(int32 ItemIndex, int32 Room, bool bHasItem) : Index(ItemIndex), AmountToFill(Room), bItemAtIndex(bHasItem) {}
	
	int32 Index{INDEX_NONE};
	int32 AmountToFill{0};
	bool bItemAtIndex{false};

	// Which grid this slot belongs to. Each grid only applies its own entries.
	TWeakObjectPtr<const UTINV_InventoryGrid> Grid;
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
	
	// Which grid this slot belongs to. Each grid only applies its own entries.
	TWeakObjectPtr<const UTINV_InventoryGrid> Grid;
};

USTRUCT(BlueprintType)
struct FTINV_ItemDataDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TECHY|Inventory")
	FText ItemName{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TECHY|Inventory")
	FText ItemDescription{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TECHY|Inventory")
	TObjectPtr<UTexture2D> ItemIcon{nullptr};

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TSubclassOf<AActor> ItemRespawnClass{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TECHY|Inventory")
	ETINV_ItemTier ItemTier{ETINV_ItemTier::Scrap};

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	int32 ItemSellValue{0};

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	int32 MaxStackSize{0};
};

USTRUCT(BlueprintType)
struct FTINV_WeaponDefaults
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	int32 WeaponBaseMaxAmmo{30};

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	float WeaponBaseFireRate{5.f};

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TArray<ETINV_WeaponFireType> WeaponFireTypes;

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	float WeaponReloadTime{3.f};

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	float WeaponBaseDamage{8.f};

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	ETINV_WeaponDamageType BaseDamageType{ETINV_WeaponDamageType::Kinetic};
};

USTRUCT(BlueprintType)
struct FTINV_ContainerDefaults
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory", meta = (ClampMin = "0", ClampMax = "3", UIMin = "0", UIMax = "3"))
	int32 Rating{0};
};

USTRUCT(BlueprintType)
struct FTINV_ItemWeaponDataDefinition : public FTINV_ItemDataDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	FTINV_WeaponDefaults WeaponDefaults;
};

USTRUCT(BlueprintType)
struct FTINV_ItemAttachmentDataDefinition : public FTINV_ItemDataDefinition
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FTINV_ItemMaterialDataDefinition : public FTINV_ItemDataDefinition
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FTINV_ItemStrongboxDataDefinition : public FTINV_ItemDataDefinition
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	FTINV_ContainerDefaults StrongboxDefaults;
};

USTRUCT(BlueprintType)
struct FTINV_SpaceQueryResult
{
	GENERATED_BODY()

	// True if the space queried has no items in it.
	bool bHasSpace{false};

	// Valid if there is a single item we can swap with.
	TWeakObjectPtr<UTINV_InventoryItem> ValidItem = nullptr;

	// Index of the valid item, if there is one.
	int32 ItemIndex{INDEX_NONE};
};