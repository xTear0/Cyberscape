// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Interaction/Inv_HighlightableStaticMesh.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_HighlightableStaticMesh.cpp_Functions
void UInv_HighlightableStaticMesh::Highlight_Implementation()
{
	IInv_Highlightable::Highlight_Implementation();

	SetOverlayMaterial(HighlightMaterial);
}

void UInv_HighlightableStaticMesh::UnHighlight_Implementation()
{
	IInv_Highlightable::UnHighlight_Implementation();

	SetOverlayMaterial(nullptr);
}
#pragma endregion
/*-------------------------------------------------------------------------*/