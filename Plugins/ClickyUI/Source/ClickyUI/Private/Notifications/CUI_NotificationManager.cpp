// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Notifications/CUI_NotificationManager.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "TimerManager.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region CUI_NotificationManager.cpp_Functions
void UCUI_NotificationManager::Deinitialize()
{
    if (const UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearAllTimersForObject(this);
    }

    Super::Deinitialize();
}

void UCUI_NotificationManager::PostNotification(const ECUINotificationType NotifType, const FText& NotifMessage, UTexture2D* NotifIcon, const float LifetimeOverride, const FName CoalesceKey)
{
    FCUINotificationPayload Payload;
    Payload.Type = NotifType;
    Payload.Message = NotifMessage;
    Payload.IconOverride = NotifIcon;
    Payload.LifetimeOverride = LifetimeOverride;
    Payload.CoalesceKey = CoalesceKey;

    PostNotificationPayload(Payload);
}

void UCUI_NotificationManager::PostInfo(const FText& NotifMessage, UTexture2D* NotifIcon, const float LifetimeOverride, const FName CoalesceKey)
{
    PostNotification(ECUINotificationType::Info, NotifMessage, NotifIcon, LifetimeOverride, CoalesceKey);
}

void UCUI_NotificationManager::PostItem(const FText& NotifMessage, UTexture2D* NotifIcon, const float LifetimeOverride, const FName CoalesceKey)
{
    PostNotification(ECUINotificationType::Item, NotifMessage, NotifIcon, LifetimeOverride, CoalesceKey);
}

void UCUI_NotificationManager::PostWarning(const FText& NotifMessage, UTexture2D* NotifIcon, const float LifetimeOverride, const FName CoalesceKey)
{
    PostNotification(ECUINotificationType::Warning, NotifMessage, NotifIcon, LifetimeOverride, CoalesceKey);
}

void UCUI_NotificationManager::PostError(const FText& NotifMessage, UTexture2D* NotifIcon, const float LifetimeOverride, const FName CoalesceKey)
{
    PostNotification(ECUINotificationType::Error, NotifMessage, NotifIcon, LifetimeOverride, CoalesceKey);
}

void UCUI_NotificationManager::PostSocial(const FText& NotifMessage, UTexture2D* NotifIcon, const float LifetimeOverride, const FName CoalesceKey)
{
    PostNotification(ECUINotificationType::Social, NotifMessage, NotifIcon, LifetimeOverride, CoalesceKey);
}

void UCUI_NotificationManager::PostAchievement(const FText& NotifMessage, UTexture2D* NotifIcon, const float LifetimeOverride, const FName CoalesceKey)
{
    PostNotification(ECUINotificationType::Achievement, NotifMessage, NotifIcon, LifetimeOverride, CoalesceKey);
}

void UCUI_NotificationManager::PostEvent(const FText& NotifMessage, UTexture2D* NotifIcon, const float LifetimeOverride, const FName CoalesceKey)
{
    PostNotification(ECUINotificationType::Event, NotifMessage, NotifIcon, LifetimeOverride, CoalesceKey);
}

void UCUI_NotificationManager::PostNotificationPayload(const FCUINotificationPayload& Payload)
{
    // 1) Coalesce onto a visible entry: bump the counter, restart the clock.
    if (!Payload.CoalesceKey.IsNone())
    {
        if (const int32* ActiveId = CoalesceKeyToActiveId.Find(Payload.CoalesceKey))
        {
            const int32 ActiveIndex = FindActiveIndexById(*ActiveId);
            if (ActiveIndex != INDEX_NONE)
            {
                FCUIActiveNotification& Entry = ActiveNotifications[ActiveIndex];
                Entry.Count++;
                Entry.Payload.Message = Payload.Message;

                if (FTimerHandle* Handle = LifetimeTimerHandles.Find(Entry.Id))
                {
                    GetWorld()->GetTimerManager().SetTimer(*Handle,
                        FTimerDelegate::CreateUObject(this, &UCUI_NotificationManager::HandleNotificationExpired, Entry.Id),
                        Entry.ResolvedLifetime, false);
                }

                OnNotificationRefreshed.Broadcast(Entry);
                return;
            }
        }

        // 1b) Coalesce onto a queued entry.
        for (FCUIActiveNotification& Queued : QueuedNotifications)
        {
            if (Queued.Payload.CoalesceKey == Payload.CoalesceKey)
            {
                Queued.Count++;
                Queued.Payload.Message = Payload.Message;
                return;
            }
        }
    }

    // 2) Room on screen? Activate. Otherwise queue.
    if (ActiveNotifications.Num() < MaxVisibleNotifications)
    {
        ActivateNotification(Payload, 1);
    }
    else
    {
        EnqueueNotification(Payload);
    }
}

