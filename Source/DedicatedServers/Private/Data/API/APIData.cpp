// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Data/API/APIData.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_APITestManager.cpp_Functions
FString UAPIData::GetAPIEndpoint(const FGameplayTag& APIEndpoint)
{
	const FString ResourceName = Resources.FindChecked(APIEndpoint);
	return InvokeURL + "/" + Stage + "/" + ResourceName;
}
#pragma endregion
/*-------------------------------------------------------------------------*/

