// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/HoverItem/Inv_HoverItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/Inv_InventoryItem.h"
#include "Widgets/Utils/Inv_WidgetUtils.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_HoverItem.cpp_Functions
void UInv_HoverItem::SetImageBrush(const UTexture2D& Texture2D, const FVector2D& DrawSize) const
{
	CreateGlintDynamicMaterialInstance(Texture2D);
	
	FSlateBrush ItemBrush;
	ItemBrush.SetResourceObject(GlintDynamicMaterialInstance);
	ItemBrush.DrawAs = ESlateBrushDrawType::Image;
	ItemBrush.ImageSize = DrawSize;
	
	Image_Icon->SetBrush(ItemBrush);
}

void UInv_HoverItem::UpdateStackCount(const int32 Count)
{
	StackCount = Count;
	if (Count > 0)
	{
		Text_StackCount->SetText(FText::AsNumber(Count));
		Text_StackCount->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Text_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

FGameplayTag UInv_HoverItem::GetItemType() const
{
	if (InventoryItem.IsValid())
	{
		return InventoryItem->GetItemManifest().GetItemType();
	}
	return FGameplayTag();
}

void UInv_HoverItem::SetIsStackable(bool bStacks)
{
	bIsStackable = bStacks;
	if (!bStacks)
	{
		Text_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

UInv_InventoryItem* UInv_HoverItem::GetInventoryItem() const
{
	return InventoryItem.Get();
}

void UInv_HoverItem::SetInventoryItem(UInv_InventoryItem* Item)
{
	InventoryItem = Item;
	if (!Item) return;
	SetItemData(
		Item->GetItemManifestMutable().GetItemRarity(),
		Item->GetItemManifestMutable().GetItemSpecialType(),
		Item->GetItemManifestMutable().GetItemEnhancement()
	);
}

void UInv_HoverItem::CreateGlintDynamicMaterialInstance(const UTexture2D& Texture2D) const
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

void UInv_HoverItem::SetItemData(EInv_ItemRarity Rarity, EInv_ItemSpecialType Type, EInv_ItemEnhancement Enhancement)
{
	ItemData.SpecialType = Type;
	ItemData.Enhancement = Enhancement;
	ItemData.Rarity = Rarity;
}
#pragma endregion
/*-------------------------------------------------------------------------*/

