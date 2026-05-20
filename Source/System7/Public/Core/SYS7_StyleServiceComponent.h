// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Extensions/UIComponent.h"
#include "Styling/SlateTypes.h"
#include "SYS7_StyleServiceComponent.generated.h"
/*-------------------------------------------------------------------------*/


/**
 * This component is added to any widget to override its color to a named
 * token from the assigned style asset. When added to a button, it can also
 * override the button's pressed and hovered sounds from the same asset.
 */


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class USYS7_StyleAsset;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_StyleServiceComponent.h_Class
UCLASS(Blueprintable)
class SYSTEM7_API USYS7_StyleServiceComponent : public UUIComponent
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style")
    TObjectPtr<USYS7_StyleAsset> StyleAsset;

    // Dropdown populates from the style asset's named color tokens
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style|Color", meta=(GetOptions="GetColorNames"))
    FString ColorToken;

    // Sound tokens — only applied when this component lives on a UButton
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style|Sound", meta=(GetOptions="GetSoundNames"))
    FString PressedSoundToken;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style|Sound", meta=(GetOptions="GetSoundNames"))
    FString HoverSoundToken;

protected:
    virtual void OnPreConstruct(bool bIsDesignTime) override;

    FLinearColor GetColor() const;
    FSlateSound  GetSound(const FString& Token) const;

    // GetOptions sources — query the assigned style asset
    UFUNCTION()
    TArray<FString> GetColorNames() const;

    UFUNCTION()
    TArray<FString> GetSoundNames() const;
};
#pragma endregion
/*-------------------------------------------------------------------------*/