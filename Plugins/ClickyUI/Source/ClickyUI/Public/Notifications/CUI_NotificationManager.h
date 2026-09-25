// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "Notifications/CUI_NotificationTypes.h"
#include "CUI_NotificationManager.generated.h"
/*-------------------------------------------------------------------------*/


class UTexture2D;

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

    /*--- One-line global posts -------------------------------------------*/
    /*  Pass `this` as WorldContextObject from any actor, component, or widget.
     *  bCoalesce merges repeats of the same message text into a counter.     */

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "NotifIcon, LifetimeOverride"))
    static void PostInfo(const UObject* WorldContextObject, const FText& NotifMessage, bool bCoalesce = false, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "NotifIcon, LifetimeOverride"))
    static void PostItem(const UObject* WorldContextObject, const FText& NotifMessage, bool bCoalesce = false, UTexture2D* NotifIcon = nullptr, ECUI_ItemTier ItemTier = ECUI_ItemTier::None, float LifetimeOverride = -1.f);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "NotifIcon, LifetimeOverride"))
    static void PostWarning(const UObject* WorldContextObject, const FText& NotifMessage, bool bCoalesce = false, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "NotifIcon, LifetimeOverride"))
    static void PostSuccess(const UObject* WorldContextObject, const FText& NotifMessage, bool bCoalesce = false, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "NotifIcon, LifetimeOverride"))
    static void PostError(const UObject* WorldContextObject, const FText& NotifMessage, bool bCoalesce = false, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "NotifIcon, LifetimeOverride"))
    static void PostSocial(const UObject* WorldContextObject, const FText& NotifMessage, bool bCoalesce = false, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "NotifIcon, LifetimeOverride"))
    static void PostAchievement(const UObject* WorldContextObject, const FText& NotifMessage, bool bCoalesce = false, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f);

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "NotifIcon, LifetimeOverride"))
    static void PostEvent(const UObject* WorldContextObject, const FText& NotifMessage, bool bCoalesce = false, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f);

    /*--- Instance API ------------------------------------------------------*/
    /*  Use these when you need an explicit coalesce key, or to target a
     *  specific local player (splitscreen).                                  */

    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications", meta = (AdvancedDisplay = "NotifIcon, LifetimeOverride, CoalesceKey"))
    void PostNotification(ECUINotificationType NotifType, const FText& NotifMessage, UTexture2D* NotifIcon = nullptr, float LifetimeOverride = -1.f, FName CoalesceKey = NAME_None, const FLinearColor TextColor = FLinearColor::Transparent, const ECUI_ItemTier ItemTier = ECUI_ItemTier::None);

    /** Full-payload entry point, for callers that build the struct themselves. */
    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications")
    void PostNotificationPayload(const FCUINotificationPayload& Payload);

    /** Dismiss a visible notification early (e.g. player clicked it). */
    UFUNCTION(BlueprintCallable, Category = "CUI|Notifications")
    void DismissNotification(int32 NotificationId);

    /*--- Queries -----------------------------------------------------------*/

    /** Works from anywhere with a world context: menus, actors, components, widgets. */
    UFUNCTION(BlueprintPure, Category = "CUI|Notifications", meta = (WorldContext = "WorldContextObject"))
    static UCUI_NotificationManager* Get(const UObject* WorldContextObject);

    const TArray<FCUIActiveNotification>& GetActiveNotifications() const { return ActiveNotifications; }

    UFUNCTION(BlueprintPure, Category = "CUI|Notifications")
    int32 GetQueuedCount() const { return QueuedNotifications.Num(); }

    /** Baked per-type defaults. LifetimeOverride on a payload beats this. */
    UFUNCTION(BlueprintPure, Category = "CUI|Notifications")
    static float GetDefaultLifetimeFor(ECUINotificationType Type);

    /** Baked per-type sort priority. Lower = closer to the stack anchor. */
    UFUNCTION(BlueprintPure, Category = "CUI|Notifications")
    static int32 GetPriorityFor(ECUINotificationType Type);

protected:

private:
    static void PostStatic(const UObject* WorldContextObject, ECUINotificationType NotifType, const FText& NotifMessage, bool bCoalesce, UTexture2D* NotifIcon, float LifetimeOverride, const FLinearColor TextColor = FLinearColor::White, const ECUI_ItemTier ItemTier = ECUI_ItemTier::None);

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