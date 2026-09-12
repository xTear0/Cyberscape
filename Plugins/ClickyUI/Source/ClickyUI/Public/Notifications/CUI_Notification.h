// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "Notifications/CUI_NotificationTypes.h"
#include "CUI_Notification.generated.h"
/*-------------------------------------------------------------------------*/


class UCUI_NotificationCounter;
/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;
class UImage;

DECLARE_DELEGATE_OneParam(FCUIOnNotificationHideFinished, class UCUI_Notification*);
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region CUI_Notification.h_Class
UCLASS()
class CLICKYUI_API UCUI_Notification : public UCUI_Widget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    /** Play the entrance animation (slide-in / grow). */
    UFUNCTION(BlueprintImplementableEvent, Category = "CUI|Events")
    void NotificationShow();

    /** Play the exit animation. MUST end by calling NotifyHideFinished. */
    UFUNCTION(BlueprintImplementableEvent, Category = "CUI|Events")
    void NotificationHide();

    /** Content landed or refreshed. Handle icon override, per-type styling, and the xN counter here. */
    UFUNCTION(BlueprintImplementableEvent, Category = "CUI|Events")
    void OnNotificationSet(const FCUIActiveNotification& Entry);

    /** Call from Blueprint when the hide animation has finished playing. */
    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications")
    void NotifyHideFinished();

    void SetNotification(const FCUIActiveNotification& Entry);

    int32 GetNotificationId() const { return CurrentEntry.Id; }

    /** The stack binds this to reclaim the widget after its hide animation. */
    FCUIOnNotificationHideFinished OnHideFinished;

protected:

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCUI_NotificationCounter> Counter;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CUI|Widgets")
    TObjectPtr<UTextBlock> Text_Message;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CUI|Widgets")
    TObjectPtr<UImage> Image_Icon;

private:

    FCUIActiveNotification CurrentEntry;

};
#pragma endregion
/*-------------------------------------------------------------------------*/