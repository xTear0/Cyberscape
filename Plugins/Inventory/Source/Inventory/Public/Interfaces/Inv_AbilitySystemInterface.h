// Copyright xTear Studios
#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inv_AbilitySystemInterface.generated.h"

class UAbilitySystemComponent;
class UInv_AttributeModificationHandler;

UINTERFACE(MinimalAPI, Blueprintable)
class UInv_AbilitySystemInterface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORY_API IInv_AbilitySystemInterface
{
	GENERATED_BODY()

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponentForInventory() const = 0;
	virtual UInv_AttributeModificationHandler* GetAttributeModificationHandlerForInventory() const = 0;
};