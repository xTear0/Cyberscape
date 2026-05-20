// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Utils/Inv_WidgetUtils.h"
#include "GameplayTags.h"
#include "GameplayTagContainer.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Types/Inv_EnumTypes.h"
#include "Widgets/Inventory/SlottedItems/Inv_SlottedItem.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*  Functions                                                              */
/*-------------------------------------------------------------------------*/
#pragma region Inv_WidgetUtils.cpp_Functions
FLinearColor UInv_WidgetUtils::GetColorFromColorEnum(EInv_Colors RequestedColor)
{
	switch (RequestedColor)
	{
		// Rarity Colors
		case EInv_Colors::SupremeRed:         return FLinearColor::FromSRGBColor(FColor::FromHex("FF0006FF"));
		case EInv_Colors::MythicalGold:       return FLinearColor::FromSRGBColor(FColor::FromHex("FF5100FF"));
		case EInv_Colors::LegendaryYellow:    return FLinearColor::FromSRGBColor(FColor::FromHex("FF9900FF"));
		case EInv_Colors::EpicPurple:         return FLinearColor::FromSRGBColor(FColor::FromHex("FF00F5FF"));
		case EInv_Colors::RareBlue:           return FLinearColor::FromSRGBColor(FColor::FromHex("0003D9FF"));
		case EInv_Colors::UncommonGreen:      return FLinearColor::FromSRGBColor(FColor::FromHex("00AE09FF"));
		case EInv_Colors::CommonGray:         return FLinearColor::FromSRGBColor(FColor::FromHex("856758FF"));

		// Attribute Colors
		case EInv_Colors::StrengthYellow:     return FLinearColor::FromSRGBColor(FColor::FromHex("FFBA00FF"));
		case EInv_Colors::SubAttributeYellow: return FLinearColor::FromSRGBColor(FColor::FromHex("FF8100FF"));
		case EInv_Colors::IntelligenceBlue:   return FLinearColor::FromSRGBColor(FColor::FromHex("0AB9FFFF"));
		case EInv_Colors::SubAttributeBlue:   return FLinearColor::FromSRGBColor(FColor::FromHex("004B92FF"));
		case EInv_Colors::FortitudeGreen:     return FLinearColor::FromSRGBColor(FColor::FromHex("00FF15FF"));
		case EInv_Colors::SubAttributeGreen:  return FLinearColor::FromSRGBColor(FColor::FromHex("004506FF"));
		case EInv_Colors::VitalityRed:        return FLinearColor::FromSRGBColor(FColor::FromHex("FF0007FF"));
		case EInv_Colors::SubAttributeRed:    return FLinearColor::FromSRGBColor(FColor::FromHex("590002FF"));

		// Resistance Colors
		case EInv_Colors::DamageTypeStatic:   return FLinearColor::White;
		case EInv_Colors::DamageTypePhyiscal: return FLinearColor::FromSRGBColor(FColor::FromHex("A78435FF"));
		case EInv_Colors::DamageTypePoison:   return FLinearColor::FromSRGBColor(FColor::FromHex("439557FF"));
		case EInv_Colors::DamageTypeIce:      return FLinearColor::FromSRGBColor(FColor::FromHex("7EFEFFFF"));
		case EInv_Colors::DamageTypeFire:     return FLinearColor::FromSRGBColor(FColor::FromHex("FF3A1CFF"));
		case EInv_Colors::DamageTypeLight:    return FLinearColor::FromSRGBColor(FColor::FromHex("D0CEFFFF"));
		case EInv_Colors::DamageTypeShadow:   return FLinearColor::FromSRGBColor(FColor::FromHex("3A2D6AFF"));

		// UI Text Colors
		case EInv_Colors::UIWhite:            return FLinearColor::FromSRGBColor(FColor::FromHex("FDD697FF"));
		case EInv_Colors::UITan:              return FLinearColor::FromSRGBColor(FColor::FromHex("856758FF"));
		case EInv_Colors::UIShadow:           return FLinearColor::FromSRGBColor(FColor::FromHex("020101FF"));

		default:                              return FLinearColor::Gray;
	}
}

