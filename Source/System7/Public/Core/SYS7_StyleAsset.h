// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SYS7_StyleAsset.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
USTRUCT(BlueprintType)
struct FSYS7_Style
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

    // Returns every named color across all groups — used to drive dropdowns
    TArray<FString> GetAllColorNames() const
    {
        TArray<FString> Names;
        Surfaces.GetKeys(Names);
        TArray<FString> Temp;
        Grays.GetKeys(Temp);    Names.Append(Temp);
        Accents.GetKeys(Temp);  Names.Append(Temp);
        Semantics.GetKeys(Temp);Names.Append(Temp);
        return Names;
    }

    // Searches all groups by name and returns the color (white = not found)
    FLinearColor FindColor(const FString& Name) const
    {
        if (const FLinearColor* C = Surfaces.Find(Name))  return *C;
        if (const FLinearColor* C = Grays.Find(Name))     return *C;
        if (const FLinearColor* C = Accents.Find(Name))   return *C;
        if (const FLinearColor* C = Semantics.Find(Name)) return *C;
        return FLinearColor::White;
    }
};
/*-------------------------------------------------------------------------*/

/*
 * The Style Asset is responsible for containing all the theming information
 * for how all widgets are styled.
 */

/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_StyleAsset.h_Class
UCLASS(BlueprintType)
class USYS7_StyleAsset : public UDataAsset
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Styles")
    TMap<FString, FSYS7_Style> StyleLibrary;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Styles", meta=(GetOptions="GetStyleNames"))
    FString ActiveTheme;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Styles")
    FSYS7_Style GetActiveStyle() const
    {
        if (const FSYS7_Style* Found = StyleLibrary.Find(ActiveTheme))
            return *Found;
        return FSYS7_Style();
    }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Styles")
    FSYS7_Style GetStyleByName(const FString& Name) const
    {
        if (const FSYS7_Style* Found = StyleLibrary.Find(Name))
            return *Found;
        return FSYS7_Style();
    }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Styles")
    FLinearColor GetColorByName(const FString& Name) const
    {
        return GetActiveStyle().FindColor(Name);
    }

    UFUNCTION()
    TArray<FString> GetStyleNames() const
    {
        TArray<FString> Keys;
        StyleLibrary.GetKeys(Keys);
        return Keys;
    }

    UFUNCTION()
    TArray<FString> GetActiveColorNames() const
    {
        return GetActiveStyle().GetAllColorNames();
    }
};
#pragma endregion
/*-------------------------------------------------------------------------*/