// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/TINV_SlottedItem.h"
#include "Items/TINV_InventoryItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_SlottedItem.cpp_Functions
UTINV_SlottedItem::UTINV_SlottedItem(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // Pre-seeded tiers; assign materials in the Blueprint defaults.
    // Scrap is left out on purpose (no glint) — add it in the editor if you want one.
    GlintMaterials.Add(ETINV_ItemTier::Tier1, nullptr);
    GlintMaterials.Add(ETINV_ItemTier::Tier2, nullptr);
    GlintMaterials.Add(ETINV_ItemTier::Tier3, nullptr);
    GlintMaterials.Add(ETINV_ItemTier::Tier4, nullptr);
    GlintMaterials.Add(ETINV_ItemTier::Tier5, nullptr);
    GlintMaterials.Add(ETINV_ItemTier::Prem,  nullptr);
}

void UTINV_SlottedItem::SetInventoryItem(UTINV_InventoryItem* Item)
{
	InventoryItem = Item;
}

void UTINV_SlottedItem::UpdateStackCount(int32 StackCount)
{
	if (StackCount > 0)
	{
		Text_StackCount->SetText(FText::AsNumber(StackCount));
		Text_StackCount->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Text_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UTINV_SlottedItem::LoadIcon(UTexture2D* Icon, ETINV_ItemTier GlintTier)
{
    CurrentIcon = Icon;

    if (Image_Icon && IsValid(Icon))
    {
       // Preserves ImageSize, DrawAs, tint and margins from the designer brush.
       Image_Icon->SetBrushResourceObject(Icon);
    }

    SetGlintTier(GlintTier);
}

void UTINV_SlottedItem::SetGlintTier(ETINV_ItemTier GlintTier)
{
    CurrentGlintTier = GlintTier;
    ApplyGlint();
}

UMaterialInstanceDynamic* UTINV_SlottedItem::GetGlintMID()
{
    if (!Image_Glint)
    {
       return nullptr;
    }

    const TObjectPtr<UMaterialInterface>* const Found = GlintMaterials.Find(CurrentGlintTier);
    UMaterialInterface* const Material = Found ? Found->Get() : nullptr;
    if (!Material)
    {
       // Tier not in the map, or intentionally left without a glint. Expected — stay silent.
       return nullptr;
    }

    // Reuse the cached MID only if it was built from this tier's material.
    if (GlintMID && GlintMID->Parent == Material)
    {
       return GlintMID;
    }

    GlintMID = UMaterialInstanceDynamic::Create(Material, this);
    Image_Glint->SetBrushResourceObject(GlintMID);

    return GlintMID;
}

void UTINV_SlottedItem::ApplyGlint()
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

    // Never eat clicks/drags meant for the slotted item.
    Image_Glint->SetVisibility(ESlateVisibility::HitTestInvisible);
}
#pragma endregion
/*-------------------------------------------------------------------------*/