FLinearColor UInv_WidgetUtils::GetColorFromRarityEnum(EInv_ItemRarity RequestedRarity)
{
	switch (RequestedRarity)
	{
		case EInv_ItemRarity::Supreme:        return FLinearColor::FromSRGBColor(FColor::FromHex("FF0006FF"));
		case EInv_ItemRarity::Mythical:		  return FLinearColor::FromSRGBColor(FColor::FromHex("FF5100FF"));
		case EInv_ItemRarity::Legendary:	  return FLinearColor::FromSRGBColor(FColor::FromHex("FF9900FF"));
		case EInv_ItemRarity::Epic:	          return FLinearColor::FromSRGBColor(FColor::FromHex("FF00F5FF"));
		case EInv_ItemRarity::Rare:	          return FLinearColor::FromSRGBColor(FColor::FromHex("0003D9FF"));
		case EInv_ItemRarity::Uncommon:	      return FLinearColor::FromSRGBColor(FColor::FromHex("00AE09FF"));
		case EInv_ItemRarity::Common:	      return FLinearColor::FromSRGBColor(FColor::FromHex("856758FF"));

		default:                              return FLinearColor::FromSRGBColor(FColor::FromHex("856758FF"));
	}
}

FLinearColor UInv_WidgetUtils::GetHalfOpacityColorFromRarityEnum(EInv_ItemRarity RequestedRarity)
{
	switch (RequestedRarity)
	{
	case EInv_ItemRarity::Supreme:        return FLinearColor::FromSRGBColor(FColor::FromHex("FF000680"));
	case EInv_ItemRarity::Mythical:		  return FLinearColor::FromSRGBColor(FColor::FromHex("FF510080"));
	case EInv_ItemRarity::Legendary:	  return FLinearColor::FromSRGBColor(FColor::FromHex("FF990080"));
	case EInv_ItemRarity::Epic:	          return FLinearColor::FromSRGBColor(FColor::FromHex("FF00F580"));
	case EInv_ItemRarity::Rare:	          return FLinearColor::FromSRGBColor(FColor::FromHex("0003D980"));
	case EInv_ItemRarity::Uncommon:	      return FLinearColor::FromSRGBColor(FColor::FromHex("00AE0980"));
	case EInv_ItemRarity::Common:	      return FLinearColor::FromSRGBColor(FColor::FromHex("85675880"));

	default:                              return FLinearColor::FromSRGBColor(FColor::FromHex("85675880"));
	}
}

