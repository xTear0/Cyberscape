// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Extensions/UIComponent.h"
#include "SYS7_ColorServiceComponent.generated.h"
/*-------------------------------------------------------------------------*/


/**
 * This component is added to any widget to override its color to a named
 * token from the assigned style asset.
 */


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class USYS7_StyleAsset;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_ColorServiceComponent.h_Class
UCLASS(Blueprintable)
class SYSTEM7_API USYS7_ColorServiceComponent : public UUIComponent
{
	GENERATED_BODY()
    
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style")
	TObjectPtr<USYS7_StyleAsset> StyleAsset;

	// Dropdown populates from the style asset's named color tokens
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style", meta=(GetOptions="GetColorNames"))
	FString ColorToken;

protected:
	virtual void OnPreConstruct(bool bIsDesignTime) override;

	FLinearColor GetColor() const;

	// GetOptions source — queries the assigned style asset
	UFUNCTION()
	TArray<FString> GetColorNames() const;
};
#pragma endregion
/*-------------------------------------------------------------------------*/