// Copyright xTear Studios
/*-------------------------------------------------------------------------*/

#include "Widgets/Utils/TINV_WidgetUtils.h"

/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_WidgetUtils.cpp_Functions
int32 UTINV_WidgetUtils::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{	  
	return Position.X + Position.Y * Columns;
}
#pragma endregion
/*-------------------------------------------------------------------------*/