FLinearColor UInv_WidgetUtils::GetColorFromAttributeTag(FGameplayTag RequestedAttributeTag)
{
	  // Primary Attributes
    if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Strength"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("FFBA00FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Intelligence"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("0AB9FFFF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Fortitude"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("00FF15FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Vitality"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("FF0007FF"));

    // Secondary Attributes
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Dexterity"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("004506FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.MaxMana"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("004B92FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.ManaRegen"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("004B92FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.MaxHealth"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("590002FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.HealthRegen"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("590002FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.CritChance"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("FF8100FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.CritDamage"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("FF8100FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.IgnoreDEF"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("FF8100FF"));

    // Damage Types
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Damage.Physical"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("A78435FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Damage.Poison"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("439557FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Damage.Ice"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("7EFEFFFF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Damage.Fire"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("FF3A1CFF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Damage.Light"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("D0CEFFFF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Damage.Shadow"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("3A2D6AFF"));

    // Resistances
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("004506FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Physical"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("A78435FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Poison"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("439557FF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Ice"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("7EFEFFFF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Fire"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("FF3A1CFF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Light"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("D0CEFFFF"));
    else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Shadow"), false)))
        return FLinearColor::FromSRGBColor(FColor::FromHex("3A2D6AFF"));
    else
        return FLinearColor::Gray;
}

FText UInv_WidgetUtils::GetPrefixFromRarityEnum(EInv_ItemRarity RequestedRarity)
{
	switch (RequestedRarity)
	{
	case EInv_ItemRarity::Supreme:        return FText::FromString(TEXT("SUPREME"));
	case EInv_ItemRarity::Mythical:		  return FText::FromString(TEXT("MYTHICAL"));
	case EInv_ItemRarity::Legendary:	  return FText::FromString(TEXT("LEGENDARY"));
	case EInv_ItemRarity::Epic:	          return FText::FromString(TEXT("EPIC"));
	case EInv_ItemRarity::Rare:	          return FText::FromString(TEXT("RARE"));
	case EInv_ItemRarity::Uncommon:	      return FText::FromString(TEXT("UNCOMMON"));
	case EInv_ItemRarity::Common:	      return FText::FromString(TEXT("COMMON"));

	default:                              return FText::FromString(TEXT("NULL"));
	}
}

FText UInv_WidgetUtils::GetAttributeTextLabel(FGameplayTag RequestedAttributeTag)
{
	if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Strength"), false)))
	    return FText::FromString("STR");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Intelligence"), false)))
	    return FText::FromString("INT");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Fortitude"), false)))
	    return FText::FromString("FORT");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Vitality"), false)))
	    return FText::FromString("VIT");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.Dexterity"), false)))
	    return FText::FromString("DEX");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.MaxMana"), false)))
	    return FText::FromString("MAX MANA");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.ManaRegen"), false)))
	    return FText::FromString("MANA REGEN");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.MaxHealth"), false)))
	    return FText::FromString("MAX HP");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.HealthRegen"), false)))
	    return FText::FromString("HP REGEN");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.CritChance"), false)))
	    return FText::FromString("CRIT %");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.CritDamage"), false)))
	    return FText::FromString("CRIT DMG");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.IgnoreDEF"), false)))
	    return FText::FromString("IGNORE RESIST");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Physical"), false)))
	    return FText::FromString("PHYSICAL DMG");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Poison"), false)))
	    return FText::FromString("POISON DMG");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Ice"), false)))
	    return FText::FromString("ICE DMG");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Fire"), false)))
	    return FText::FromString("FIRE DMG");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Light"), false)))
	    return FText::FromString("LIGHT DMG");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Shadow"), false)))
	    return FText::FromString("SHADOW DMG");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance"), false)))
	    return FText::FromString("RESIST ALL");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Physical"), false)))
	    return FText::FromString("PHYS RESIST");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Poison"), false)))
	    return FText::FromString("POISON RESIST");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Ice"), false)))
	    return FText::FromString("ICE RESIST");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Fire"), false)))
	    return FText::FromString("FIRE RESIST");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Light"), false)))
	    return FText::FromString("LIGHT RESIST");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Shadow"), false)))
	    return FText::FromString("SHADOW RESIST");
	else
	    return FText::FromString("NO TAG");
}

FText UInv_WidgetUtils::GetItemTypeNameFromTag(FGameplayTag ItemType)
{
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Weapons.Swords"), false)))
	{
		return FText::FromString("SWORD");
	}
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Weapons.Hammers"), false)))
	{
		return FText::FromString("HAMMER");
	}
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Weapons.Staffs"), false)))
	{
		return FText::FromString("STAFF");
	}
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Weapons.Maces"), false)))
	{
		return FText::FromString("MACE");
	}
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Weapons.Bows"), false)))
	{
		return FText::FromString("BOW");
	}
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Weapons.Shields"), false)))
	{
		return FText::FromString("SHIELD");
	}
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Weapons"), false)))
	{
		return FText::FromString("WEAPON");
	}
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Helmets"), false)))
	{
		return FText::FromString("HELMET");
	}
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Belts"), false)))
	{
		return FText::FromString("BELT");
	}
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Gauntlets"), false)))
	{
		return FText::FromString("GAUNTLETS");
	}
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Greaves"), false)))
	{
		return FText::FromString("GREAVES");
	}
	if (ItemType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("TOTUItems.Equipment.Chestplates"), false)))
	{
		return FText::FromString("CHESTPLATE");
	}
	
	return FText::FromString("ITEM");
}

FText UInv_WidgetUtils::GetAttributeTextName(FGameplayTag RequestedAttributeTag)
{
	if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Strength"), false)))
	    return FText::FromString("STRENGTH");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Intelligence"), false)))
	    return FText::FromString("INTELLIGENCE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Fortitude"), false)))
	    return FText::FromString("FORTITUDE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Primary.Vitality"), false)))
	    return FText::FromString("VITALITY");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.Dexterity"), false)))
	    return FText::FromString("DEXTERITY");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.MaxMana"), false)))
	    return FText::FromString("MAXIMUM MANA");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.ManaRegen"), false)))
	    return FText::FromString("MANA REGENERATION");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.MaxHealth"), false)))
	    return FText::FromString("MAXIMUM HEALTH");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.HealthRegen"), false)))
	    return FText::FromString("HEALTH REGENERATION");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.CritChance"), false)))
	    return FText::FromString("CRITICAL CHANCE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.CritDamage"), false)))
	    return FText::FromString("CRITICAL DAMAGE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Secondary.IgnoreDEF"), false)))
	    return FText::FromString("IGNORE RESISTANCE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Physical"), false)))
	    return FText::FromString("PHYSICAL DAMAGE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Poison"), false)))
	    return FText::FromString("POISON DAMAGE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Ice"), false)))
	    return FText::FromString("ICE DAMAGE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Fire"), false)))
	    return FText::FromString("FIRE DAMAGE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Light"), false)))
	    return FText::FromString("LIGHT DAMAGE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Damage.Shadow"), false)))
	    return FText::FromString("SHADOW DAMAGE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance"), false)))
	    return FText::FromString("ALL RESISTANCE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Physical"), false)))
	    return FText::FromString("PHYSICAL RESISTANCE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Poison"), false)))
	    return FText::FromString("POISON RESISTANCE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Ice"), false)))
	    return FText::FromString("ICE RESISTANCE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Fire"), false)))
	    return FText::FromString("FIRE RESISTANCE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Light"), false)))
	    return FText::FromString("LIGHT RESISTANCE");
	else if (RequestedAttributeTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Attributes.Resistance.Shadow"), false)))
	    return FText::FromString("SHADOW RESISTANCE");
	else
	    return FText::FromString("NO TAG");
}

