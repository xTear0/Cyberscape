// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"

#include "InputState.h"
#include "Items/Inv_InventoryItem.h"
#include "Widgets/ItemPopUp/Inv_ItemPopUp.h"
#include "Components/Image.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_GridSlot.cpp_Functions
void UInv_GridSlot::NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseEnter(MyGeometry, MouseEvent);
	GridSlotHovered.Broadcast(TileIndex, MouseEvent);
}

void UInv_GridSlot::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseLeave(MouseEvent);
	GridSlotUnHovered.Broadcast(TileIndex, MouseEvent);
}

FReply UInv_GridSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& MouseEvent)
{
	GridSlotClicked.Broadcast(TileIndex, MouseEvent);
	return FReply::Handled();
}

void UInv_GridSlot::SetInventoryItem(UInv_InventoryItem* Item)
{
	InventoryItem = Item;
}

void UInv_GridSlot::SetItemPopUp(UInv_ItemPopUp* PopUp)
{
	ItemPopUp = PopUp;
	ItemPopUp->SetGridIndex(GetIndex());
	ItemPopUp->OnNativeDestruct.AddUObject(this, &ThisClass::OnItemPopUpDestruct);
}

UInv_ItemPopUp* UInv_GridSlot::GetItemPopUp() const
{
	return ItemPopUp.Get();
}

void UInv_GridSlot::SetOccupiedTexture(const FLinearColor& OverlayColor)
{
	GridSlotState = EInv_GridSlotState::Occupied;
	if (OverlayColor != FLinearColor::White) Image_GridSlot->SetColorAndOpacity(OverlayColor);
	Image_GridSlot->SetBrush(Brush_Occupied);
}

void UInv_GridSlot::SetUnoccupiedTexture()
{
	GridSlotState = EInv_GridSlotState::Unoccupied;
	Image_GridSlot->SetColorAndOpacity(FLinearColor::White);
	Image_GridSlot->SetBrush(Brush_Unoccupied);
}

void UInv_GridSlot::SetSelectedTexture()
{
	GridSlotState = EInv_GridSlotState::Selected;
	Image_GridSlot->SetBrush(Brush_Selected);
}

void UInv_GridSlot::SetGrayedOutTexture()
{
	GridSlotState = EInv_GridSlotState::GrayedOut;
	Image_GridSlot->SetBrush(Brush_GrayedOut);
}

void UInv_GridSlot::OnItemPopUpDestruct(UUserWidget* Menu)
{
	ItemPopUp.Reset();
}
#pragma endregion
/*-------------------------------------------------------------------------*/