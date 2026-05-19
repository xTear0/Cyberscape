// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DS_UITheme.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_UITheme.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_UITheme : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FSlateColor GlobalWidgetOverlayColor;
	
	UPROPERTY(EditDefaultsOnly)
	FSlateColor HoveredTextColor;

	UPROPERTY(EditDefaultsOnly)
	FSlateColor UnhoveredTextColor;

	UPROPERTY(EditDefaultsOnly)	TObjectPtr<USoundBase> SFX_Error;
	UPROPERTY(EditDefaultsOnly)	TObjectPtr<USoundBase> SFX_Error_Critical;
	UPROPERTY(EditDefaultsOnly)	TObjectPtr<USoundBase> SFX_Success;
	UPROPERTY(EditDefaultsOnly)	TObjectPtr<USoundBase> SFX_Success_Super;
	UPROPERTY(EditDefaultsOnly)	TObjectPtr<USoundBase> SFX_NextStep;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<USoundBase> SFX_Click;
	UPROPERTY(EditDefaultsOnly)	TObjectPtr<USoundBase> SFX_Keyboard_Click;
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/