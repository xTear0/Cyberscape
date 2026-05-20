// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "Inv_EnumTypes.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*  Declarations										                   */
/*-------------------------------------------------------------------------*/
class UInv_InventoryItem;

UENUM(BlueprintType)
enum class EInv_AttributeScalarPower : uint8
{
	Low,
	Med,
	High,
	Max
};

UENUM(BlueprintType)
enum class EInv_ItemOriginSource : uint8
{
	// Core gameplay loops
	CombatActivity,     // Dungeons, bosses, raids, enemies
	Exploration,        // Chests, secrets, world discovery
	Progression,        // Quests, campaign, achievements

	// Economy
	Crafted,            // Player-created or upgraded
	Purchased,          // Store, bundles, premium tracks

	// Event / System
	Trophy,				// Exceptional event standing
	EventReward,        // Seasonal or limited-time events
	Administrative,     // Debug spawn, support grants

	Unknown				// Fallback
};

UENUM(BlueprintType)
enum class EInv_SecondaryAttributeRules : uint8
{
	// Priority attributes (duplicated in pool)
	PRIORITY_ATTACK_DEFAULT,
	PRIORITY_ATTACK_FIRE,
	PRIORITY_ATTACK_ICE,
	PRIORITY_ATTACK_COLD_FIRE,
	PRIORITY_ATTACK_LIGHTNING,
	PRIORITY_ATTACK_VOID,
	PRIORITY_ATTACK_MULTIPLIERS,  // All *_Mult variants
	PRIORITY_ATTACK_CRITICAL,     // Crit damage/rate
    
	PRIORITY_RESIST_DEFAULT,
	PRIORITY_RESIST_FIRE,
	PRIORITY_RESIST_ICE,
	PRIORITY_RESIST_COLD_FIRE,
	PRIORITY_RESIST_MULTIPLIERS,
    
	PRIORITY_ARMOR,               // All armor types
	PRIORITY_HEALTH,              // Health and Recovery
	PRIORITY_AGILITY,             // Agility, Energy, Evasion
	PRIORITY_SPECIAL,             // All special stats
    
	// Blocked attributes (excluded from pool)
	BLOCKED_ATTACK_DEFAULT,
	BLOCKED_ATTACK_FIRE,
	BLOCKED_ATTACK_ICE,
	BLOCKED_ATTACK_COLD_FIRE,
	BLOCKED_ATTACK_LIGHTNING,
	BLOCKED_ATTACK_VOID,
	BLOCKED_ATTACK_MULTIPLIERS,
	BLOCKED_ATTACK_CRITICAL,
    
	BLOCKED_RESIST_DEFAULT,
	BLOCKED_RESIST_FIRE,
	BLOCKED_RESIST_ICE,
	BLOCKED_RESIST_COLD_FIRE,
	BLOCKED_RESIST_MULTIPLIERS,
    
	BLOCKED_ARMOR,
	BLOCKED_HEALTH,
	BLOCKED_AGILITY,
	BLOCKED_SPECIAL
};

UENUM(BlueprintType)
enum class EInv_ItemCategory : uint8
{
	Equippable,
	Consumable,
	Craftable,
	None
};

UENUM(BlueprintType)
enum class EInv_ItemRarity : uint8
{
	Supreme,
	Mythical,
	Legendary,
	Epic,
	Rare,
	Uncommon,
	Common
};

UENUM(BlueprintType)
enum class EInv_ItemSpecialType : uint8
{
	Prismatic,
	Ethereal,
	Netherborn,
	Eldritch,
	Runescribed,
	None
};

UENUM(BlueprintType)
enum class EInv_ItemEnhancement : uint8
{
	Prime,
	Enchanted,
	Corrupted,
	Cursed,
	None
};

UENUM(BlueprintType)
enum class EInv_ItemStar : uint8
{
	NoStars,
	OneStar,
	TwoStar,
	ThreeStar,
	FourStar,
	FiveStar,
	SixStar,
	SevenStar
};

UENUM(BlueprintType)
enum class EInv_Colors : uint8
{
	// Rarity Colors
	SupremeRed			UMETA(DisplayName = "Supreme Red"),
	MythicalGold		UMETA(DisplayName = "Mythical Gold"),
	LegendaryYellow		UMETA(DisplayName = "Legendary Yellow"),
	EpicPurple			UMETA(DisplayName = "Epic Purple"),
	RareBlue			UMETA(DisplayName = "Rare Blue"),
	UncommonGreen		UMETA(DisplayName = "Uncommon Green"),
	CommonGray			UMETA(DisplayName = "Common Gray"),

