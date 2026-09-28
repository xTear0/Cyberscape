// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/HoverItem/TINV_HoverItem.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Items/TINV_InventoryItem.h"
#include "Widgets/Inventory/Icons/TINV_GlintedIcon.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_HoverItem.cpp_Functions
void UTINV_HoverItem::SetInventoryItem(UTINV_InventoryItem* Item)
{
	InventoryItem = Item;
}

void UTINV_HoverItem::UpdateStackCount(const int32 NewStackCount)
{
	StackCount = NewStackCount;

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

void UTINV_HoverItem::SetDisplaySize(const float Size)
{
	SizeBox_Root->SetWidthOverride(Size);
	SizeBox_Root->SetHeightOverride(Size);
}

#pragma endregion
/*-------------------------------------------------------------------------*/