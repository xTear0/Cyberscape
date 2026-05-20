// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "AttributeHoverSubsystem.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                         */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnGlobalAttributeHover,
	bool, bShow,
	FGameplayTag, AttributeTag
);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region AttributeHoverSubsystem.h_Class
UCLASS()
class INVENTORY_API UAttributeHoverSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Global delegate that inventory systems can bind to
	UPROPERTY(BlueprintAssignable)
	FOnGlobalAttributeHover OnAttributeHoverChanged;
    
	// Function for widgets to call when attribute is hovered
	UFUNCTION(BlueprintCallable, Category = "Attribute Hover")
	void BroadcastAttributeHover(bool bShow, FGameplayTag AttributeTag);
    
	// Static helper to get the subsystem
	UFUNCTION(BlueprintCallable, Category = "Attribute Hover", CallInEditor)
	static UAttributeHoverSubsystem* Get(const UObject* WorldContext);
};
#pragma endregion
/*-------------------------------------------------------------------------*/