// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Core/CUI_StyleAsset.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_StyleAsset.cpp_Functions

/*-------------------------------------------------------------------------*/
/*   FCUI_Style                                                            */
/*-------------------------------------------------------------------------*/
TArray<FString> FCUI_Style::GetAllColorNames() const
{
    TArray<FString> Names;
    Surfaces.GetKeys(Names);

    TArray<FString> Temp;
    Grays.GetKeys(Temp);     Names.Append(Temp);
    Accents.GetKeys(Temp);   Names.Append(Temp);
    Semantics.GetKeys(Temp); Names.Append(Temp);
    Rarity.GetKeys(Temp);   Names.Append(Temp);
    return Names;
}

FLinearColor FCUI_Style::FindColor(const FString& Name) const
{
    if (const FLinearColor* C = Surfaces.Find(Name))  return *C;
    if (const FLinearColor* C = Grays.Find(Name))     return *C;
    if (const FLinearColor* C = Accents.Find(Name))   return *C;
    if (const FLinearColor* C = Semantics.Find(Name)) return *C;
    if (const FLinearColor* C = Rarity.Find(Name)) return *C;
    return FLinearColor::White;
}

TArray<FString> FCUI_Style::GetAllSoundNames() const
{
    TArray<FString> Names;
    SoundCues.GetKeys(Names);
    return Names;
}

FSlateSound FCUI_Style::FindSound(const FString& Name) const
{
    if (const FSlateSound* Found = SoundCues.Find(Name))
        return *Found;
    return FSlateSound();
}

TArray<FString> FCUI_Style::GetAllFontFamilyNames() const
{
    TArray<FString> Names;
    FontFamilies.GetKeys(Names);
    return Names;
}

FCUI_FontFamily FCUI_Style::FindFontFamily(const FString& Name) const
{
    if (const FCUI_FontFamily* Found = FontFamilies.Find(Name))
        return *Found;
    return FCUI_FontFamily();
}


/*-------------------------------------------------------------------------*/
/*   UCUI_StyleAsset                                                       */
/*-------------------------------------------------------------------------*/
FCUI_Style UCUI_StyleAsset::GetActiveStyle() const
{
    if (const FCUI_Style* Found = StyleLibrary.Find(ActiveTheme))
        return *Found;
    return FCUI_Style();
}

FCUI_Style UCUI_StyleAsset::GetStyleByName(const FString& Name) const
{
    if (const FCUI_Style* Found = StyleLibrary.Find(Name))
        return *Found;
    return FCUI_Style();
}

FLinearColor UCUI_StyleAsset::GetColorByName(const FString& Name) const
{
    const FCUI_Style* Style = FindActiveStyle();
    return Style ? Style->FindColor(Name) : FLinearColor::White;
}

FSlateSound UCUI_StyleAsset::GetSoundByName(const FString& Name) const
{
    const FCUI_Style* Style = FindActiveStyle();
    return Style ? Style->FindSound(Name) : FSlateSound();
}

USoundBase* UCUI_StyleAsset::GetSoundBaseByName(const FString& Name) const
{
    const FCUI_Style* Style = FindActiveStyle();
    if (!Style) return nullptr;

    const FSlateSound* Found = Style->SoundCues.Find(Name);
    return Found ? Cast<USoundBase>(const_cast<UObject*>(Found->GetResourceObject())) : nullptr;
}

FCUI_FontFamily UCUI_StyleAsset::GetFontFamilyByName(const FString& Name) const
{
    const FCUI_Style* Style = FindActiveStyle();
    return Style ? Style->FindFontFamily(Name) : FCUI_FontFamily();
}

bool UCUI_StyleAsset::HasColor(const FString& Name) const
{
    const FCUI_Style* Style = FindActiveStyle();
    return Style
        && (Style->Surfaces.Contains(Name) || Style->Grays.Contains(Name)
         || Style->Accents.Contains(Name)  || Style->Semantics.Contains(Name)
         || Style->Rarity.Contains(Name));
}

TArray<FString> UCUI_StyleAsset::GetStyleNames() const
{
    TArray<FString> Keys;
    StyleLibrary.GetKeys(Keys);
    return Keys;
}

TArray<FString> UCUI_StyleAsset::GetActiveColorNames() const
{
    return GetActiveStyle().GetAllColorNames();
}

TArray<FString> UCUI_StyleAsset::GetActiveSoundNames() const
{
    return GetActiveStyle().GetAllSoundNames();
}

TArray<FString> UCUI_StyleAsset::GetActiveFontFamilyNames() const
{
    return GetActiveStyle().GetAllFontFamilyNames();
}

#pragma endregion
/*-------------------------------------------------------------------------*/
