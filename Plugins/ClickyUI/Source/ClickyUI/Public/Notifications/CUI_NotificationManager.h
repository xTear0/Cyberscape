// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "Notifications/CUI_NotificationTypes.h"
#include "CUI_NotificationManager.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region CUI_NotificationManager.h_Class
UCLASS(Config = Game)
class CLICKYUI_API UCUI_NotificationManager : public ULocalPlayerSubsystem
{
    GENERATED_BODY()

public:
    virtual void Deinitialize() override;

    /*--- Stack widget binds to these -------------------------------------*/

    /** A notification entered the visible stack. Spawn a widget at InsertIndex. */
    UPROPERTY(BlueprintAssignable, Category = "CUI|Notifications")
    FCUIOnNotificationActivated OnNotificationActivated;

    /** A visible notification coalesced (Count changed, lifetime restarted). */
    UPROPERTY(BlueprintAssignable, Category = "CUI|Notifications")
    FCUIOnNotificationRefreshed OnNotificationRefreshed;

    /** A visible notification expired. Play the hide animation and release the widget. */
    UPROPERTY(BlueprintAssignable, Category = "CUI|Notifications")
    FCUIOnNotificationDismissed OnNotificationDismissed;

    /** Overflow queue depth changed. Drive a "+N more" counter with this. */
    UPROPERTY(BlueprintAssignable, Category = "CUI|Notifications")
    FCUIOnNotificationQueueChanged OnQueueChanged;

    /*--- Gameplay-facing API ---------------------------------------------*/

    /** Fire-and-forget entry point. Icon, lifetime, and coalescing are optional. */
    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (AdvancedDisplay = "NotifIcon, LifetimeOverride, CoalesceKey"))
    void PostNotification(ECUINotificationType NotifType, const FText& NotifMessage, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f, FName CoalesceKey = NAME_None);

    /** Full-payload entry point, for callers that build the struct themselves. */
    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications")
    void PostNotificationPayload(const FCUINotificationPayload& Payload);

    /*--- Typed conveniences ----------------------------------------------*/

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (AdvancedDisplay = "NotifIcon, LifetimeOverride, CoalesceKey"))
    void PostInfo(const FText& NotifMessage, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f, FName CoalesceKey = NAME_None);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (AdvancedDisplay = "NotifIcon, LifetimeOverride, CoalesceKey"))
    void PostItem(const FText& NotifMessage, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f, FName CoalesceKey = NAME_None);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (AdvancedDisplay = "NotifIcon, LifetimeOverride, CoalesceKey"))
    void PostWarning(const FText& NotifMessage, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f, FName CoalesceKey = NAME_None);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (AdvancedDisplay = "NotifIcon, LifetimeOverride, CoalesceKey"))
    void PostError(const FText& NotifMessage, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f, FName CoalesceKey = NAME_None);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (AdvancedDisplay = "NotifIcon, LifetimeOverride, CoalesceKey"))
    void PostSocial(const FText& NotifMessage, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f, FName CoalesceKey = NAME_None);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (AdvancedDisplay = "NotifIcon, LifetimeOverride, CoalesceKey"))
    void PostAchievement(const FText& NotifMessage, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f, FName CoalesceKey = NAME_None);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (AdvancedDisplay = "NotifIcon, LifetimeOverride, CoalesceKey"))
    void PostEvent(const FText& NotifMessage, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f, FName CoalesceKey = NAME_None);

    /*----------------------------------------------------------------------*/
    
    UFUNCTION(BlueprintPure, Category = "CUI|Notifications")
    const TArray<FCUIActiveNotification>& GetActiveNotifications() const { return ActiveNotifications; }

    /** Baked per-type defaults. LifetimeOverride on a payload beats this. */
    UFUNCTION(BlueprintPure, Category = "CUI|Notifications")
    static float GetDefaultLifetimeFor(ECUINotificationType Type);

    /** Baked per-type sort priority. Lower = closer to the stack anchor. */
    UFUNCTION(BlueprintPure, Category = "CUI|Notifications")
    static int32 GetPriorityFor(ECUINotificationType Type);

    /** Convenience accessor: UCUI_NotificationManager::Get(PC)->PostWarning(...) */
    static UCUI_NotificationManager* Get(const APlayerController* PlayerController);

protected:

private:
    void ActivateNotification(const FCUINotificationPayload& Payload, int32 InitialCount);
    void EnqueueNotification(const FCUINotificationPayload& Payload);
    void HandleNotificationExpired(int32 NotificationId);
    void TryDequeue();

    int32 FindActiveIndexById(int32 NotificationId) const;

    TArray<FCUIActiveNotification> ActiveNotifications;

    /** Payload + accumulated count for entries waiting on a free slot. */
    TArray<FCUIActiveNotification> QueuedNotifications;

    TMap<FName, int32> CoalesceKeyToActiveId;

    TMap<int32, FTimerHandle> LifetimeTimerHandles;

    FTimerHandle DequeueTimerHandle;

    int32 NextNotificationId{0};

    /** How many notifications may be on screen at once; the rest queue. Config-overridable. */
    UPROPERTY(Config)
    int32 MaxVisibleNotifications{5};

    /** Breather between a dismissal and the next queued entry spawning. Config-overridable. */
    UPROPERTY(Config)
    float DequeueDelay{0.1f};

};
#pragma endregion
/*-------------------------------------------------------------------------*/