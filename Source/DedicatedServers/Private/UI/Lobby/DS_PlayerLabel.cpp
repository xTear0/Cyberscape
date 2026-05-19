// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Lobby/DS_PlayerLabel.h"
#include "Components/TextBlock.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_PlayerLabel.cpp_Functions
void UDS_PlayerLabel::SetUsername(const FString& Username) const
{
	TextBlock_Username->SetText(FText::FromString(Username));
}

FString UDS_PlayerLabel::GetUsername() const
{
	return TextBlock_Username->GetText().ToString();
}
#pragma endregion
/*-------------------------------------------------------------------------*/