FText UInv_WidgetUtils::GetSignedAttributeValueFromInt(int32 RequestedValue)
{
	// This function takes an int32 and returns an FText signed value. I.e., 32 becomes "+32"
	
	FNumberFormattingOptions Options;
	FText NumberText = FText::AsNumber(RequestedValue, &Options);

	FText Prefix = RequestedValue < 0
		? FText::FromString(TEXT("-"))
		: FText::FromString(TEXT("+"));

	FText Result = FText::Format(
		NSLOCTEXT("MyNamespace", "PlusMinusFmt", "{0}{1}"),
		Prefix,
		NumberText);

	return Result;
}

FInv_ItemGlowMaterialData UInv_WidgetUtils::GetItemGlowData(FInv_ItemData ItemData)
{
	FInv_ItemGlowMaterialData Data;
	
	if (ItemData.Rarity == EInv_ItemRarity::Supreme)
	{
		Data.GodRayIntensity = 0.6f;
		Data.GodRayPow = 3.0f;
		Data.DistortionGlow = 1.0f;
		Data.StarsBrightness = 0.5f;
	}
	if (ItemData.Rarity == EInv_ItemRarity::Mythical)
	{
		Data.GodRayIntensity = 0.7f;
		Data.GodRayPow = 3.0f;
		Data.DistortionGlow = 0.88f;
		Data.StarsBrightness = 0.4f;
	}
	if (ItemData.Rarity == EInv_ItemRarity::Legendary)
	{
		Data.GodRayIntensity = 0.8f;
		Data.GodRayPow = 3.0f;
		Data.DistortionGlow = 0.66f;
		Data.StarsBrightness = 0.3f;
	}
	if (ItemData.Rarity == EInv_ItemRarity::Epic)
	{
		Data.GodRayIntensity = 0.9f;
		Data.GodRayPow = 3.0f;
		Data.DistortionGlow = 0.44f;
		Data.StarsBrightness = 0.1f;
	}
	if (ItemData.Rarity == EInv_ItemRarity::Rare
		or
		ItemData.Rarity == EInv_ItemRarity::Uncommon
		or
		ItemData.Rarity == EInv_ItemRarity::Common)
	{
		Data.GodRayIntensity = 10.0f;
		Data.GodRayPow = 10.0f;
		Data.DistortionGlow = 0.0f;
		Data.StarsBrightness = 0.0f;
	}

	if  (ItemData.SpecialType == EInv_ItemSpecialType::Prismatic)
	{
		Data.PrismaticBlend = 0.33f;
		Data.PrismaticIntensity = 120.0f;
	} else
	{
		Data.PrismaticBlend = 0.0f;
		Data.PrismaticIntensity = 0.0f;
	}
	
	Data.RarityColor = GetColorFromRarityEnum(ItemData.Rarity);
	return Data;
}

