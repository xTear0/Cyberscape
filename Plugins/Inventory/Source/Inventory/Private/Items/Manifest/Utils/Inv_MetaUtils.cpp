// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Items/Manifest/Utils/Inv_MetaUtils.h"
#include "Types/Inv_EnumTypes.h"
#include "Types/Inv_StructTypes.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*  Functions                                                              */
/*-------------------------------------------------------------------------*/
#pragma region Inv_MetaUtils.cpp_Functions
int UInv_MetaUtils::GetRandIntFromBaseScalar(const EInv_AttributeScalarPower BaseScalar)
{
    if (BaseScalar == EInv_AttributeScalarPower::Low)
        return FMath::RandRange(6, 7);
    if (BaseScalar == EInv_AttributeScalarPower::Med)
        return FMath::RandRange(8, 10);
    if (BaseScalar == EInv_AttributeScalarPower::High)
        return FMath::RandRange(10, 12);
    if (BaseScalar == EInv_AttributeScalarPower::Max)
        return FMath::RandRange(13, 15);
    else
    {
        return 0;
    }
}

int UInv_MetaUtils::GetRandIntFromMultScalar(const EInv_AttributeScalarPower MultScalar)
{
    if (MultScalar == EInv_AttributeScalarPower::Low)
        return FMath::RandRange(4, 5);
    if (MultScalar == EInv_AttributeScalarPower::Med)
        return FMath::RandRange(6, 8);
    if (MultScalar == EInv_AttributeScalarPower::High)
        return FMath::RandRange(8, 10);
    if (MultScalar == EInv_AttributeScalarPower::Max)
        return FMath::RandRange(10, 12);
    else
    {
        return 0;
    }
}

TArray<EInv_AttributeEntry> UInv_MetaUtils::GetValidAttributeList(TArray<EInv_SecondaryAttributeRules> Rules)
{
    TArray<EInv_AttributeEntry> ValidAttributeList;
    TSet<EInv_AttributeEntry> BlockedSet;
    TSet<EInv_AttributeEntry> PrioritySet;
    
    static const TMap<EInv_SecondaryAttributeRules, TArray<EInv_AttributeEntry>> RuleMap = GetRuleToAttributeMap();
    
    // Parse rules to build blocked and priority sets
    for (const EInv_SecondaryAttributeRules& Rule : Rules)
    {
        if (const TArray<EInv_AttributeEntry>* Attributes = RuleMap.Find(Rule))
        {
            FString RuleName = UEnum::GetValueAsString(Rule);
            if (RuleName.Contains("BLOCKED"))
            {
                BlockedSet.Append(*Attributes);
            }
            else if (RuleName.Contains("PRIORITY"))
            {
                PrioritySet.Append(*Attributes);
            }
        }
    }
    
    // Add all non-blocked attributes
    for (int32 i = 0; i < int32(EInv_AttributeEntry::Special_XP) + 1; ++i)
    {
        EInv_AttributeEntry Attr = (EInv_AttributeEntry)i;
        if (!BlockedSet.Contains(Attr))
        {
            ValidAttributeList.Add(Attr);
            
            // Duplicate if priority
            if (PrioritySet.Contains(Attr))
            {
                ValidAttributeList.Add(Attr);
            }
        }
    }
    
    return ValidAttributeList;
}

