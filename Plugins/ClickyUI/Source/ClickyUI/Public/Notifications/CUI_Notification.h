// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "Notifications/CUI_NotificationTypes.h"
#include "CUI_Notification.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;
class UImage;
class UTexture2D;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class UCUI_NotificationCounter;
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

    UFUNCTION(BlueprintPure, Category = "CUI|Glint")
    bool HasGlint() const { return Image_Glint != nullptr && GlintMID != nullptr; }


    /** Play the entrance animation (slide-in / grow). */
    UFUNCTION(BlueprintImplementableEvent, Category = "CUI|Events")
    void NotificationShow();

    /** Play the exit animation. MUST end by calling NotifyHideFinished. */
    UFUNCTION(BlueprintImplementableEvent, Category = "CUI|Events")
    void NotificationHide();

    /** Content landed or refreshed. Handle per-type styling here. */
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

    /** Optional: notification Blueprints without a glint layer still compile. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "CUI|Widgets")
    TObjectPtr<UImage> Image_Glint;

    UPROPERTY(EditDefaultsOnly, Category = "CUI|Glint")
    TObjectPtr<UMaterialInterface> GlintMaterial;

    /** Must match the parameter names inside the glint material. */
    UPROPERTY(EditDefaultsOnly, Category = "CUI|Glint|Params")
    FName GlintTextureParam{TEXT("Texture")};

    UPROPERTY(EditDefaultsOnly, Category = "CUI|Glint|Params")
    FName GlintTextureObjectParam{TEXT("Texture Object")};
    
    /** Hide the glint layer entirely when the entry carries no icon. */
    UPROPERTY(EditDefaultsOnly, Category = "CUI|Glint")
    bool bHideGlintWithoutIcon{true};

    /** Returns the MID, creating it on first use. Null if there's no glint layer. */
    UMaterialInstanceDynamic* GetGlintMID();

private:

    FCUIActiveNotification CurrentEntry;

    UPROPERTY(Transient)
    TObjectPtr<UMaterialInstanceDynamic> GlintMID;

    void ApplyIcon(const FCUIActiveNotification& Entry);
    void ApplyGlint(const FCUIActiveNotification& Entry);

};
#pragma endregion
/*-------------------------------------------------------------------------*/