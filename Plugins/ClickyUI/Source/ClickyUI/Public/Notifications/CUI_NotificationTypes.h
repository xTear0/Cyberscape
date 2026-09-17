// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "CUI_NotificationTypes.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTexture2D;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Types                                                                 */
/*-------------------------------------------------------------------------*/
#pragma region CUI_NotificationTypes.h_Types
UENUM(BlueprintType)
enum class ECUINotificationType : uint8
{
    Info        UMETA(DisplayName = "Info"),
    Item        UMETA(DisplayName = "Item"),
    Warning     UMETA(DisplayName = "Warning"),
    Success     UMETA(DisplayName = "Success"),
    Error       UMETA(DisplayName = "Error"),
    Social      UMETA(DisplayName = "Social"),
    Achievement UMETA(DisplayName = "Achievement"),
    Event       UMETA(DisplayName = "Event")
};

USTRUCT(BlueprintType)
struct FCUINotificationPayload
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CUI|Notification")
    ECUINotificationType Type{ECUINotificationType::Info};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CUI|Notification")
    FText Message;

    /** Optional. When null, the widget keeps its Blueprint-preset icon for this type. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CUI|Notification")
    TObjectPtr<UTexture2D> IconOverride{nullptr};

    /** Optional. <= 0 means "use the per-type default from ClickyUI settings". */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CUI|Notification")
    float LifetimeOverride{-1.f};

    /**
     * Optional. Notifications sharing a key while one is on screen merge into
     * a counter bump instead of spawning (e.g. "Pickup.ScrapMetal" x40).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CUI|Notification")
    FName CoalesceKey{NAME_None};
};

/** A live notification as tracked by the manager. What the stack widget receives. */
USTRUCT(BlueprintType)
struct FCUIActiveNotification
{
    GENERATED_BODY()

    /** Stable id for the lifetime of this entry. Use it to map to your widget instance. */
    UPROPERTY(BlueprintReadOnly, Category = "CUI|Notification")
    int32 Id{INDEX_NONE};

    UPROPERTY(BlueprintReadOnly, Category = "CUI|Notification")
    FCUINotificationPayload Payload;

    /** How many posts have coalesced into this entry. Starts at 1. */
    UPROPERTY(BlueprintReadOnly, Category = "CUI|Notification")
    int32 Count{1};

    /** Lifetime after resolving override vs. per-type default. */
    UPROPERTY(BlueprintReadOnly, Category = "CUI|Notification")
    float ResolvedLifetime{3.f};

    /** Lower value = closer to the stack anchor. */
    UPROPERTY(BlueprintReadOnly, Category = "CUI|Notification")
    int32 Priority{0};
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCUIOnNotificationActivated, const FCUIActiveNotification&, Entry, int32, InsertIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCUIOnNotificationRefreshed, const FCUIActiveNotification&, Entry);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCUIOnNotificationDismissed, int32, NotificationId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCUIOnNotificationQueueChanged, int32, QueuedCount);
#pragma endregion
/*-------------------------------------------------------------------------*/