FInv_ItemGlintMaterialData UInv_WidgetUtils::GetItemGlintData(FInv_ItemData ItemData)
{
	FInv_ItemGlintMaterialData Data;

	// Item has no Type and No Enhancement, it should have no color.
	if (ItemData.SpecialType == EInv_ItemSpecialType::None
		&&  ItemData.Enhancement == EInv_ItemEnhancement::None)
	{
		Data.ColorOpacity = 0.0f;
		Data.PrismaticBlend = 0.0f;
		return Data; // Early return.
	}
	
	if (ItemData.SpecialType == EInv_ItemSpecialType::Prismatic)
	{
		Data.PrismaticBlend = 1.25f;
		Data.ColorOpacity = 1.f;
		Data.GlintColor = FLinearColor::FromSRGBColor(FColor::FromHex("FF47ACFF"));
	}
	else
	{
		Data.PrismaticBlend = 0.0f;
	}

	if (ItemData.SpecialType == EInv_ItemSpecialType::Eldritch)
	{
		Data.ColorOpacity = -0.1f;
		Data.GlintColor = FLinearColor::FromSRGBColor(FColor::FromHex("FFE3A1FF"));
	}

	if (ItemData.SpecialType == EInv_ItemSpecialType::Netherborn)
	{
		Data.ColorOpacity = 2.0f;
		Data.GlintColor = FLinearColor::FromSRGBColor(FColor::FromHex("920F00FF"));
	}

	if (ItemData.SpecialType == EInv_ItemSpecialType::Ethereal)
	{
		Data.ColorOpacity = 0.35f;
		Data.GlintColor = FLinearColor::FromSRGBColor(FColor::FromHex("ABFFF9FF"));
	}

	if (ItemData.SpecialType == EInv_ItemSpecialType::Runescribed)
	{
		Data.ColorOpacity = 0.77f;
		Data.GlintColor = FLinearColor::FromSRGBColor(FColor::FromHex("00DE2FFF"));
	}

	// TODO: eventually enchantments will exist but im too lazy to add those rn
	
	return Data;
}

FVector2D UInv_WidgetUtils::GetWidgetPosition(UWidget* Widget)
{
	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	const FGeometry Geometry = Widget->GetCachedGeometry();
	USlateBlueprintLibrary::LocalToViewport(Widget, Geometry, USlateBlueprintLibrary::GetLocalTopLeft(Geometry), PixelPosition, ViewportPosition);
	return ViewportPosition;
}

FVector2D UInv_WidgetUtils::GetWidgetSize(UWidget* Widget)
{
	const FGeometry Geometry = Widget->GetCachedGeometry();
	return Geometry.GetLocalSize();
}

bool UInv_WidgetUtils::IsWithinBounds(const FVector2D& BoundaryPos, const FVector2D& WidgetSize,
                                      const FVector2D& MousePos)
{
	return MousePos.X >= BoundaryPos.X && MousePos.X <= (BoundaryPos.X + WidgetSize.X) &&
		MousePos.Y >= BoundaryPos.Y && MousePos.Y <= (BoundaryPos.Y + WidgetSize.Y);
}

bool UInv_WidgetUtils::IsWithinWidgetBounds(const FVector2D& WidgetPos, const FVector2D& WidgetSize,
											const FVector2D& MousePos)
{
	return MousePos.X >= WidgetPos.X && MousePos.X <= (WidgetPos.X + WidgetSize.X) &&
		   MousePos.Y >= WidgetPos.Y && MousePos.Y <= (WidgetPos.Y + WidgetSize.Y);
}

FVector2D UInv_WidgetUtils::GetClampedWidgetPosition(const FVector2D& Boundary, const FVector2D& WidgetSize,
	const FVector2D& MousePosition)
{
	FVector2D ClampedPosition = MousePosition;

	// Adjust horizontal position to ensure that the widget stays within the boundary.
	if (MousePosition.X + WidgetSize.X > Boundary.X) // Widget exceeds right edge boundary.
	{
		ClampedPosition.X = Boundary.X - WidgetSize.X;
	}
	if (MousePosition.X < 0.f) // Widget exceeds the left edge boundary.
	{
		ClampedPosition.X = 0.f;
	}

	// Adjust vertical position to ensure that the widget stays within the boundary.
	if (MousePosition.Y + WidgetSize.Y > Boundary.Y) // Widget exceeds the bottom edge boundary.
	{
		ClampedPosition.Y = Boundary.Y - WidgetSize.Y;
	}
	if (MousePosition.Y < 0.f)
	{
		ClampedPosition.Y = 0.f;
	}
	return ClampedPosition;
}


int32 UInv_WidgetUtils::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{
	return Position.X + Position.Y * Columns;
}

FIntPoint UInv_WidgetUtils::GetPositionFromIndex(const int32 Index, const int32 Columns)
{
	return FIntPoint(Index % Columns,  Index / Columns);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
