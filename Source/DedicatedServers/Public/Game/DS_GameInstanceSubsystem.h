// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#if WITH_GAMELIFT
#include "GameLiftServerSDK.h"
#include "GameLiftServerSDKModels.h"
#endif
#include "DS_GameInstanceSubsystem.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_GameInstanceSubsystem.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_GameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UDS_GameInstanceSubsystem();

	UPROPERTY(BlueprintReadOnly)
	bool bGameLiftInitialized;
	
#if WITH_GAMELIFT
	void InitGameLift(const FServerParameters& ServerParameters);
	
	/* Process Parameters needs to remain in scope for the lifetime of the app.
	Hence, why this is a member variable. Feel free to peak the definition to
	see exactly what this is doing and how it works. */
	TSharedPtr<FProcessParameters> ProcessParameters;
#endif
};
#pragma endregion
/*-------------------------------------------------------------------------*/