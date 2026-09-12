// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_NotificationCounter.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region CUI_NotificationCoalesceCounter.h_Class
UCLASS

()
class CLICKYUI_API UCUI_NotificationCounter : public UCUI_Widget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "CUI|Events")
	void OnCountUpdated();

	UFUNCTION(BlueprintCallable)
	void SetCount(const int32 StackCount);
	
	UFUNCTION(BlueprintCallable)
	int32 GetCount() {return Count;}

	UPROPERTY(EditAnywhere, Category = "CUI|Defaults")
	FText Prefix;
	
	UPROPERTY(EditAnywhere, Category = "CUI|Defaults")
	FText Suffix;
	
private:
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentCount;

	int32 Count{0};
};
#pragma endregion
/*-------------------------------------------------------------------------*/
