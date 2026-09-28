// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Core/CUI_Widget.h"
#include "Notifications/CUI_NotificationTypes.h"
#include "CUI_TieredItemNameText.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region CUI_TieredItemNameText.h_Class
/**
 * Item name with brackets, tinted by tier.
 * [TextBox_Bracket1][TextBox_ItemName][TextBox_Bracket2] all get the same tier color.
 */
UCLASS()
class CLICKYUI_API UCUI_TieredItemNameText : public UCUI_Widget
{
    GENERATED_BODY()

public:
    /** Sets the item name text and colors the brackets and name with the tier's rarity color. */
    UFUNCTION(BlueprintCallable, Category = "CLICKY|TieredText")
    void SetItemNameAndTier(const FText& ItemName, ECUI_ItemTier Tier);

    UFUNCTION(BlueprintPure, Category = "CLICKY|TieredText")
    FText GetItemName() const { return CurrentName; }

    UFUNCTION(BlueprintPure, Category = "CLICKY|TieredText")
    ECUI_ItemTier GetTier() const { return CurrentTier; }

protected:
    virtual void NativePreConstruct() override;

    /** Color for tiers with no rarity color (None, Scrap). Empty = leave the text alone. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CLICKY|TieredText", meta = (GetOptions = "GetColorTokenOptions"))
    FString FallbackToken = TEXT("Gray/Border");

#if WITH_EDITORONLY_DATA
    /** Designer-only preview name. Not used at runtime. */
    UPROPERTY(EditAnywhere, Category = "CLICKY|TieredText|Preview")
    FText PreviewName = NSLOCTEXT("CUI", "TieredItemNamePreview", "Item Name");

    /** Designer-only preview tier. Not used at runtime. */
    UPROPERTY(EditAnywhere, Category = "CLICKY|TieredText|Preview")
    ECUI_ItemTier PreviewTier = ECUI_ItemTier::Tier1;
#endif

private:
    void ApplyName();
    void ApplyColor();
    void ApplyColorTo(UTextBlock* Target, const FSlateColor& Color) const;

    UFUNCTION()
    TArray<FString> GetColorTokenOptions() const;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TextBox_Bracket1;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TextBox_ItemName;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TextBox_Bracket2;

    FText CurrentName;
    ECUI_ItemTier CurrentTier = ECUI_ItemTier::None;
};
#pragma endregion
/*-------------------------------------------------------------------------*/