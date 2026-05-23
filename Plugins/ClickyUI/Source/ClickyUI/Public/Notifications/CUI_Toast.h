// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_Toast.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;

UENUM(BlueprintType)
enum class ECUI_ToastType : uint8
{
	Info    UMETA(DisplayName = "Info"),
	Success UMETA(DisplayName = "Success"),
	Warning UMETA(DisplayName = "Warning"),
	Error   UMETA(DisplayName = "Error"),
	Generic UMETA(DisplayName = "Generic")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Toast_OnDismissedEvent);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Toast.h_Class
UCLASS(Abstract)
class CLICKYUI_API UCUI_Toast : public UCUI_Widget
{
	GENERATED_BODY()

public:

	/** Broadcast when the toast finishes its dismiss animation and is ready to be removed. */
	UPROPERTY(BlueprintAssignable, Category = "Toast|Event")
	FCUI_Toast_OnDismissedEvent OnDismissed;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Message;

	/** How long (in seconds) the toast stays visible before auto-dismissing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toast|Defaults", meta = (ClampMin = "0.5"))
	float DisplayDuration = 3.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Toast")
	ECUI_ToastType ToastType = ECUI_ToastType::Info;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* Anim_Show;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* Anim_Dismiss;

	/** Called by CUI_Toast_Container after creation to configure this toast. */
	void Initialize(const FText& Message, ECUI_ToastType Type, float Duration);

	/** Manually trigger the dismiss sequence before the timer fires. */
	UFUNCTION(BlueprintCallable, Category = "Toast")
	void Dismiss();

protected:
	virtual void NativeConstruct() override;

private:
	FTimerHandle DisplayTimer;
	FTimerHandle DismissAnimTimer;

	UFUNCTION() void BeginDismiss();
	UFUNCTION() void FinalizeDismiss();
};
#pragma endregion
/*-------------------------------------------------------------------------*/
