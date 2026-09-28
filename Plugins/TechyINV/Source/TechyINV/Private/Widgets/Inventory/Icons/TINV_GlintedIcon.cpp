// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/Icons/TINV_GlintedIcon.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "ItemData/TINV_ItemDataTable.h"
#include "Items/TINV_InventoryItem.h"
#include "Items/Components/TINV_ItemComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_GlintedIcon.cpp_Functions
UTINV_GlintedIcon::UTINV_GlintedIcon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GlintMaterials.Add(ETINV_ItemTier::Tier1, nullptr);
	GlintMaterials.Add(ETINV_ItemTier::Tier2, nullptr);
	GlintMaterials.Add(ETINV_ItemTier::Tier3, nullptr);
	GlintMaterials.Add(ETINV_ItemTier::Tier4, nullptr);
	GlintMaterials.Add(ETINV_ItemTier::Tier5, nullptr);
	GlintMaterials.Add(ETINV_ItemTier::Prem,  nullptr);
}

void UTINV_GlintedIcon::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Image_Icon)
	{
		IconVisibility = Image_Icon->GetVisibility();
	}
}

void UTINV_GlintedIcon::SetIcon(UTexture2D* Icon, ETINV_ItemTier GlintTier)
{
	CurrentIcon = Icon;

	if (Image_Icon)
	{
		if (IsValid(Icon))
		{
			Image_Icon->SetBrushResourceObject(Icon);
			Image_Icon->SetVisibility(IconVisibility);
		}
		else
		{
			Image_Icon->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	SetGlintTier(GlintTier);
}

bool UTINV_GlintedIcon::SetFromItemComponent(const UTINV_ItemComponent* ItemComponent)
{
	if (!IsValid(ItemComponent))
	{
		ClearIcon();
		return false;
	}

	return SetFromManifest(ItemComponent->GetItemManifest());
}

bool UTINV_GlintedIcon::SetFromInventoryItem(const UTINV_InventoryItem* Item)
{
	if (!IsValid(Item))
	{
		ClearIcon();
		return false;
	}

	return SetFromManifest(Item->GetItemManifest());
}

bool UTINV_GlintedIcon::SetFromManifest(const FTINV_ItemManifest& Manifest)
{
	const FTINV_ItemDataDefinition* ItemData = ItemDataTable ? ItemDataTable->GetDataByTag(Manifest.GetItemID()) : nullptr;
	if (!ItemData)
	{
		ClearIcon();
		return false;
	}

	SetIcon(ItemData->ItemIcon, ItemData->ItemTier);
	return true;
}

void UTINV_GlintedIcon::SetGlintTier(ETINV_ItemTier GlintTier)
{
	CurrentGlintTier = GlintTier;
	ApplyGlint();
}

void UTINV_GlintedIcon::ClearIcon()
{
	SetIcon(nullptr, ETINV_ItemTier::Scrap);
}

UMaterialInstanceDynamic* UTINV_GlintedIcon::GetGlintMID()
{
	if (!Image_Glint)
	{
		return nullptr;
	}

	const TObjectPtr<UMaterialInterface>* const Found = GlintMaterials.Find(CurrentGlintTier);
	UMaterialInterface* const Material = Found ? Found->Get() : nullptr;
	if (!Material)
	{
		return nullptr;
	}

	if (GlintMID && GlintMID->Parent == Material)
	{
		return GlintMID;
	}

	GlintMID = UMaterialInstanceDynamic::Create(Material, this);
	Image_Glint->SetBrushResourceObject(GlintMID);

	return GlintMID;
}

void UTINV_GlintedIcon::ApplyGlint()
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

	Image_Glint->SetVisibility(ESlateVisibility::HitTestInvisible);
}
#pragma endregion
/*-------------------------------------------------------------------------*/