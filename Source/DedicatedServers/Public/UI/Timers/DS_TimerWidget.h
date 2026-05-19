// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/DS_EnumTypes.h"
#include "DS_TimerWidget.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class ADS_PlayerController;
class UTextBlock;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_TimerWidget.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_TimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	EDS_CountdownTimerType TimerType = EDS_CountdownTimerType::None;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ADS_PlayerController> OwningPlayerController;

	UPROPERTY(BlueprintReadOnly)
	bool bActive = false;

	UPROPERTY(EditDefaultsOnly)
	bool bCanBeNegative = false;

	UPROPERTY(EditDefaultsOnly)
	bool bShowCentiSeconds = true;

	UPROPERTY(EditDefaultsOnly)
	bool bHiddenWhenInactive = true;
	
	UFUNCTION()
	virtual void OnTimerUpdated(float CountdownTimeLeft, EDS_CountdownTimerType Type);

	UFUNCTION()
	virtual void OnTimerStopped(float CountdownTimeLeft, EDS_CountdownTimerType Type);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Timer Updated"))
	void K2_OnTimerUpdated(float CountdownTimeLeft, EDS_CountdownTimerType Type);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Timer Started"))
	void K2_OnTimerStarted(float CountdownTimeLeft, EDS_CountdownTimerType Type);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Timer Stopped"))
	void K2_OnTimerStopped(float CountdownTimeLeft, EDS_CountdownTimerType Type);
	
	FString FormatTimeAsString(float TimeSeconds) const;
	
private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Time;

	float InternalCountdown;

	void TimerStarted(float InitialTime);
	void TimerStopped();
	void UpdateCountdown(float TimeSeconds);
};
#pragma endregion
/*-------------------------------------------------------------------------*/