	// Attribute Colors
	StrengthYellow			UMETA(DisplayName = "Strength Bright Yellow"),
		SubAttributeYellow	UMETA(DisplayName = "Sub-Attribute Yellow"),
	IntelligenceBlue		UMETA(DisplayName = "Intelligence Bright Blue"),
		SubAttributeBlue	UMETA(DisplayName = "Sub-Attribute Blue"),
	FortitudeGreen			UMETA(DisplayName = "Fortitude Bright Green"),
		SubAttributeGreen	UMETA(DisplayName = "Sub-Attribute Green"),
	VitalityRed				UMETA(DisplayName = "Vitality Bright Red"),
		SubAttributeRed		UMETA(DisplayName = "Sub-Attribute Red"),
	
	// Damage Colors
	DamageTypeStatic		UMETA(DisplayName = "Damage Type Static"),
	DamageTypePhyiscal		UMETA(DisplayName = "DamageType - Physical Yellow"),
	DamageTypePoison		UMETA(DisplayName = "DamageType - Poison Green"),
	DamageTypeIce			UMETA(DisplayName = "DamageType - Ice Blue"),
	DamageTypeFire			UMETA(DisplayName = "DamageType - Fire Red"),
	DamageTypeLight			UMETA(DisplayName = "DamageType - Light White"),
	DamageTypeShadow		UMETA(DisplayName = "DamageType - Shadow Black"),
	
	// Colors Used By Text in UIs
	UIWhite				UMETA(DisplayName = "Basic UI White"),
	UITan				UMETA(DisplayName = "Basic UI Tan"),
	UIShadow			UMETA(DisplayName = "Basic UI Shadow")
};

UENUM(BlueprintType)
enum class EInv_AttributeEntry : uint8
{
	// Damage Base		(Increases outgoing damage by a flat value)
	Attack_Default,		// Deals normal damage.
	Attack_Fire,		// Deals fire damage.
	Attack_Ice,			// Deals ice damage.
	Attack_Cold_Fire,	// Deals cold fire damage.
	Attack_Lightning,	// Deals lightning damage.
	Attack_Void,		// Deals void damage.
	
	// Damage Mult		(Increases specific damage by an add-mult value)
	Attack_Default_Mult,
	Attack_Fire_Mult,
	Attack_Ice_Mult,
	Attack_Cold_Fire_Mult,
	Attack_Lightning_Mult,
	Attack_Void_Mult,

	// Damage Extra	(Further modifies damage) // No multiplicative values for this type.
	Attack_Crit_Damage,	// If a hit is a critical hit, additive multiplier from this.
	Attack_Crit_Rate,	// Increases the chance of a hit being critical.
	
	// Armor		(Decrease received damage) // No multiplicative values for this type.
	Armor_Light,		// Weak against all attacks, no agility penalty.
	Armor_Heavy,		// Strong against all attacks, agility penalty.
	Armor_Spectral,		// Weak against regular attacks, strong against all others.

	// Resist Base	(Reduces incoming damage)
	Resist_Default,		// Resists normal damage.
	Resist_Fire,		// Resists fire damage.
	Resist_Ice,			// Resists ice damage.
	Resist_Cold_Fire,	// Resists cold fire damage.

	// Resist Mult	(Reduces specific incoming damage by an add-mult value)
	Resist_Default_Mult,
	Resist_Fire_Mult,
	Resist_Ice_Mult,
	Resist_Cold_Fire_Mult,
	
	// Health Base	(Increase HP etc.)
	Health,				// Increases health pool.
	Recovery,			// Increases regen and knockdown recovery speed.

	// Health Mult	(Increase HP etc. by an add-mult value)
	Health_Mult,
	Recovery_Mult,
	
	// Agility		(Increases movement speed etc.) // No multiplicative values for this type.
	Agility,			// Increases movement speed.
	Energy,				// Reduces ability cost and cooldowns.
	Evasion,			// Chance to change any hit into a weak hit (cant crit, half dmg).

