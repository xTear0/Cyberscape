// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "Notifications/CUI_NotificationTypes.h"
#include "CUI_NotificationStack.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UVerticalBox;
class UCUI_NotificationCounter;
class UCUI_Notification;
class UCUI_NotificationManager;

/** Wrapper so pools can be stored per widget class (nested containers are not UPROPERTY-legal). */
USTRUCT()
struct FCUINotificationWidgetPool
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<TObjectPtr<UCUI_Notification>> Widgets;
};
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region CUI_NotificationStack.h_Class
UCLASS()
class CLICKYUI_API UCUI_NotificationStack : public UCUI_Widget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

protected:

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CUI|Widgets")
    TObjectPtr<UVerticalBox> VerticalBox_Stack;

    /** "+N more" readout for the overflow queue. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "CUI|Widgets")
    TObjectPtr<UCUI_NotificationCounter> OverflowCounter;

    /** Fallback entry widget for types that are not present in NotificationWidgetClasses. */
    UPROPERTY(EditAnywhere, Category = "CUI|Defaults")
    TSubclassOf<UCUI_Notification> DefaultNotificationWidgetClass;

    /** Per-type entry widgets with preset icons/styling. Unlisted types use the default. */
    UPROPERTY(EditAnywhere, Category = "CUI|Defaults")
    TMap<ECUINotificationType, TSubclassOf<UCUI_Notification>> NotificationWidgetClasses;

    /**
     * Per-rarity entry widgets. Checked first whenever a payload carries a tier other than None.
     * Unlisted tiers fall back to NotificationWidgetClasses, then DefaultNotificationWidgetClass.
     */
    UPROPERTY(EditAnywhere, Category = "CUI|Defaults")
    TMap<ECUI_ItemTier, TSubclassOf<UCUI_Notification>> ItemTierWidgetClasses;

    /** Widgets pre-created per class up front; pools grow on demand past this. */
    UPROPERTY(EditAnywhere, Category = "CUI|Defaults", meta = (ClampMin = "0"))
    int32 InitialPoolSizePerClass{3};

private:

    /*--- Manager delegate handlers ---------------------------------------*/
    UFUNCTION()
    void HandleNotificationActivated(const FCUIActiveNotification& Entry, int32 InsertIndex);

    UFUNCTION()
    void HandleNotificationRefreshed(const FCUIActiveNotification& Entry);

    UFUNCTION()
    void HandleNotificationDismissed(int32 NotificationId);

    UFUNCTION()
    void HandleQueueChanged(int32 QueuedCount);

    /*--- Pooling ----------------------------------------------------------*/
    TSubclassOf<UCUI_Notification> ResolveWidgetClass(ECUINotificationType Type, ECUI_ItemTier ItemTier) const;
    UCUI_Notification* AcquireWidget(ECUINotificationType Type, ECUI_ItemTier ItemTier);
    UCUI_Notification* CreatePooledWidget(TSubclassOf<UCUI_Notification> WidgetClass);
    void HandleWidgetHideFinished(UCUI_Notification* Widget);

    UCUI_NotificationManager* GetManager() const;

    /** Idle widgets awaiting reuse, keyed by widget class. */
    UPROPERTY()
    TMap<TSubclassOf<UCUI_Notification>, FCUINotificationWidgetPool> WidgetPools;

    /** Live widgets keyed by notification id. */
    UPROPERTY()
    TMap<int32, TObjectPtr<UCUI_Notification>> ActiveWidgets;

};
#pragma endregion
/*-------------------------------------------------------------------------*/