// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Notifications/CUI_NotificationStack.h"
#include "Notifications/CUI_Notification.h"
#include "Notifications/CUI_NotificationManager.h"
#include "Notifications/CUI_NotificationCounter.h"
#include "Components/VerticalBox.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region CUI_NotificationStack.cpp_Functions
void UCUI_NotificationStack::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    // Pre-warm one pool per mapped type so bursts don't hitch on CreateWidget.
    TSet<TSubclassOf<UCUI_Notification>> ClassesToWarm;
    if (DefaultNotificationWidgetClass)
    {
        ClassesToWarm.Add(DefaultNotificationWidgetClass);
    }
    for (const TPair<ECUINotificationType, TSubclassOf<UCUI_Notification>>& Pair : NotificationWidgetClasses)
    {
        if (Pair.Value)
        {
            ClassesToWarm.Add(Pair.Value);
        }
    }

    for (const TSubclassOf<UCUI_Notification>& WidgetClass : ClassesToWarm)
    {
        FCUINotificationWidgetPool& Pool = WidgetPools.FindOrAdd(WidgetClass);
        for (int32 i = 0; i < InitialPoolSizePerClass; ++i)
        {
            UCUI_Notification* Widget = CreateWidget<UCUI_Notification>(this, WidgetClass);
            Widget->OnHideFinished.BindUObject(this, &UCUI_NotificationStack::HandleWidgetHideFinished);
            Pool.Widgets.Add(Widget);
        }
    }
}

void UCUI_NotificationStack::NativeConstruct()
{
    Super::NativeConstruct();

    if (UCUI_NotificationManager* Manager = GetManager())
    {
        Manager->OnNotificationActivated.AddDynamic(this, &UCUI_NotificationStack::HandleNotificationActivated);
        Manager->OnNotificationRefreshed.AddDynamic(this, &UCUI_NotificationStack::HandleNotificationRefreshed);
        Manager->OnNotificationDismissed.AddDynamic(this, &UCUI_NotificationStack::HandleNotificationDismissed);
        Manager->OnQueueChanged.AddDynamic(this, &UCUI_NotificationStack::HandleQueueChanged);
    }
}

void UCUI_NotificationStack::NativeDestruct()
{
    if (UCUI_NotificationManager* Manager = GetManager())
    {
        Manager->OnNotificationActivated.RemoveDynamic(this, &UCUI_NotificationStack::HandleNotificationActivated);
        Manager->OnNotificationRefreshed.RemoveDynamic(this, &UCUI_NotificationStack::HandleNotificationRefreshed);
        Manager->OnNotificationDismissed.RemoveDynamic(this, &UCUI_NotificationStack::HandleNotificationDismissed);
        Manager->OnQueueChanged.RemoveDynamic(this, &UCUI_NotificationStack::HandleQueueChanged);
    }

    Super::NativeDestruct();
}

TSubclassOf<UCUI_Notification> UCUI_NotificationStack::ResolveWidgetClass(const ECUINotificationType Type) const
{
    const TSubclassOf<UCUI_Notification>* Mapped = NotificationWidgetClasses.Find(Type);
    return (Mapped && *Mapped) ? *Mapped : DefaultNotificationWidgetClass;
}

UCUI_Notification* UCUI_NotificationStack::AcquireWidget(const ECUINotificationType Type)
{
    const TSubclassOf<UCUI_Notification> WidgetClass = ResolveWidgetClass(Type);
    if (!WidgetClass)
    {
        return nullptr;
    }

    FCUINotificationWidgetPool& Pool = WidgetPools.FindOrAdd(WidgetClass);
    if (!Pool.Widgets.IsEmpty())
    {
        return Pool.Widgets.Pop();
    }

    UCUI_Notification* Widget = CreateWidget<UCUI_Notification>(this, WidgetClass);
    Widget->OnHideFinished.BindUObject(this, &UCUI_NotificationStack::HandleWidgetHideFinished);
    return Widget;
}

void UCUI_NotificationStack::HandleWidgetHideFinished(UCUI_Notification* Widget)
{
    if (!IsValid(Widget))
    {
        return;
    }

    Widget->RemoveFromParent();
    WidgetPools.FindOrAdd(Widget->GetClass()).Widgets.Add(Widget);
}

void UCUI_NotificationStack::HandleNotificationActivated(const FCUIActiveNotification& Entry, const int32 InsertIndex)
{
    UCUI_Notification* Widget = AcquireWidget(Entry.Payload.Type);
    if (!Widget)
    {
        return;
    }

    ActiveWidgets.Add(Entry.Id, Widget);

    VerticalBox_Stack->InsertChildAt(InsertIndex, Widget);
    Widget->SetNotification(Entry);
}

void UCUI_NotificationStack::HandleNotificationRefreshed(const FCUIActiveNotification& Entry)
{
    if (const TObjectPtr<UCUI_Notification>* Widget = ActiveWidgets.Find(Entry.Id))
    {
        (*Widget)->SetNotification(Entry);
    }
}

void UCUI_NotificationStack::HandleNotificationDismissed(const int32 NotificationId)
{
    TObjectPtr<UCUI_Notification> Widget;
    if (ActiveWidgets.RemoveAndCopyValue(NotificationId, Widget))
    {
        // Widget stays in the box while its exit animation plays;
        // HandleWidgetHideFinished reclaims it.
        Widget->NotificationHide();
    }
}

void UCUI_NotificationStack::HandleQueueChanged(const int32 QueuedCount)
{
    if (OverflowCounter)
    {
        OverflowCounter->SetCount(QueuedCount);
    }
}

UCUI_NotificationManager* UCUI_NotificationStack::GetManager() const
{
    const ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
    return IsValid(LocalPlayer) ? LocalPlayer->GetSubsystem<UCUI_NotificationManager>() : nullptr;
}
#pragma endregion
/*-------------------------------------------------------------------------*/