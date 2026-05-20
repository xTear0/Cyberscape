// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/SlottedItems/Inv_SlottedItem.h"
#include "Items/Inv_InventoryItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*  Functions                                                              */
/*-------------------------------------------------------------------------*/
#pragma region Inv_SlottedItem.cpp_Functions
FReply UInv_SlottedItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& MouseEvent)
{
	OnSlottedItemClick.Broadcast(GridIndex, MouseEvent);
	return FReply::Handled();
}

void UInv_SlottedItem::NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	UInv_InventoryStatics::ItemHovered(GetOwningPlayer(), InventoryItem.Get());
}

void UInv_SlottedItem::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	UInv_InventoryStatics::ItemUnhovered(GetOwningPlayer());	
}

FVector2D UInv_SlottedItem::GetImageIconSize() const
{
	return Image_Icon->GetBrush().GetImageSize();
}

FVector2D UInv_SlottedItem::GetImageGlowSize() const
{
	return  Image_Glow->GetBrush().GetImageSize();
}

void UInv_SlottedItem::SetGlowSize(FVector2D& NewGlowSize)
{
	GetImageGlow()->SetDesiredSizeOverride(NewGlowSize);
}

void UInv_SlottedItem::SetInventoryItem(UInv_InventoryItem* Item)
{
	InventoryItem = Item;
	if (!Item) return;
	SetItemData(
		Item->GetItemManifestMutable().GetItemRarity(),
		Item->GetItemManifestMutable().GetItemSpecialType(),
		Item->GetItemManifestMutable().GetItemEnhancement()
		);
}

void UInv_SlottedItem::SetImageBrush(const UTexture2D& Texture2D, const FVector2D& DrawSize) const
{
	CreateGlowDynamicMaterialInstance();
	Image_Glow->SetBrushFromMaterial(GlowDynamicMaterialInstance);

	CreateGlintDynamicMaterialInstance(Texture2D);
	
		FSlateBrush ItemBrush;
		ItemBrush.SetResourceObject(GlintDynamicMaterialInstance);
		ItemBrush.DrawAs = ESlateBrushDrawType::Image;
		ItemBrush.ImageSize = DrawSize;
	
	Image_Icon->SetBrush(ItemBrush);
}

void UInv_SlottedItem::CreateGlowDynamicMaterialInstance() const
{
	check(BaseGlowMaterial != nullptr);
	GlowDynamicMaterialInstance = UMaterialInstanceDynamic::Create(BaseGlowMaterial, nullptr);

	FInv_ItemGlowMaterialData Data = UInv_WidgetUtils::GetItemGlowData(ItemData);
	GlowDynamicMaterialInstance->SetVectorParameterValue(FName("Color"), Data.RarityColor);
	GlowDynamicMaterialInstance->SetScalarParameterValue(FName("God Ray Intensity"), Data.GodRayIntensity);
	GlowDynamicMaterialInstance->SetScalarParameterValue(FName("God Ray Pow"), Data.GodRayPow);
	GlowDynamicMaterialInstance->SetScalarParameterValue(FName("Distortion Glow"), Data.DistortionGlow);
	GlowDynamicMaterialInstance->SetScalarParameterValue(FName("Stars Brightness"), Data.StarsBrightness);
	GlowDynamicMaterialInstance->SetScalarParameterValue(FName("Prismatic Blend"), Data.PrismaticBlend);
	GlowDynamicMaterialInstance->SetScalarParameterValue(FName("Prismatic Intensity"), Data.PrismaticIntensity);
}

void UInv_SlottedItem::CreateGlintDynamicMaterialInstance(const UTexture2D& Texture2D) const
{
	check(BaseGlintMaterial != nullptr);
	GlintDynamicMaterialInstance = UMaterialInstanceDynamic::Create(BaseGlintMaterial, nullptr);

	FInv_ItemGlintMaterialData Data = UInv_WidgetUtils::GetItemGlintData(ItemData);
	GlintDynamicMaterialInstance->SetVectorParameterValue(FName("Color"), Data.GlintColor);
	GlintDynamicMaterialInstance->SetTextureParameterValue(FName("Mask"), const_cast<UTexture2D*>(&Texture2D));
	GlintDynamicMaterialInstance->SetTextureParameterValue(FName("Texture"), const_cast<UTexture2D*>(&Texture2D));
	GlintDynamicMaterialInstance->SetScalarParameterValue(FName("Color Opacity"), Data.ColorOpacity);
	GlintDynamicMaterialInstance->SetScalarParameterValue(FName("Prismatic Blend"), Data.PrismaticBlend);
}

void UInv_SlottedItem::UpdateStackCount(int32 StackCount) const
{
	if (StackCount > 0)
	{
		Text_StackCount->SetVisibility(ESlateVisibility::Visible);
		Text_StackCount->SetText(FText::AsNumber(StackCount));
	}
	else
	{
		Text_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInv_SlottedItem::SetItemData(EInv_ItemRarity Rarity, EInv_ItemSpecialType Type, EInv_ItemEnhancement Enhancement)
{
	ItemData.SpecialType = Type;
	ItemData.Enhancement = Enhancement;
	ItemData.Rarity = Rarity;
}
#pragma endregion
/*-------------------------------------------------------------------------*/