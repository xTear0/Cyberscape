// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Subsystems/AttributeHoverSubsystem.h"
#include "Engine/World.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region AttributeHoverSubsystem.cpp_Functions

void UAttributeHoverSubsystem::BroadcastAttributeHover(bool bShow, FGameplayTag AttributeTag)
{
	OnAttributeHoverChanged.Broadcast(bShow, AttributeTag);
}

UAttributeHoverSubsystem* UAttributeHoverSubsystem::Get(const UObject* WorldContext)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (UGameInstance* GameInstance = World->GetGameInstance())
		{
			return GameInstance->GetSubsystem<UAttributeHoverSubsystem>();
		}
	}
	return nullptr;
}

#pragma endregion
/*-------------------------------------------------------------------------*/