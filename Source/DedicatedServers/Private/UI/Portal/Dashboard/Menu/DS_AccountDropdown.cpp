// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/Dashboard/Menu/DS_AccountDropdown.h"
#include "Components/TextBlock.h"
#include "Player/DS_LocalPlayerSubsystem.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_AccountDropdown.cpp_Functions
void UDS_AccountDropdown::NativeConstruct()
{
	Super::NativeConstruct();

	UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = GetLocalPlayerSubsystem();
	if (IsValid(LocalPlayerSubsystem))
	{
		TextBlock_ButtonText->SetText(FText::FromString(LocalPlayerSubsystem->Username));
	}
}

UDS_LocalPlayerSubsystem* UDS_AccountDropdown::GetLocalPlayerSubsystem() const
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (IsValid(PlayerController) && IsValid(PlayerController->GetLocalPlayer()))
	{
		UDS_LocalPlayerSubsystem* LocalPlayerSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UDS_LocalPlayerSubsystem>();
		if (IsValid(LocalPlayerSubsystem))
		{
			return LocalPlayerSubsystem;
		}
	}
	return nullptr;
}
#pragma endregion
/*-------------------------------------------------------------------------*/
