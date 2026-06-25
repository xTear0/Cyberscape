// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Font.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateTypes.h"
#include "CUI_StyleAsset.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
USTRUCT(BlueprintType)
struct FCUI_FontFamily
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TObjectPtr<UFont> FontObject = nullptr;

    // Matches a TypefaceFontName entry inside FontObject. Leave as None to use the font's default typeface.
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName Typeface = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin="1"))
    float DefaultSize = 12.0f;
};

USTRUCT(BlueprintType)
struct FCUI_Style
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TMap<FString, FLinearColor> Surfaces
    {
        { TEXT("Surface/BG"),      FLinearColor(FColor::FromHex(TEXT("0D0E1A"))) },
        { TEXT("Surface/Base"),    FLinearColor(FColor::FromHex(TEXT("12131F"))) },
        { TEXT("Surface/Raised"),  FLinearColor(FColor::FromHex(TEXT("1A1D32"))) },
        { TEXT("Surface/Overlay"), FLinearColor(FColor::FromHex(TEXT("21253E"))) },
        { TEXT("Surface/Hover"),   FLinearColor(FColor::FromHex(TEXT("2A2F50"))) },
    };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TMap<FString, FLinearColor> Grays
    {
        { TEXT("Gray/Border"),    FLinearColor(FColor::FromHex(TEXT("2E3146"))) },
        { TEXT("Gray/Subtle"),    FLinearColor(FColor::FromHex(TEXT("3D4270"))) },
        { TEXT("Gray/Muted"),     FLinearColor(FColor::FromHex(TEXT("5B618F"))) },
        { TEXT("Gray/Secondary"), FLinearColor(FColor::FromHex(TEXT("8E93C0"))) },
        { TEXT("Gray/Primary"),   FLinearColor(FColor::FromHex(TEXT("C8D0F5"))) },
    };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TMap<FString, FLinearColor> Accents
    {
        { TEXT("Accent/950"), FLinearColor(FColor::FromHex(TEXT("0B0D1C"))) },
        { TEXT("Accent/900"), FLinearColor(FColor::FromHex(TEXT("12163A"))) },
        { TEXT("Accent/800"), FLinearColor(FColor::FromHex(TEXT("1E2568"))) },
        { TEXT("Accent/700"), FLinearColor(FColor::FromHex(TEXT("2D3E9A"))) },
        { TEXT("Accent/600"), FLinearColor(FColor::FromHex(TEXT("4B67D0"))) },
        { TEXT("Accent/400"), FLinearColor(FColor::FromHex(TEXT("809DE7"))) },
        { TEXT("Accent/300"), FLinearColor(FColor::FromHex(TEXT("A3BAEE"))) },
        { TEXT("Accent/200"), FLinearColor(FColor::FromHex(TEXT("C2D2F5"))) },
        { TEXT("Accent/100"), FLinearColor(FColor::FromHex(TEXT("E0E9FC"))) },
        { TEXT("Accent/50"),  FLinearColor(FColor::FromHex(TEXT("F0F4FE"))) },
    };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TMap<FString, FLinearColor> Semantics
    {
        { TEXT("Success"),    FLinearColor(FColor::FromHex(TEXT("3BAA78"))) },
        { TEXT("SuccessBg"),  FLinearColor(FColor::FromHex(TEXT("1E2E24"))) },
        { TEXT("Warning"),    FLinearColor(FColor::FromHex(TEXT("D98A38"))) },
        { TEXT("WarningBg"),  FLinearColor(FColor::FromHex(TEXT("2B2214"))) },
        { TEXT("Danger"),     FLinearColor(FColor::FromHex(TEXT("D94848"))) },
        { TEXT("DangerBg"),   FLinearColor(FColor::FromHex(TEXT("2B1414"))) },
        { TEXT("Info"),       FLinearColor(FColor::FromHex(TEXT("809DE7"))) },
        { TEXT("InfoBg"),     FLinearColor(FColor::FromHex(TEXT("1A1D32"))) },
    };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TMap<FString, FSlateSound> SoundCues
    {
        { TEXT("Account Created"),       FSlateSound() },
        { TEXT("Button Click"),          FSlateSound() },
        { TEXT("Button Hover"),          FSlateSound() },
        { TEXT("Click"),                 FSlateSound() },
        { TEXT("Error"),                 FSlateSound() },
        { TEXT("Exit"),                  FSlateSound() },
        { TEXT("Incorrect Credentials"), FSlateSound() },
        { TEXT("Join Server"),           FSlateSound() },
        { TEXT("Login"),                 FSlateSound() },
        { TEXT("Next"),                  FSlateSound() },
        { TEXT("Search"),                FSlateSound() },
        { TEXT("Searching"),             FSlateSound() },
        { TEXT("Successful Login"),      FSlateSound() },
        { TEXT("Transition"),            FSlateSound() }
    };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TMap<FString, FCUI_FontFamily> FontFamilies
    {
        { TEXT("Display"), FCUI_FontFamily() },
        { TEXT("Body"),    FCUI_FontFamily() },
        { TEXT("Mono"),    FCUI_FontFamily() }
    };

    TArray<FString> GetAllColorNames() const;
    FLinearColor FindColor(const FString& Name) const;
    TArray<FString> GetAllSoundNames() const;
    FSlateSound FindSound(const FString& Name) const;
    TArray<FString> GetAllFontFamilyNames() const;
    FCUI_FontFamily FindFontFamily(const FString& Name) const;
};
/*-------------------------------------------------------------------------*/

/*
 * The Style Asset is responsible for containing all the theming information
 * for how all widgets are styled.
 */

/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_StyleAsset.h_Class
UCLASS(BlueprintType)
class CLICKYUI_API UCUI_StyleAsset : public UDataAsset
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Styles")
    TMap<FString, FCUI_Style> StyleLibrary;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Styles", meta=(GetOptions="GetStyleNames"))
    FString ActiveTheme;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Styles")
    FCUI_Style GetActiveStyle() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Styles")
    FCUI_Style GetStyleByName(const FString& Name) const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Styles")
    FLinearColor GetColorByName(const FString& Name) const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Styles")
    FSlateSound GetSoundByName(const FString& Name) const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Styles")
    USoundBase* GetSoundBaseByName(const FString& Name) const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Styles")
    FCUI_FontFamily GetFontFamilyByName(const FString& Name) const;

    UFUNCTION()
    TArray<FString> GetStyleNames() const;

    UFUNCTION()
    TArray<FString> GetActiveColorNames() const;

    UFUNCTION()
    TArray<FString> GetActiveSoundNames() const;

    UFUNCTION()
    TArray<FString> GetActiveFontFamilyNames() const;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
