// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Extensions/UIComponent.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateTypes.h"
#include "SYS7_StyleServiceComponent.generated.h"
/*-------------------------------------------------------------------------*/


/**
 * This component is added to any widget to override its color, sound, or font
 * to a named token from the assigned style asset. Color applies to most widget
 * types; sound applies to UButton; font applies to UTextBlock.
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

    // Font family — picks the UFont asset from the style asset (only applied to UTextBlock)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style|Font", meta=(GetOptions="GetFontFamilyNames"))
    FString FontFamilyToken;

    // Typeface variant within the selected family (matches TypefaceFontName in the UFont asset)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style|Font", meta=(GetOptions="GetTypefaceNames"))
    FString Typeface = TEXT("Display/Default");

    // Optional size override — 0 means use the family's default size
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style|Font", meta=(ClampMin="0"))
    float FontSizeOverride = 0.0f;

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

    UFUNCTION()
    TArray<FString> GetTypefaceNames() const;
};
#pragma endregion
/*-------------------------------------------------------------------------*/