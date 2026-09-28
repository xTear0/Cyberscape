// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/TINV_SlottedItem.h"
#include "Components/TextBlock.h"
#include "Items/TINV_InventoryItem.h"
#include "Widgets/Inventory/Icons/TINV_GlintedIcon.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_SlottedItem.cpp_Functions
void UTINV_SlottedItem::SetInventoryItem(UTINV_InventoryItem* Item)
{
	InventoryItem = Item;
}

void UTINV_SlottedItem::UpdateStackCount(int32 StackCount) const
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

void UTINV_SlottedItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	DefaultStackTextColor = Text_StackCount->GetColorAndOpacity();
}

void UTINV_SlottedItem::SetPreview(const bool bPreview) const
{
	GetGlintedIcon()->SetRenderOpacity(bPreview ? PreviewIconOpacity : 1.f);
	Text_StackCount->SetColorAndOpacity(bPreview ? PreviewStackTextColor : DefaultStackTextColor);
}
#pragma endregion
/*-------------------------------------------------------------------------*/