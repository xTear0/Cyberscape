// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "CUI_Button_Wide.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Button_Wide_OnClickedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Button_Wide_OnPressedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Button_Wide_OnReleasedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCUI_Button_Wide_OnHoverEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCUI_Button_Wide_OnIsEnabledEvent, bool, bIsEnabled);
class UButton;
class UTextBlock;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Button_Wide.h_Class
UCLASS()
class CLICKYUI_API UCUI_Button_Wide : public UCUI_Widget
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CUI_Button|Defaults")
    FText TextContent;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CUI_Button|Defaults")
    float TextSize { 24.f };

    /** Events propagated up from UButton bound member. */
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "CUI_Button|Event")
    FCUI_Button_Wide_OnClickedEvent OnClicked;

    /* This event triggers immediately, instead of waiting for the animation   */
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "CUI_Button|Event")
    FCUI_Button_Wide_OnClickedEvent OnClickedInstant;

    UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
    FCUI_Button_Wide_OnPressedEvent OnPressed;

    UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
    FCUI_Button_Wide_OnReleasedEvent OnReleased;

    UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
    FCUI_Button_Wide_OnHoverEvent OnHovered;

    UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
    FCUI_Button_Wide_OnHoverEvent OnUnhovered;

    UPROPERTY(BlueprintAssignable, Category = "CUI_Button|Event")
    FCUI_Button_Wide_OnIsEnabledEvent OnIsEnabled;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> UE_Button;

    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> TextBlock_Button;

    UPROPERTY(Transient, meta=(BindWidgetAnimOptional))
    UWidgetAnimation* Anim_Enabled;

    UPROPERTY(Transient, meta=(BindWidgetAnimOptional))
    UWidgetAnimation* Anim_Transition;

    UPROPERTY(BlueprintReadWrite)
    bool OverrideDisableAnimation = false;

    /** Passthrough accessors matching UButton's interface. */
    UFUNCTION(BlueprintCallable, Category = "CUI_Button")
    void SetIsButtonEnabled(bool bInIsEnabled);

    UFUNCTION(BlueprintCallable, Category = "CUI_Button")
    bool GetIsButtonEnabled() const;

    /* CUI Button can operate as a TextBlock if it implements the optional text block bindings. */
    UFUNCTION(BlueprintCallable, Category = "CUI_Button")
    void SetText(const FText& InText) const;

    /* CUI Button can operate as a TextBlock if it implements the optional text block bindings. */
    UFUNCTION(BlueprintCallable, Category = "CUI_Button")
    FText GetText() const;

    void PlayTransitionAnimation(bool Reverse);
    void ClearAnimations();

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    void SetTextContent() const;
    virtual void NativePreConstruct() override;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
