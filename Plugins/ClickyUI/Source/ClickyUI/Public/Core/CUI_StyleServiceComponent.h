// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Extensions/UIComponent.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateTypes.h"
#include "CUI_StyleServiceComponent.generated.h"
/*-------------------------------------------------------------------------*/

/**
 * This component is added to any widget to override its color, sound, or font
 * to a named token from the assigned style asset. Color applies to most widget
 * types; sound applies to UButton; font applies to UTextBlock.
 *
 * Tokens can be changed at runtime via SetColorToken / SetStyleAsset, or by
 * editing the properties directly and calling RefreshStyle().
 */


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCUI_StyleAsset;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_StyleServiceComponent.h_Class
UCLASS(Blueprintable)
class CLICKYUI_API UCUI_StyleServiceComponent : public UUIComponent
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style")
    TObjectPtr<UCUI_StyleAsset> StyleAsset;

    // Dropdown populates from the style asset's named color tokens
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style|Color", meta=(GetOptions="GetColorNames"))
    FString ColorToken;

    // Sound tokens — only applied when this component lives on a UButton
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style|Sound", meta=(GetOptions="GetSoundNames"))
    FString PressedSoundToken;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style|Sound", meta=(GetOptions="GetSoundNames"))
    FString HoverSoundToken;

    // Font family — picks the UFont asset from the style asset (only applied to UTextBlock)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style|Font", meta=(GetOptions="GetFontFamilyNames"))
    FString FontFamilyToken;

    // Optional size override — 0 means use the family's default size
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style|Font", meta=(ClampMin="0"))
    float FontSizeOverride = 0.0f;

    /*---------------------------------------------------------------------*/
    /*   Runtime API                                                       */
    /*---------------------------------------------------------------------*/

    /**
     * Sets the color token (e.g. "Gray/Secondary", "Accent/600", "Danger", "Rare").
     * Rejects tokens that don't exist in the active style of the style asset.
     * @return true if the token was accepted.
     */
    UFUNCTION(BlueprintCallable, Category="Style|Color")
    bool SetColorToken(const FString& NewToken, bool bRefresh = true);

    UFUNCTION(BlueprintCallable, Category="Style")
    void SetStyleAsset(UCUI_StyleAsset* NewStyleAsset, bool bRefresh = true);

    // Re-applies color, sounds and font to the owner widget (same work as PreConstruct).
    UFUNCTION(BlueprintCallable, Category="Style")
    void RefreshStyle();

    // True if the token exists in the style asset's active style.
    UFUNCTION(BlueprintPure, Category="Style|Color")
    bool IsValidColorToken(const FString& Token) const;

    UFUNCTION(BlueprintPure, Category="Style|Color")
    FLinearColor GetResolvedColor() const { return GetColor(); }

protected:
    virtual void OnPreConstruct(bool bIsDesignTime) override;

    FLinearColor   GetColor() const;
    FSlateSound    GetSound(const FString& Token) const;
    FSlateFontInfo BuildFont() const;

    // GetOptions sources — query the assigned style asset
    UFUNCTION()
    TArray<FString> GetColorNames() const;

    UFUNCTION()
    TArray<FString> GetSoundNames() const;

    UFUNCTION()
    TArray<FString> GetFontFamilyNames() const;
};
#pragma endregion
/*-------------------------------------------------------------------------*/