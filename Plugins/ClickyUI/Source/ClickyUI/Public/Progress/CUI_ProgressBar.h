// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_ProgressBar.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UProgressBar;

UENUM(BlueprintType)
enum class ECUI_ProgressBarMode : uint8
{
	Determinate   UMETA(DisplayName = "Determinate"),
	Indeterminate UMETA(DisplayName = "Indeterminate")
};
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_ProgressBar.h_Class
UCLASS()
class CLICKYUI_API UCUI_ProgressBar : public UCUI_Widget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> UE_ProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress|Defaults")
	ECUI_ProgressBarMode Mode = ECUI_ProgressBarMode::Determinate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress|Defaults", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DefaultPercent = 0.0f;

	/* Played on loop while in Indeterminate mode. Bind this in your Widget Blueprint. */
	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* Anim_Indeterminate;

	UFUNCTION(BlueprintCallable, Category = "Progress")
	void SetPercent(float InPercent);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Progress")
	float GetPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Progress")
	void SetMode(ECUI_ProgressBarMode InMode);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Progress")
	ECUI_ProgressBarMode GetMode() const { return Mode; }

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	void ApplyMode();
};
#pragma endregion
/*-------------------------------------------------------------------------*/