void UCUI_NotificationManager::ActivateNotification(const FCUINotificationPayload& Payload, const int32 InitialCount)
{
    FCUIActiveNotification Entry;
    Entry.Id = NextNotificationId++;
    Entry.Payload = Payload;
    Entry.Count = InitialCount;
    Entry.ResolvedLifetime = Payload.LifetimeOverride > 0.f
        ? Payload.LifetimeOverride
        : GetDefaultLifetimeFor(Payload.Type);
    Entry.Priority = GetPriorityFor(Payload.Type);

    // Sort in: first slot whose priority is worse than ours. Newest wins ties,
    // so an error burst stacks newest-first while still outranking info.
    int32 InsertIndex = ActiveNotifications.Num();
    for (int32 i = 0; i < ActiveNotifications.Num(); ++i)
    {
        if (ActiveNotifications[i].Priority >= Entry.Priority)
        {
            InsertIndex = i;
            break;
        }
    }
    ActiveNotifications.Insert(Entry, InsertIndex);

    if (!Payload.CoalesceKey.IsNone())
    {
        CoalesceKeyToActiveId.Add(Payload.CoalesceKey, Entry.Id);
    }

    FTimerHandle& Handle = LifetimeTimerHandles.Add(Entry.Id);
    GetWorld()->GetTimerManager().SetTimer(Handle,
        FTimerDelegate::CreateUObject(this, &UCUI_NotificationManager::HandleNotificationExpired, Entry.Id),
        Entry.ResolvedLifetime, false);

    OnNotificationActivated.Broadcast(Entry, InsertIndex);
}

void UCUI_NotificationManager::EnqueueNotification(const FCUINotificationPayload& Payload)
{
    FCUIActiveNotification Queued;
    Queued.Id = INDEX_NONE; // assigned on activation
    Queued.Payload = Payload;
    Queued.Priority = GetPriorityFor(Payload.Type);

    int32 InsertIndex = QueuedNotifications.Num();
    for (int32 i = 0; i < QueuedNotifications.Num(); ++i)
    {
        if (QueuedNotifications[i].Priority > Queued.Priority)
        {
            InsertIndex = i;
            break;
        }
    }
    QueuedNotifications.Insert(Queued, InsertIndex);

    OnQueueChanged.Broadcast(QueuedNotifications.Num());
}

void UCUI_NotificationManager::HandleNotificationExpired(const int32 NotificationId)
{
    const int32 ActiveIndex = FindActiveIndexById(NotificationId);
    if (ActiveIndex == INDEX_NONE)
    {
        return;
    }

    if (FTimerHandle* Handle = LifetimeTimerHandles.Find(NotificationId))
    {
        GetWorld()->GetTimerManager().ClearTimer(*Handle);
        LifetimeTimerHandles.Remove(NotificationId);
    }

    const FName CoalesceKey = ActiveNotifications[ActiveIndex].Payload.CoalesceKey;
    if (!CoalesceKey.IsNone())
    {
        CoalesceKeyToActiveId.Remove(CoalesceKey);
    }

    ActiveNotifications.RemoveAt(ActiveIndex);
    OnNotificationDismissed.Broadcast(NotificationId);

    if (!QueuedNotifications.IsEmpty())
    {
        if (DequeueDelay > 0.f)
        {
            GetWorld()->GetTimerManager().SetTimer(DequeueTimerHandle,
                FTimerDelegate::CreateUObject(this, &UCUI_NotificationManager::TryDequeue),
                DequeueDelay, false);
        }
        else
        {
            TryDequeue();
        }
    }
}

void UCUI_NotificationManager::TryDequeue()
{
    if (QueuedNotifications.IsEmpty() || ActiveNotifications.Num() >= MaxVisibleNotifications)
    {
        return;
    }

    const FCUIActiveNotification Next = QueuedNotifications[0];
    QueuedNotifications.RemoveAt(0);
    OnQueueChanged.Broadcast(QueuedNotifications.Num());

    ActivateNotification(Next.Payload, Next.Count);
}

int32 UCUI_NotificationManager::FindActiveIndexById(const int32 NotificationId) const
{
    return ActiveNotifications.IndexOfByPredicate([NotificationId](const FCUIActiveNotification& Entry)
    {
        return Entry.Id == NotificationId;
    });
}

float UCUI_NotificationManager::GetDefaultLifetimeFor(const ECUINotificationType Type)
{
    switch (Type)
    {
        case ECUINotificationType::Error:       return 6.f;
        case ECUINotificationType::Warning:     return 5.f;
        case ECUINotificationType::Achievement: return 5.f;
        case ECUINotificationType::Event:       return 4.f;
        case ECUINotificationType::Social:      return 4.f;
        case ECUINotificationType::Item:        return 3.f;
        case ECUINotificationType::Info:        return 3.f;
        default:                                return 3.f;
    }
}

int32 UCUI_NotificationManager::GetPriorityFor(const ECUINotificationType Type)
{
    switch (Type)
    {
        case ECUINotificationType::Error:       return 0;
        case ECUINotificationType::Warning:     return 10;
        case ECUINotificationType::Achievement: return 20;
        case ECUINotificationType::Event:       return 30;
        case ECUINotificationType::Social:      return 40;
        case ECUINotificationType::Item:        return 50;
        case ECUINotificationType::Info:        return 60;
        default:                                return MAX_int32;
    }
}

UCUI_NotificationManager* UCUI_NotificationManager::Get(const APlayerController* PlayerController)
{
    if (!IsValid(PlayerController))
    {
        return nullptr;
    }

    const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
    return IsValid(LocalPlayer) ? LocalPlayer->GetSubsystem<UCUI_NotificationManager>() : nullptr;
}
#pragma endregion
/*-------------------------------------------------------------------------*/