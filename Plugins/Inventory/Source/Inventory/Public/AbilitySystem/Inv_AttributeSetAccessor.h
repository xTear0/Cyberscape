// Copyright xTear Studios
#pragma once
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "Inv_AttributeSetAccessor.generated.h"


UCLASS(Abstract, Blueprintable)
class INVENTORY_API UInv_AttributeSetAccessor : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Attributes")
	FGameplayAttribute GetAttributeFromTag(const FGameplayTag& AttributeTag) const;
	virtual FGameplayAttribute GetAttributeFromTag_Implementation(const FGameplayTag& AttributeTag) const { return FGameplayAttribute(); }
};