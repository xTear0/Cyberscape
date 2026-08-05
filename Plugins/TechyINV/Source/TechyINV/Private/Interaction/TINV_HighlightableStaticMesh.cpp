// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Interaction/TINV_HighlightableStaticMesh.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_HighlightableStaticMesh.cpp_Functions
void UTINV_HighlightableStaticMesh::Highlight_Implementation()
{
	ITINV_Highlightable::Highlight_Implementation();
	SetOverlayMaterial(HighlightMaterial);
}

void UTINV_HighlightableStaticMesh::UnHighlight_Implementation()
{
	ITINV_Highlightable::UnHighlight_Implementation();
	SetOverlayMaterial(nullptr);
}
#pragma endregion
/*-------------------------------------------------------------------------*/
