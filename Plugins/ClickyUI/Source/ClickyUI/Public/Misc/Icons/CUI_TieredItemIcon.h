// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "Notifications/CUI_NotificationTypes.h"
#include "CUI_TieredItemIcon.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCUI_StyleAsset;
class UImage;
class UMaterialInstanceDynamic;
class UMaterialInterface;
class UTexture2D;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region CUI_TieredItemIcon.h_Class
/**
 * Item icon with a per-tier glint overlay.
 * Owns the icon image, the glint image, the per-tier glint materials and the cached MID.
 * Anything that shows an item icon (slots, tooltips, loot popups) can drop this in.
 */
UCLASS()
class CLICKYUI_API UCUI_TieredItemIcon : public UCUI_Widget
{
    GENERATED_BODY()

public:
    UCUI_TieredItemIcon(const FObjectInitializer& ObjectInitializer);

    /**
     * Sets the icon texture and refreshes the glint for the current tier.
     * Null clears the icon (icon + glint collapse).
     * Keeps the designer brush (DrawAs, tint, margins); ImageSize only changes if bMatchTextureSize is on.
     */
    UFUNCTION(BlueprintCallable, Category = "CLICKY|TieredIcon")
    void SetIcon(UTexture2D* Icon);

    /** Sets icon and tier in one pass (one glint refresh instead of two). */
    UFUNCTION(BlueprintCallable, Category = "CLICKY|TieredIcon")
    void SetIconAndTier(UTexture2D* Icon, ECUI_ItemTier Tier);

    /** Swaps the glint tier without touching the icon. */
    UFUNCTION(BlueprintCallable, Category = "CLICKY|TieredIcon")
    void SetTier(ECUI_ItemTier Tier);

    /** Removes the icon and hides the glint. */
    UFUNCTION(BlueprintCallable, Category = "CLICKY|TieredIcon")
    void ClearIcon();

    UFUNCTION(BlueprintPure, Category = "CLICKY|TieredIcon")
    UTexture2D* GetIcon() const { return CurrentIcon; }

    UFUNCTION(BlueprintPure, Category = "CLICKY|TieredIcon")
    ECUI_ItemTier GetTier() const { return CurrentTier; }

    UFUNCTION(BlueprintPure, Category = "CLICKY|TieredIcon")
    bool HasIcon() const { return IsValid(CurrentIcon); }

    UImage* GetImageIcon() const { return Image_Icon; }
    UImage* GetImageGlint() const { return Image_Glint; }
    UImage* GetImageBackground() const { return Image_Background; }
    UImage* GetImageBackgroundStroke() const { return Image_BackgroundStroke; }

    /** Background fill token for a tier (the darker accent). Empty for None and Scrap. */
    UFUNCTION(BlueprintPure, Category = "CLICKY|TieredIcon|Background")
    static FString GetTierColorToken(ECUI_ItemTier Tier);

    /** Outline token for a tier (the brighter rarity color). Empty for None and Scrap. */
    UFUNCTION(BlueprintPure, Category = "CLICKY|TieredIcon|Background")
    static FString GetTierStrokeColorToken(ECUI_ItemTier Tier);

    /** Material texture parameter fed with the item icon. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CLICKY|TieredIcon|Glint")
    FName GlintTextureParam = TEXT("Texture");

    /** Material texture-object parameter fed with the item icon. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CLICKY|TieredIcon|Glint")
    FName GlintTextureObjectParam = TEXT("Texture Object");

protected:
    virtual void NativePreConstruct() override;

    /** If true, the icon (and glint) brush ImageSize is set to the texture's pixel size. Off = keep designer size. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CLICKY|TieredIcon")
    bool bMatchTextureSize = false;

    /** Visibility the icon image uses while it has a texture. Visible keeps it hit-testable for drag/click on parents. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CLICKY|TieredIcon")
    ESlateVisibility IconShownVisibility = ESlateVisibility::Visible;

    /*---------------------------------------------------------------------*/
    /*   Background                                                        */
    /*---------------------------------------------------------------------*/

    /** Background fill for tiers with no rarity color (None, Scrap). Empty = leave the image alone. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CLICKY|TieredIcon|Background", meta = (GetOptions = "GetColorTokenOptions"))
    FString FallbackBackgroundToken = TEXT("Surface/Raised");

    /** Outline for tiers with no rarity color (None, Scrap). Empty = leave the image alone. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CLICKY|TieredIcon|Background", meta = (GetOptions = "GetColorTokenOptions"))
    FString FallbackStrokeToken = TEXT("Gray/Border");

    /** Multiplies the background token's alpha, so one token can back a solid frame or a faint wash. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CLICKY|TieredIcon|Background", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float BackgroundOpacity = 1.0f;

    /** Multiplies the stroke token's alpha. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CLICKY|TieredIcon|Background", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float StrokeOpacity = 1.0f;

#if WITH_EDITORONLY_DATA
    /** Designer-only preview icon. Not used at runtime. */
    UPROPERTY(EditAnywhere, Category = "CLICKY|TieredIcon|Preview")
    TObjectPtr<UTexture2D> PreviewIcon;

    /** Designer-only preview tier. Not used at runtime. */
    UPROPERTY(EditAnywhere, Category = "CLICKY|TieredIcon|Preview")
    ECUI_ItemTier PreviewTier = ECUI_ItemTier::Tier1;
#endif

private:
    void ApplyIcon();
    void ApplyGlint();
    void ApplyBackground();
    UMaterialInstanceDynamic* GetGlintMID();

    /** Resolves Token (or Fallback when empty) against the style asset and tints Target. */
    void ApplyTokenColor(UImage* Target, const FString& Token, const FString& Fallback, float OpacityScale) const;

    UFUNCTION()
    TArray<FString> GetColorTokenOptions() const;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Image_Icon;

    /** Optional: widgets without a glint layer still work as plain icons. */
    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UImage> Image_Glint;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Image_Background;

    /** Optional outline drawn over the background. */
    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UImage> Image_BackgroundStroke;

    /** One glint material per tier. Missing or null entry = that tier shows no glint. */
    UPROPERTY(EditDefaultsOnly, Category = "CLICKY|TieredIcon|Glint", meta = (ForceInlineRow))
    TMap<ECUI_ItemTier, TObjectPtr<UMaterialInterface>> GlintMaterials;

    UPROPERTY(Transient)
    TObjectPtr<UMaterialInstanceDynamic> GlintMID;

    UPROPERTY(Transient)
    TObjectPtr<UTexture2D> CurrentIcon;

    ECUI_ItemTier CurrentTier = ECUI_ItemTier::None;
};
#pragma endregion
/*-------------------------------------------------------------------------*/