// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffect.h"
#include "AbilitySystem/Inv_AttributeSetAccessor.h"
#include "Interfaces/Inv_AbilitySystemInterface.h"
#include "Inv_EquippedItemPayload.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "Inv_AttributeModificationHandler.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UAbilitySystemComponent;
struct FGameplayAttribute;

USTRUCT(BlueprintType)
struct INVENTORY_API FInv_ItemPayloadDataEntry
{
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadOnly)
    FName ItemName = "null";
    
    UPROPERTY(BlueprintReadOnly)
    FLinearColor ItemColor =  FLinearColor::White;

    UPROPERTY(BlueprintReadOnly)
    int32 AttributeValue{0};
};

USTRUCT(BlueprintType)
struct INVENTORY_API FHoverInspectResult
{
    GENERATED_BODY()

    // This array is filled with valid entries of items modifying an attribute.
    UPROPERTY(BlueprintReadOnly) 
    TArray<FInv_ItemPayloadDataEntry> PayloadEntries; 

    // This int32 is the final value of all the payloads added up.
    UPROPERTY(BlueprintReadOnly)
    int32 TotalAttributeValue{0};
};
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_AttributeModificationHandler.h_Class
UCLASS(BlueprintType, Blueprintable)
class INVENTORY_API UInv_AttributeModificationHandler : public UObject
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SetAttributeSetAccessor(UInv_AttributeSetAccessor* Accessor) { AttributeSetAccessor = Accessor; }
    
/*-------------------------------------------------------------------------*/
/*   Payload Management Functions                                          */
/*-------------------------------------------------------------------------*/
#pragma region Inv_AttributeModificationHandler.h_AttributeExporting
    
    UFUNCTION()
    void AddPayload(const FGuid& PayloadID, const FInv_EquippedItemPayload& Payload);
    
    UFUNCTION()
    void RemovePayload(const FGuid& PayloadID);
    
#pragma endregion
/*-------------------------------------------------------------------------*/

    
    
/*-------------------------------------------------------------------------*/
/*   Payload Data Querying Functions                                       */
/*-------------------------------------------------------------------------*/
#pragma region Inv_AttributeModificationHandler.h_PayloadQueryingFunctions
    TArray<FInv_ItemPayloadDataEntry> QueryPayloadAttributeData(const FGameplayTag& Attribute);
        // Helper function. Returns an array of FInv_ItemAttributeDataEntries. These contain info about the payloads
        // which modify a specific attribute.

    int32 QueryPayloadAttributeValue(const FGameplayTag& Attribute);
        // Helper function. Returns an int32 total value of an attribute from all payloads.

    UFUNCTION(BlueprintCallable, Category = "Inv_AttributeModificationHandler")
    FHoverInspectResult HoverInspectAttribute(const FGameplayTag& Attribute);
        // This function returns an FHoverInspectResult which pulls information from the active payloads to give
        // information about the payloads modifying a specific attribute.
#pragma endregion
/*-------------------------------------------------------------------------*/


    
/*-------------------------------------------------------------------------*/
/*   Attribute Exporting Functions                                         */
/*-------------------------------------------------------------------------*/
#pragma region Inv_AttributeModificationHandler.h_AttributeExporting
    
    void CycleGameplayEffectFromPayloads();
        void RemoveGameplayEffect();    // Called first.
        void ApplyGameplayEffect();     // Called second.

#pragma endregion
/*-------------------------------------------------------------------------*/

    
private:
    // Helper Functions
    FGameplayAttribute GetAttributeFromTag(const FGameplayTag& AttributeTag) const;
    UAbilitySystemComponent* GetValidatedAbilitySystemComponent();
    TMap<FGameplayTag, int32> CalculateAttributeTotals();
    UGameplayEffect* CreateDynamicGameplayEffect(const TMap<FGameplayTag, int32>& AttributeTotals);
    bool AddModifierToEffect(UGameplayEffect* Effect, const FGameplayTag& AttributeTag, int32 Value);
    void ApplyEffectToAbilitySystem(UAbilitySystemComponent* ASC, UGameplayEffect* Effect);
    
    // Payload storage
    UPROPERTY()
    TMap<FString, FInv_EquippedItemPayload> ActivePayloads;

    UPROPERTY()
    TWeakObjectPtr<UAbilitySystemComponent> CachedASC;
    
    FActiveGameplayEffectHandle ActiveEffectHandle;

    UPROPERTY()
    TObjectPtr<UInv_AttributeSetAccessor> AttributeSetAccessor;
    
};
#pragma endregion
/*-------------------------------------------------------------------------*/