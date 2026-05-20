// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/NewItemDescription/Inv_ItemDescriptionCompositeBase.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemDescriptionCompositeBase.cpp_Functions
void UInv_ItemDescriptionCompositeBase::Collapse()
{
	SetVisibility(ESlateVisibility::Collapsed);	
}
void UInv_ItemDescriptionCompositeBase::Expand()
{
	SetVisibility(ESlateVisibility::Visible);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
