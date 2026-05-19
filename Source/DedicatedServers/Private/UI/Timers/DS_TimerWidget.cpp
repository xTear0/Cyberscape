// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Timers/DS_TimerWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetStringLibrary.h"
#include "Player/DS_PlayerController.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_TimerWidget.cpp_Functions
void UDS_TimerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	OwningPlayerController = Cast<ADS_PlayerController>(GetOwningPlayer());
	if (IsValid(OwningPlayerController))
	{
		OwningPlayerController->OnTimerUpdated.AddDynamic(this, &UDS_TimerWidget::OnTimerUpdated);
		OwningPlayerController->OnTimerStopped.AddDynamic(this, &UDS_TimerWidget::OnTimerStopped);
	}

	if (bHiddenWhenInactive)
	{
		TextBlock_Time->SetRenderOpacity(0.f);
	}
}

void UDS_TimerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bActive)
	{
		float NewTime = InternalCountdown - InDeltaTime;
		UpdateCountdown(NewTime);
	}
}

void UDS_TimerWidget::OnTimerUpdated(float CountdownTimeLeft, EDS_CountdownTimerType Type)
{
	if (Type != TimerType) return;

	if (!bActive)
	{
		TimerStarted(CountdownTimeLeft);
	}
	UpdateCountdown(CountdownTimeLeft);
	K2_OnTimerUpdated(CountdownTimeLeft, TimerType);
}

void UDS_TimerWidget::OnTimerStopped(float CountdownTimeLeft, EDS_CountdownTimerType Type)
{
	if (Type != TimerType) return;
	TimerStopped();
	K2_OnTimerStopped(CountdownTimeLeft, TimerType);
}

FString UDS_TimerWidget::FormatTimeAsString(float TimeSeconds) const
{
	TimeSeconds = bCanBeNegative ? TimeSeconds : FMath::Abs(TimeSeconds);
	FString DisplayTimeString;
	if (bShowCentiSeconds)
	{
		DisplayTimeString = UKismetStringLibrary::TimeSecondsToString(TimeSeconds);
	} else
	{
		const TCHAR* NegativeModifier = TimeSeconds < 0.f? TEXT("-") : TEXT("");
		TimeSeconds = FMath::Abs(TimeSeconds);
		
		const int32 NumMinutes = FMath::FloorToInt(TimeSeconds/60.f);
		const int32 NumSeconds = FMath::FloorToInt(TimeSeconds-(NumMinutes*60.f));
		
		DisplayTimeString = FString::Printf(TEXT("%s%02d:%02d"), NegativeModifier, NumMinutes, NumSeconds);
	}
	
	return DisplayTimeString;
}

void UDS_TimerWidget::TimerStarted(float InitialTime)
{
	bActive = true;
	TextBlock_Time->SetRenderOpacity(1.f);
	K2_OnTimerStarted(InitialTime, TimerType);
}

void UDS_TimerWidget::TimerStopped()
{
	bActive = false;
	UpdateCountdown(0.f);
	if (bHiddenWhenInactive)
	{
		TextBlock_Time->SetRenderOpacity(0.f);
	}
}

void UDS_TimerWidget::UpdateCountdown(float TimeSeconds)
{
	InternalCountdown = TimeSeconds;
	const FText TimeText = FText::FromString(FormatTimeAsString(InternalCountdown));
	TextBlock_Time->SetText(TimeText);
}
#pragma endregion
/*-------------------------------------------------------------------------*/

