// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "EquipmentManagement/Modifications/Inv_AttributeModificationHandler.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemGlobals.h"
#include "InterchangeResult.h"

/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Payload Management                                                    */
/*-------------------------------------------------------------------------*/
#pragma region Inv_AttributeModificationHandler.cpp_PayloadManagement
void UInv_AttributeModificationHandler::AddPayload(const FGuid& PayloadID, const FInv_EquippedItemPayload& Payload)
{
    ActivePayloads.Add(PayloadID.ToString(), Payload);
    CycleGameplayEffectFromPayloads();
}

void UInv_AttributeModificationHandler::RemovePayload(const FGuid& PayloadID)
{
    if (ActivePayloads.Contains(PayloadID.ToString()))
    {
        ActivePayloads.Remove(PayloadID.ToString());
    } else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Payload was found with the ID %s. No issue, skipping."), *PayloadID.ToString());
    }
    CycleGameplayEffectFromPayloads();
}
#pragma endregion
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Payload Data Querying Functions                                       */
/*-------------------------------------------------------------------------*/
#pragma region Inv_AttributeModificationHandler.cpp_PayloadQuerying
TArray<FInv_ItemPayloadDataEntry> UInv_AttributeModificationHandler::QueryPayloadAttributeData(
    const FGameplayTag& Attribute)
{
    TArray<FInv_ItemPayloadDataEntry> Result;
    
    // Reserve space to minimize reallocations.
    Result.Reserve(ActivePayloads.Num());
    
    // Iterate over all active payloads in the TMap.
    for (const auto& PayloadPair : ActivePayloads)
    {
        const FInv_EquippedItemPayload& Payload = PayloadPair.Value;
        
        for (const FInv_ItemAttributePair& AttributePair : Payload.ItemAttributesContainer)
        {
            if (AttributePair.AttributeTag.MatchesTagExact(Attribute))
            {
                FInv_ItemPayloadDataEntry& NewEntry = Result.AddDefaulted_GetRef();
                NewEntry.ItemName = Payload.ItemName;
                NewEntry.ItemColor = Payload.ItemColor;
                NewEntry.AttributeValue = AttributePair.Value;
            }
        }
    }
    
    // Shrink the array to fit only the actual number of results.
    Result.Shrink();
    
    return Result;
}

int32 UInv_AttributeModificationHandler::QueryPayloadAttributeValue(const FGameplayTag& Attribute)
{
    int32 Result = 0;
    // Iterate over all active payloads in the TMap.
    for (const auto& PayloadPair : ActivePayloads)
    {
        const FInv_EquippedItemPayload& Payload = PayloadPair.Value;
        for (const FInv_ItemAttributePair& AttributePair : Payload.ItemAttributesContainer)
        {
            if (AttributePair.AttributeTag.MatchesTagExact(Attribute))
            {
                Result += AttributePair.Value;
            }
        }
    }
    return Result;
}

FHoverInspectResult UInv_AttributeModificationHandler::HoverInspectAttribute(const FGameplayTag& Attribute)
{
    FHoverInspectResult Result;                                             // Create Result
    
    Result.PayloadEntries = QueryPayloadAttributeData(Attribute);           // Fill in Payload Entries
    Result.TotalAttributeValue = QueryPayloadAttributeValue(Attribute);     // Fill in total Attribute Value
    
    return Result;                                                          // Return Result.
}
#pragma endregion
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Attribute Exporting Functions                                         */
/*-------------------------------------------------------------------------*/
#pragma region Inv_AttributeModificationHandler.cpp_AttributeExporting
void UInv_AttributeModificationHandler::CycleGameplayEffectFromPayloads()
{
    RemoveGameplayEffect();
    ApplyGameplayEffect();
}

void UInv_AttributeModificationHandler::RemoveGameplayEffect()
{
    // Check if we have a valid effect handle and ASC
    if (ActiveEffectHandle.IsValid() && CachedASC.IsValid())
    {
        CachedASC->RemoveActiveGameplayEffect(ActiveEffectHandle);
    }
    
    // Reset the handle regardless of whether removal was successful
    ActiveEffectHandle = FActiveGameplayEffectHandle();
}

void UInv_AttributeModificationHandler::ApplyGameplayEffect()
{
    UAbilitySystemComponent* ASC = GetValidatedAbilitySystemComponent();
    if (!ASC) return;
    CachedASC = ASC;
    
    TMap<FGameplayTag, int32> AttributeTotals = CalculateAttributeTotals();
    
    UGameplayEffect* DynamicEffect = CreateDynamicGameplayEffect(AttributeTotals);
    if (!DynamicEffect) return;
    
    ApplyEffectToAbilitySystem(ASC, DynamicEffect);
}

