// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Composite/Inv_CompositeBase.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_CompositeBase.cpp_Functions
void UInv_CompositeBase::Collapse()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UInv_CompositeBase::Expand()
{
	SetVisibility(ESlateVisibility::Visible);
}
#pragma endregion
/*-------------------------------------------------------------------------*/

