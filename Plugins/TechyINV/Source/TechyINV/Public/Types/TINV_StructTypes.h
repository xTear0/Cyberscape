#pragma once
#include "TINV_EnumTypes.h"
#include "TINV_StructTypes.generated.h"


class UImage;
enum class ETINV_ItemTier : uint8;
enum class ETINV_WeaponDamageType : uint8;
enum class ETINV_WeaponFireType : uint8;
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

USTRUCT(BlueprintType)
struct FTINV_ItemDataDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	FText ItemName{};

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TObjectPtr<UImage> ItemIcon{nullptr};

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TSubclassOf<AActor> ItemRespawnClass{nullptr};

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	ETINV_ItemTier ItemTier{ETINV_ItemTier::Scrap};

	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	int32 ItemSellValue{0};
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