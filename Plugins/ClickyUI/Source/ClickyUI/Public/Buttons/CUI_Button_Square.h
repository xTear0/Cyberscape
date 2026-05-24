// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_Button_Square.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Button_Square_OnClickedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Button_Square_OnPressedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Button_Square_OnReleasedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Button_Square_OnHoverEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCUI_Button_Square_OnIsEnabledEvent, bool, bIsEnabled);
class UButton;
class UImage;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Button_Square.h_Class
UCLASS()
class CLICKYUI_API UCUI_Button_Square : public UCUI_Widget
{
	GENERATED_BODY()

public:
    /** Events propagated up from UButton bound member. */
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "CUI_Button|Event")
    FCUI_Button_Square_OnClickedEvent OnClicked;

    /* Instead of OnClicked, you'd rather use this  */
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "CUI_Button|Event")
    FCUI_Button_Square_OnClickedEvent OnClickedPostAnim;

    UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
    FCUI_Button_Square_OnPressedEvent OnPressed;

    UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
    FCUI_Button_Square_OnReleasedEvent OnReleased;

    UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
    FCUI_Button_Square_OnHoverEvent OnHovered;

    UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
    FCUI_Button_Square_OnHoverEvent OnUnhovered;

    UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
    FCUI_Button_Square_OnIsEnabledEvent OnIsEnabled;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> UE_Button;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CUI_Button|Defaults")
    TObjectPtr<UTexture2D> Image_Icon;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> UE_Image;

    UPROPERTY(Transient, meta=(BindWidgetAnimOptional))
    UWidgetAnimation* Anim_Hovered;

    UPROPERTY(Transient, meta=(BindWidgetAnimOptional))
    UWidgetAnimation* Anim_Clicked;

    UPROPERTY(Transient, meta=(BindWidgetAnimOptional))
    UWidgetAnimation* Anim_Selected;

    UPROPERTY(Transient, meta=(BindWidgetAnimOptional))
    UWidgetAnimation* Anim_Deselected;

    UPROPERTY(BlueprintReadWrite)
    bool OverrideDisableAnimation = false;

    /** Passthrough accessors matching UButton's interface. */
    UFUNCTION(BlueprintCallable, Category = "CUI_Button")
    void SetIsButtonEnabled(bool bInIsEnabled);

    UFUNCTION(BlueprintCallable, Category = "CUI_Button")
    bool GetIsButtonEnabled() const;

    void ShowButtonAsSelected();
    void ShowButtonAsDeselected();

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual void NativePreConstruct() override;

    UFUNCTION() void OnHoveredEvent();
    UFUNCTION() void OnUnhoveredEvent();
    UFUNCTION() void OnClickedEvent();
    UFUNCTION() void OnIsEnabledEvent();

private:

    FTimerHandle HoverPulseTimer;
    FTimerHandle ClickPulseTimer;

    void PlayHoverAnimation();
    void PostAnimation();

    UFUNCTION() void HandleClicked()    { OnClicked.Broadcast();   }
    UFUNCTION() void HandlePressed()    { OnPressed.Broadcast();   }
    UFUNCTION() void HandleReleased()   { OnReleased.Broadcast();  }
    UFUNCTION() void HandleHovered()    { OnHovered.Broadcast();   }
    UFUNCTION() void HandleUnhovered()  { OnUnhovered.Broadcast(); }
};
#pragma endregion
/*-------------------------------------------------------------------------*/
