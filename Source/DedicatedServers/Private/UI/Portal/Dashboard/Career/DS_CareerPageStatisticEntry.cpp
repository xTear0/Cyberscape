// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/Dashboard/Career/DS_CareerPageStatisticEntry.h"

#include "Components/TextBlock.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_CareerStatisticEntry.cpp_Functions
void UDS_CareerPageStatisticEntry::SetStatisticText(const FString& StatisticName, int32 StatisticValue)
{
	TextBlock_StatisticName->SetText(FText::FromString(StatisticName));
	TextBlock_StatisticValue->SetText(FText::AsNumber(StatisticValue));	
}
#pragma endregion
/*-------------------------------------------------------------------------*/

