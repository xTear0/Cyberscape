// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/ItemDescription/Inv_ItemDescription.h"
#include "Components/SizeBox.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_InventoryComponent.cpp_Functions
FVector2D UInv_ItemDescription::GetBoxSize() const
{
	return SizeBox->GetDesiredSize();
}

void UInv_ItemDescription::SetVisibility(ESlateVisibility InVisibility)
{
	for (auto Child : GetChildren())
	{
		Child->Collapse();
	}
	Super::SetVisibility(InVisibility);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