	// Special		(Rare attributes that increase special stats) // No multiplicative values for this type.
	Special_Supremacy,	// Increases all non-special stats by a very small percentage.
	Special_Treasure,	// Increases drop chances for treasure.
	Special_Luck,		// Improves the odds of getting rare items.
	Special_XP			// Increases the amount of received XP.
};

UENUM(BlueprintType)
enum class EInv_ItemAttribute : uint8
{
	None 				UMETA(DisplayName = "None"),
	
	Strength  			UMETA(DisplayName = "Strength"),
	Intelligence 		UMETA(DisplayName = "Intelligence"),
	Fortitude 			UMETA(DisplayName = "Fortitude"),
	Vitality 			UMETA(DisplayName = "Vitality"),

	Dexterity  			UMETA(DisplayName = "Dexterity"),
	MaxMana				UMETA(DisplayName = "Maximum Mana"),
	ManaRegen			UMETA(DisplayName = "Mana Regeneration"),
	MaxHealth			UMETA(DisplayName = "Maximum Health"),
	HealthRegen			UMETA(DisplayName = "Health Regeneration"),
	CritChance			UMETA(DisplayName = "Crit Chance"),
	CritDamage			UMETA(DisplayName = "Crit Damage"),
	IgnoreDEF			UMETA(DisplayName = "Ignore Resistance"),			
	
	DamagePhysical		UMETA(DisplayName = "Physical Damage"),
	DamagePoison 		UMETA(DisplayName = "Poison Damage"),
	DamageIce 			UMETA(DisplayName = "Ice Damage"),
	DamageFire 			UMETA(DisplayName = "Fire Damage"),
	DamageLight 		UMETA(DisplayName = "Light Damage"),
	DamageShadow 		UMETA(DisplayName = "Shadow Damage"),

	ResistanceGlobal  		UMETA(DisplayName = "Global Resistance"),
	ResistancePhysical  	UMETA(DisplayName = "Physical Resistance"),
	ResistancePoison  		UMETA(DisplayName = "Poison Resistance"),
	ResistanceIce 			UMETA(DisplayName = "Ice Resistance"),
	ResistanceFire 			UMETA(DisplayName = "Fire Resistance"),
	ResistanceLight 		UMETA(DisplayName = "Light Resistance"),
	ResistanceShadow 		UMETA(DisplayName = "Shadow Resistance"),
	MAX UMETA(Hidden)
};

USTRUCT()
struct FInv_SlotAvailability
{
	GENERATED_BODY()

	FInv_SlotAvailability() {}
	FInv_SlotAvailability(int32 ItemIndex, int32 Room, bool bHasItem) : Index(ItemIndex), AmountToFill(Room), bItemAtIndex(bHasItem) {}
	
	int32 Index{INDEX_NONE};
	int32 AmountToFill{0};
	bool bItemAtIndex{false};
};

USTRUCT()
struct FInv_SlotAvailabilityResult
{
	GENERATED_BODY()

	FInv_SlotAvailabilityResult() {}

	TWeakObjectPtr<UInv_InventoryItem> Item;
	int32 TotalRoomToFill{0};
	int32 Remainder{0};
	bool bStackable{false};
	TArray<FInv_SlotAvailability> SlotAvailabilities;
	
};

UENUM(BlueprintType)
enum class EInv_TileQuadrant :  uint8
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	None
};

USTRUCT(BlueprintType)
struct FInv_TileParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FIntPoint TileCoordinates{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 TileIndex{INDEX_NONE};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	EInv_TileQuadrant TileQuadrant{EInv_TileQuadrant::None};
};

inline bool operator==(const FInv_TileParameters& A, const  FInv_TileParameters& B)
{
	return A.TileCoordinates == B.TileCoordinates &&
		A.TileIndex == B.TileIndex &&
			A.TileQuadrant == B.TileQuadrant;
}

USTRUCT()
struct FInv_SpaceQueryResult
{
	GENERATED_BODY()

	// True if the space queried has no items in it.
	bool bHasSpace{false};

	// Valid if there is a single item we can swap with.
	TWeakObjectPtr<UInv_InventoryItem> ValidItem = nullptr;

	// Upper left index of the valid item, if there is one.
	int32 UpperLeftIndex{INDEX_NONE};
};
/*-------------------------------------------------------------------------*/