// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "Notifications/CUI_Toast.h"
#include "CUI_Toast_Container.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UVerticalBox;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Toast_Container.h_Class
UCLASS()
class CLICKYUI_API UCUI_Toast_Container : public UCUI_Widget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Toasts;

	/** The Widget Blueprint subclass of CUI_Toast to instantiate for each notification. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toast")
	TSubclassOf<UCUI_Toast> ToastClass;

	/** Maximum number of toasts visible at once. Oldest is removed when the limit is exceeded. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toast", meta = (ClampMin = "1"))
	int32 MaxToasts = 3;

	/**
	 * Spawn and display a toast notification.
	 * @param Message    Text shown on the toast.
	 * @param Type       Visual category (Info / Success / Warning / Error / Generic).
	 * @param Duration   How long the toast stays visible before auto-dismissing (seconds).
	 */
	UFUNCTION(BlueprintCallable, Category = "Toast")
	void ShowToast(const FText& Message, ECUI_ToastType Type = ECUI_ToastType::Info, float Duration = 3.0f);

private:
	UPROPERTY()
	TArray<TObjectPtr<UCUI_Toast>> ActiveToasts;

	// Called by each toast's OnDismissed broadcast; scans for toasts removed from the hierarchy.
	UFUNCTION() void HandleToastDismissed();
};
#pragma endregion
/*-------------------------------------------------------------------------*/
