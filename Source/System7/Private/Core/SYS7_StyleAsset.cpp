// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "System7/Public/Core/SYS7_StyleAsset.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_StyleAsset.cpp_Functions

/*-------------------------------------------------------------------------*/
/*   FSYS7_Style                                                           */
/*-------------------------------------------------------------------------*/
TArray<FString> FSYS7_Style::GetAllColorNames() const
{
    TArray<FString> Names;
    Surfaces.GetKeys(Names);

    TArray<FString> Temp;
    Grays.GetKeys(Temp);     Names.Append(Temp);
    Accents.GetKeys(Temp);   Names.Append(Temp);
    Semantics.GetKeys(Temp); Names.Append(Temp);
    return Names;
}

FLinearColor FSYS7_Style::FindColor(const FString& Name) const
{
    if (const FLinearColor* C = Surfaces.Find(Name))  return *C;
    if (const FLinearColor* C = Grays.Find(Name))     return *C;
    if (const FLinearColor* C = Accents.Find(Name))   return *C;
    if (const FLinearColor* C = Semantics.Find(Name)) return *C;
    return FLinearColor::White;
}

TArray<FString> FSYS7_Style::GetAllSoundNames() const
{
    TArray<FString> Names;
    SoundCues.GetKeys(Names);
    return Names;
}

FSlateSound FSYS7_Style::FindSound(const FString& Name) const
{
    if (const FSlateSound* Found = SoundCues.Find(Name))
        return *Found;
    return FSlateSound();
}

TArray<FString> FSYS7_Style::GetAllFontFamilyNames() const
{
    TArray<FString> Names;
    FontFamilies.GetKeys(Names);
    return Names;
}

FSYS7_FontFamily FSYS7_Style::FindFontFamily(const FString& Name) const
{
    if (const FSYS7_FontFamily* Found = FontFamilies.Find(Name))
        return *Found;
    return FSYS7_FontFamily();
}


/*-------------------------------------------------------------------------*/
/*   USYS7_StyleAsset                                                      */
/*-------------------------------------------------------------------------*/
FSYS7_Style USYS7_StyleAsset::GetActiveStyle() const
{
    if (const FSYS7_Style* Found = StyleLibrary.Find(ActiveTheme))
        return *Found;
    return FSYS7_Style();
}

FSYS7_Style USYS7_StyleAsset::GetStyleByName(const FString& Name) const
{
    if (const FSYS7_Style* Found = StyleLibrary.Find(Name))
        return *Found;
    return FSYS7_Style();
}

FLinearColor USYS7_StyleAsset::GetColorByName(const FString& Name) const
{
    return GetActiveStyle().FindColor(Name);
}

FSlateSound USYS7_StyleAsset::GetSoundByName(const FString& Name) const
{
    return GetActiveStyle().FindSound(Name);
}

FSYS7_FontFamily USYS7_StyleAsset::GetFontFamilyByName(const FString& Name) const
{
    return GetActiveStyle().FindFontFamily(Name);
}

TArray<FString> USYS7_StyleAsset::GetStyleNames() const
{
    TArray<FString> Keys;
    StyleLibrary.GetKeys(Keys);
    return Keys;
}

TArray<FString> USYS7_StyleAsset::GetActiveColorNames() const
{
    return GetActiveStyle().GetAllColorNames();
}

TArray<FString> USYS7_StyleAsset::GetActiveSoundNames() const
{
    return GetActiveStyle().GetAllSoundNames();
}

TArray<FString> USYS7_StyleAsset::GetActiveFontFamilyNames() const
{
    return GetActiveStyle().GetAllFontFamilyNames();
}

#pragma endregion
/*-------------------------------------------------------------------------*/