TMap<EInv_SecondaryAttributeRules, TArray<EInv_AttributeEntry>> UInv_MetaUtils::GetRuleToAttributeMap()
{
    static TMap<EInv_SecondaryAttributeRules, TArray<EInv_AttributeEntry>> RuleMap;
    
    if (RuleMap.Num() == 0)
    {
        // Attack mappings - PRIORITY
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_ATTACK_DEFAULT, 
            {EInv_AttributeEntry::Attack_Default});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_ATTACK_FIRE, 
            {EInv_AttributeEntry::Attack_Fire});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_ATTACK_ICE, 
            {EInv_AttributeEntry::Attack_Ice});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_ATTACK_COLD_FIRE, 
            {EInv_AttributeEntry::Attack_Cold_Fire});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_ATTACK_LIGHTNING, 
            {EInv_AttributeEntry::Attack_Lightning});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_ATTACK_VOID, 
            {EInv_AttributeEntry::Attack_Void});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_ATTACK_MULTIPLIERS, 
            {EInv_AttributeEntry::Attack_Default_Mult, EInv_AttributeEntry::Attack_Fire_Mult,
             EInv_AttributeEntry::Attack_Ice_Mult, EInv_AttributeEntry::Attack_Cold_Fire_Mult,
             EInv_AttributeEntry::Attack_Lightning_Mult, EInv_AttributeEntry::Attack_Void_Mult});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_ATTACK_CRITICAL, 
            {EInv_AttributeEntry::Attack_Crit_Damage, EInv_AttributeEntry::Attack_Crit_Rate});
        
        // Resist mappings - PRIORITY
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_RESIST_DEFAULT, 
            {EInv_AttributeEntry::Resist_Default});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_RESIST_FIRE, 
            {EInv_AttributeEntry::Resist_Fire});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_RESIST_ICE, 
            {EInv_AttributeEntry::Resist_Ice});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_RESIST_COLD_FIRE, 
            {EInv_AttributeEntry::Resist_Cold_Fire});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_RESIST_MULTIPLIERS, 
            {EInv_AttributeEntry::Resist_Default_Mult, EInv_AttributeEntry::Resist_Fire_Mult,
             EInv_AttributeEntry::Resist_Ice_Mult, EInv_AttributeEntry::Resist_Cold_Fire_Mult});
        
        // Other categories - PRIORITY
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_ARMOR, 
            {EInv_AttributeEntry::Armor_Light, EInv_AttributeEntry::Armor_Heavy, 
             EInv_AttributeEntry::Armor_Spectral});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_HEALTH, 
            {EInv_AttributeEntry::Health, EInv_AttributeEntry::Recovery,
             EInv_AttributeEntry::Health_Mult, EInv_AttributeEntry::Recovery_Mult});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_AGILITY, 
            {EInv_AttributeEntry::Agility, EInv_AttributeEntry::Energy, 
             EInv_AttributeEntry::Evasion});
        RuleMap.Add(EInv_SecondaryAttributeRules::PRIORITY_SPECIAL, 
            {EInv_AttributeEntry::Special_Supremacy, EInv_AttributeEntry::Special_Treasure,
             EInv_AttributeEntry::Special_Luck, EInv_AttributeEntry::Special_XP});
        
        // Attack mappings - BLOCKED (mirror of priority)
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_ATTACK_DEFAULT, 
            {EInv_AttributeEntry::Attack_Default});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_ATTACK_FIRE, 
            {EInv_AttributeEntry::Attack_Fire});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_ATTACK_ICE, 
            {EInv_AttributeEntry::Attack_Ice});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_ATTACK_COLD_FIRE, 
            {EInv_AttributeEntry::Attack_Cold_Fire});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_ATTACK_LIGHTNING, 
            {EInv_AttributeEntry::Attack_Lightning});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_ATTACK_VOID, 
            {EInv_AttributeEntry::Attack_Void});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_ATTACK_MULTIPLIERS, 
            {EInv_AttributeEntry::Attack_Default_Mult, EInv_AttributeEntry::Attack_Fire_Mult,
             EInv_AttributeEntry::Attack_Ice_Mult, EInv_AttributeEntry::Attack_Cold_Fire_Mult,
             EInv_AttributeEntry::Attack_Lightning_Mult, EInv_AttributeEntry::Attack_Void_Mult});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_ATTACK_CRITICAL, 
            {EInv_AttributeEntry::Attack_Crit_Damage, EInv_AttributeEntry::Attack_Crit_Rate});
        
        // Resist mappings - BLOCKED
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_RESIST_DEFAULT, 
            {EInv_AttributeEntry::Resist_Default});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_RESIST_FIRE, 
            {EInv_AttributeEntry::Resist_Fire});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_RESIST_ICE, 
            {EInv_AttributeEntry::Resist_Ice});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_RESIST_COLD_FIRE, 
            {EInv_AttributeEntry::Resist_Cold_Fire});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_RESIST_MULTIPLIERS, 
            {EInv_AttributeEntry::Resist_Default_Mult, EInv_AttributeEntry::Resist_Fire_Mult,
             EInv_AttributeEntry::Resist_Ice_Mult, EInv_AttributeEntry::Resist_Cold_Fire_Mult});
        
        // Other categories - BLOCKED
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_ARMOR, 
            {EInv_AttributeEntry::Armor_Light, EInv_AttributeEntry::Armor_Heavy, 
             EInv_AttributeEntry::Armor_Spectral});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_HEALTH, 
            {EInv_AttributeEntry::Health, EInv_AttributeEntry::Recovery,
             EInv_AttributeEntry::Health_Mult, EInv_AttributeEntry::Recovery_Mult});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_AGILITY, 
            {EInv_AttributeEntry::Agility, EInv_AttributeEntry::Energy, 
             EInv_AttributeEntry::Evasion});
        RuleMap.Add(EInv_SecondaryAttributeRules::BLOCKED_SPECIAL, 
            {EInv_AttributeEntry::Special_Supremacy, EInv_AttributeEntry::Special_Treasure,
             EInv_AttributeEntry::Special_Luck, EInv_AttributeEntry::Special_XP});
    }
    
    return RuleMap;
}
#pragma endregion
/*-------------------------------------------------------------------------*/