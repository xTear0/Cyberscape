// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Misc/Icons/CUI_TieredItemIcon.h"
#include "Components/Image.h"
#include "Core/CUI_StyleAsset.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region CUI_TieredItemIcon.cpp_Functions
UCUI_TieredItemIcon::UCUI_TieredItemIcon(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // Pre-seeded tiers; assign materials in the Blueprint defaults.
    // None and Scrap are left out on purpose (no glint) — add them in the editor if you want one.
    for (const ECUI_ItemTier Tier : { ECUI_ItemTier::Tier1, ECUI_ItemTier::Tier2, ECUI_ItemTier::Tier3,
                                      ECUI_ItemTier::Tier4, ECUI_ItemTier::Tier5, ECUI_ItemTier::Prem })
    {
        GlintMaterials.Add(Tier, nullptr);
    }
}

void UCUI_TieredItemIcon::NativePreConstruct()
{
    Super::NativePreConstruct();

#if WITH_EDITORONLY_DATA
    if (IsDesignTime())
    {
        // Live preview in the UMG designer.
        CurrentIcon = PreviewIcon;
        CurrentTier = PreviewTier;
    }
#endif

    // At runtime this re-applies whatever was set before the widget was (re)constructed.
    SetIconAndTier(CurrentIcon, CurrentTier);
}

void UCUI_TieredItemIcon::SetIcon(UTexture2D* Icon)
{
    CurrentIcon = Icon;
    ApplyIcon();
    ApplyGlint();
}

void UCUI_TieredItemIcon::SetIconAndTier(UTexture2D* Icon, ECUI_ItemTier Tier)
{
    CurrentTier = Tier;
    ApplyBackground();
    SetIcon(Icon);
}

void UCUI_TieredItemIcon::SetTier(ECUI_ItemTier Tier)
{
    CurrentTier = Tier;
    ApplyGlint();
    ApplyBackground();
}

void UCUI_TieredItemIcon::ClearIcon()
{
    SetIcon(nullptr);
}

void UCUI_TieredItemIcon::ApplyIcon()
{
    if (!Image_Icon)
    {
        return;
    }

    if (!IsValid(CurrentIcon))
    {
        // Drop the texture reference too, so a cleared slot doesn't keep the old icon alive.
        Image_Icon->SetBrushResourceObject(nullptr);
        Image_Icon->SetVisibility(ESlateVisibility::Collapsed);
        return;
    }

    // Swaps only the resource (and ImageSize when matching); DrawAs, tint, margins,
    // outline etc. from the designer brush are preserved.
    Image_Icon->SetBrushFromTexture(CurrentIcon, bMatchTextureSize);
    Image_Icon->SetVisibility(IconShownVisibility);
}

UMaterialInstanceDynamic* UCUI_TieredItemIcon::GetGlintMID()
{
    const TObjectPtr<UMaterialInterface>* const Found = GlintMaterials.Find(CurrentTier);
    UMaterialInterface* const Material = Found ? Found->Get() : nullptr;
    if (!Material)
    {
        // Tier not in the map, or intentionally left without a glint. Expected — stay silent.
        return nullptr;
    }

    // Reuse the cached MID only if it was built from this tier's material.
    if (!GlintMID || GlintMID->Parent != Material)
    {
        GlintMID = UMaterialInstanceDynamic::Create(Material, this);
        Image_Glint->SetBrushResourceObject(GlintMID);
    }

    return GlintMID;
}

void UCUI_TieredItemIcon::ApplyGlint()
{
    if (!Image_Glint)
    {
        return;
    }

    UMaterialInstanceDynamic* const MID = GetGlintMID();

    if (!MID || !IsValid(CurrentIcon))
    {
        Image_Glint->SetVisibility(ESlateVisibility::Collapsed);
        return;
    }

    MID->SetTextureParameterValue(GlintTextureParam, CurrentIcon);
    MID->SetTextureParameterValue(GlintTextureObjectParam, CurrentIcon);

    if (bMatchTextureSize)
    {
        // Keep the glint the same size as the icon it sits on.
        FSlateBrush Brush = Image_Glint->GetBrush();
        Brush.ImageSize = FVector2D(CurrentIcon->GetSizeX(), CurrentIcon->GetSizeY());
        Image_Glint->SetBrush(Brush);
    }

    // Never eat clicks/drags meant for whatever owns this icon.
    Image_Glint->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCUI_TieredItemIcon::ApplyBackground()
{
    ApplyTokenColor({ Image_Background, Image_Background_Anim }, GetTierColorToken(CurrentTier), FallbackBackgroundToken, BackgroundOpacity);
    ApplyTokenColor({ Image_BackgroundStroke }, GetTierStrokeColorToken(CurrentTier), FallbackStrokeToken, StrokeOpacity);
}

void UCUI_TieredItemIcon::ApplyTokenColor(std::initializer_list<UImage*> Targets, const FString& Token, const FString& Fallback, float OpacityScale) const
{
    // No style asset assigned: leave whatever the designer set on the brushes.
    if (!IsValid(StyleAsset))
    {
        return;
    }

    const FString& Resolved = Token.IsEmpty() ? Fallback : Token;
    if (Resolved.IsEmpty())
    {
        return;
    }

    FLinearColor Color = StyleAsset->GetColorByName(Resolved);
    Color.A *= OpacityScale;

    for (UImage* const Target : Targets)
    {
        if (Target)
        {
            Target->SetColorAndOpacity(Color);
        }
    }
}

FString UCUI_TieredItemIcon::GetTierBaseToken(ECUI_ItemTier Tier)
{
    switch (Tier)
    {
        case ECUI_ItemTier::Tier1: return TEXT("Common");
        case ECUI_ItemTier::Tier2: return TEXT("Uncommon");
        case ECUI_ItemTier::Tier3: return TEXT("Rare");
        case ECUI_ItemTier::Tier4: return TEXT("Legendary");
        case ECUI_ItemTier::Tier5: return TEXT("Omega");
        case ECUI_ItemTier::Prem:  return TEXT("Premium");
        default:                   return FString();
    }
}

FString UCUI_TieredItemIcon::GetTierColorToken(ECUI_ItemTier Tier)
{
    const FString Base = GetTierBaseToken(Tier);
    return Base.IsEmpty() ? Base : Base + TEXT("_Accent");
}

FString UCUI_TieredItemIcon::GetTierStrokeColorToken(ECUI_ItemTier Tier)
{
    return GetTierBaseToken(Tier);
}

TArray<FString> UCUI_TieredItemIcon::GetColorTokenOptions() const
{
    return IsValid(StyleAsset) ? StyleAsset->GetActiveColorNames() : TArray<FString>{};
}
#pragma endregion
/*-------------------------------------------------------------------------*/