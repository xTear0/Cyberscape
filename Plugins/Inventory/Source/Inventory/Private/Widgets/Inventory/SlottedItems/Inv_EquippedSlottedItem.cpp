// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/SlottedItems/Inv_EquippedSlottedItem.h"
#include "Components/Image.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions			                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_EquippedSlottedItem.cpp_Functions
FReply UInv_EquippedSlottedItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	OnEquippedSlottedItemClicked.Broadcast(this);
	return FReply::Handled();
}

void UInv_EquippedSlottedItem::SetImageBrush(const UTexture2D& Texture2D, const FVector2D& DrawSize)
{
	Super::SetImageBrush(Texture2D, DrawSize);
	SetWidgetSize();
}

void UInv_EquippedSlottedItem::SetWidgetSize()
{
	FVector2D WidgetSize = GetImageIconSize();
	SetGlowSize(WidgetSize);
	
	FMargin ItemMargin;
		ItemMargin.Bottom = WidgetSize.Y * -1.5f;
		ItemMargin.Top = WidgetSize.Y * -0.5f;
		ItemMargin.Left = WidgetSize.X * -0.5f;
		ItemMargin.Right = WidgetSize.X * -1.5f;
	SetPadding(ItemMargin);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