UAbilitySystemComponent* UInv_AttributeModificationHandler::GetValidatedAbilitySystemComponent()
{
    // Try to get from outer that implements the interface
    UObject* Outer = GetOuter();
    if (!Outer)
    {
        UE_LOG(LogTemp, Warning, TEXT("AttributeModificationHandler: No outer object"));
        return nullptr;
    }
    
    if (IInv_AbilitySystemInterface* AbilityInterface = Cast<IInv_AbilitySystemInterface>(Outer))
    {
        UAbilitySystemComponent* ASC = AbilityInterface->GetAbilitySystemComponentForInventory();
        if (!ASC)
        {
            UE_LOG(LogTemp, Warning, TEXT("AttributeModificationHandler: No Ability System Component"));
            return nullptr;
        }
        return ASC;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("AttributeModificationHandler: Outer does not implement IInv_AbilitySystemInterface"));
    return nullptr;
}

TMap<FGameplayTag, int32> UInv_AttributeModificationHandler::CalculateAttributeTotals()
{
    TMap<FGameplayTag, int32> AttributeTotals;
    
    for (const auto& PayloadPair : ActivePayloads)
    {
        const FInv_EquippedItemPayload& Payload = PayloadPair.Value;
        
        for (const FInv_ItemAttributePair& AttributePair : Payload.ItemAttributesContainer)
        {
            if (AttributeTotals.Contains(AttributePair.AttributeTag))
            {
                AttributeTotals[AttributePair.AttributeTag] += AttributePair.Value;
            }
            else
            {
                AttributeTotals.Add(AttributePair.AttributeTag, AttributePair.Value);
            }
        }
    }
    
    return AttributeTotals;
}

UGameplayEffect* UInv_AttributeModificationHandler::CreateDynamicGameplayEffect(const TMap<FGameplayTag, int32>& AttributeTotals)
{
    // Create a dynamic gameplay effect
    UGameplayEffect* DynamicEffect = NewObject<UGameplayEffect>(GetTransientPackage());
    if (!DynamicEffect)
    {
        UE_LOG(LogTemp, Error, TEXT("AttributeModificationHandler: Failed to create dynamic gameplay effect"));
        return nullptr;
    }
    
    // Configure the effect for infinite duration
    DynamicEffect->DurationPolicy = EGameplayEffectDurationType::Infinite;
    DynamicEffect->Modifiers.Empty(); // Clear any existing modifiers
    
    // Add modifiers for each attribute
    for (const auto& AttributeTotal : AttributeTotals)
    {
        if (AddModifierToEffect(DynamicEffect, AttributeTotal.Key, AttributeTotal.Value))
        {
            UE_LOG(LogTemp, VeryVerbose, TEXT("AttributeModificationHandler: Added modifier for %s with value %d"), 
                *AttributeTotal.Key.ToString(), AttributeTotal.Value);
        }
    }
    
    return DynamicEffect;
}

bool UInv_AttributeModificationHandler::AddModifierToEffect(UGameplayEffect* Effect, const FGameplayTag& AttributeTag, int32 Value)
{
    // Skip attributes with zero modification
    if (Value == 0)
    {
        return false;
    }
    
    // Resolve tag to actual attribute
    FGameplayAttribute GameplayAttribute = GetAttributeFromTag(AttributeTag);
    if (!GameplayAttribute.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("AttributeModificationHandler: Invalid attribute for tag %s"), *AttributeTag.ToString());
        return false;
    }
    
    // Create and configure the modifier
    FGameplayModifierInfo NewModifier;
    NewModifier.Attribute = GameplayAttribute;
    NewModifier.ModifierOp = EGameplayModOp::Additive;
    
    // Set the magnitude using a simple scalar float
    FScalableFloat Magnitude;
    Magnitude.Value = static_cast<float>(Value);
    NewModifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(Magnitude);
    
    // Add the modifier to the effect
    Effect->Modifiers.Add(NewModifier);
    return true;
}

void UInv_AttributeModificationHandler::ApplyEffectToAbilitySystem(UAbilitySystemComponent* ASC, UGameplayEffect* Effect)
{
    // Only apply the effect if we have modifiers
    if (Effect->Modifiers.Num() > 0)
    {
        // Apply the effect directly using the class
        FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
        ActiveEffectHandle = ASC->ApplyGameplayEffectToSelf(Effect, 1.0f, ContextHandle);
        
        if (!ActiveEffectHandle.IsValid())
        {
            UE_LOG(LogTemp, Warning, TEXT("AttributeModificationHandler: Failed to apply gameplay effect. Modifiers: %d"), Effect->Modifiers.Num());
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("AttributeModificationHandler: Successfully applied gameplay effect with %d modifiers"), Effect->Modifiers.Num());
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("AttributeModificationHandler: No modifiers to apply"));
    }
}

FGameplayAttribute UInv_AttributeModificationHandler::GetAttributeFromTag(const FGameplayTag& AttributeTag) const
{
    if (!AttributeSetAccessor)
    {
        UE_LOG(LogTemp, Warning, TEXT("AttributeSetAccessor not set!"));
        return FGameplayAttribute();
    }
    
    return AttributeSetAccessor->GetAttributeFromTag(AttributeTag);
}
#pragma endregion
/*-------------------------------------------------------------------------*/