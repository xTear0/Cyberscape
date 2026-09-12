// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_TextStatusNotification.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region CUI_TextStatusNotification.h_Class
UCLASS

()
class CLICKYUI_API UCUI_TextStatusNotification : public UCUI_Widget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "CUI|Events")
	void MessageShow();

	UFUNCTION(BlueprintImplementableEvent, Category = "CUI|Events")
	void MessageHide();

	void SetMessage(const FText& Message);
	
protected:

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Message;

	UPROPERTY(EditAnywhere, Category = "CUI|Defaults")
	float MessageLifetime{3.f};

	FTimerHandle MessageTimerHandle;

	bool bIsMessageActive{false};
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/
