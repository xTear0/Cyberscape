// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/TINV_StructTypes.h"
#include "TINV_GridSlot.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UImage;
class UCUI_StyleAsset;
class UCUI_StyleServiceComponent;
class UTINV_ItemComponent;
class UTINV_InventoryItem;

UENUM(BlueprintType)
enum class ETINV_GridSlotState : uint8
{
    Unoccupied,
    Occupied,
    Selected,
    GrayedOut
};
/*-------------------------------------------------------------------------*/

/*
 * A single slot in the inventory grid. The brush never changes; each state
 * only swaps the color token on Image_GridSlot's CUI Style Service Component.
 */

/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_GridSlot.h_Class
UCLASS()
class TECHYINV_API UTINV_GridSlot : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetTileIndex(int32 Index) { TileIndex = Index; }
    int32 GetTileIndex() const { return TileIndex; }
    ETINV_GridSlotState GetGridSlotState() const { return GridSlotState; }
    TWeakObjectPtr<UTINV_InventoryItem> GetInventoryItem() const { return InventoryItem; }
    void SetInventoryItem(UTINV_InventoryItem* NewItem);
    void SetStackCount(int32 NewStackCount) { StackCount = NewStackCount; }
    int32 GetStackCount() const { return StackCount; }

    void SetUnoccupiedTexture();

    // Uses the tier's rarity accent color when bRarityOverridesOccupiedSlot is true.
    // Scrap (the default) has no rarity color and falls back to OccupiedColorToken.
    void SetOccupiedTexture(ETINV_ItemTier Tier = ETINV_ItemTier::Scrap);

    void SetSelectedTexture();
    void SetGrayedOutTexture();

protected:
    virtual void NativeOnInitialized() override;

private:
    
    int32 TileIndex = INDEX_NONE;
    int32 StackCount;
    TWeakObjectPtr<UTINV_InventoryItem> InventoryItem;

    
    ETINV_GridSlotState GridSlotState = ETINV_GridSlotState::Unoccupied;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Image_GridSlot;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Image_GridSlotStroke;

    /*---------------------------------------------------------------------*/
    /*   Style                                                             */
    /*---------------------------------------------------------------------*/

    // Feeds the token dropdowns below. Also assigned to the style component
    // at runtime if the component has no style asset of its own.
    UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory|Style")
    TObjectPtr<UCUI_StyleAsset> StyleAsset;

    UPROPERTY(EditAnywhere, Category = "TECHY|Inventory", meta = (GetOptions = "GetColorTokenOptions"))
    FString UnoccupiedColorToken = TEXT("Gray/Secondary");

    UPROPERTY(EditAnywhere, Category = "TECHY|Inventory", meta = (GetOptions = "GetColorTokenOptions"))
    FString OccupiedColorToken = TEXT("Gray/Muted");

    UPROPERTY(EditAnywhere, Category = "TECHY|Inventory", meta = (GetOptions = "GetColorTokenOptions"))
    FString SelectedColorToken = TEXT("Accent/50");

    UPROPERTY(EditAnywhere, Category = "TECHY|Inventory", meta = (GetOptions = "GetColorTokenOptions"))
    FString GrayedOutColorToken = TEXT("Gray/Border");

    // When true, an occupied slot uses the item's tier color instead of OccupiedColorToken.
    UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
    bool bRarityOverridesOccupiedSlot = true;

    // Found once in NativeOnInitialized; owned by the widget's UI component extension.
    TWeakObjectPtr<UCUI_StyleServiceComponent> CachedStyle_Background;
    TWeakObjectPtr<UCUI_StyleServiceComponent> CachedStyle_Stroke;

    TWeakObjectPtr<UTINV_ItemComponent> DisplayedItem;

    UCUI_StyleServiceComponent* FindStyleComponent(UWidget* Target) const;
    void ApplyColorToken(const FString& Token) const;

    // Tier -> style asset color token. Returns nullptr for tiers with no rarity color (Scrap).
    static const TCHAR* GetTierColorToken(ETINV_ItemTier Tier);

    UFUNCTION()
    TArray<FString> GetColorTokenOptions() const;
};
#pragma endregion
/*-------------------------------------------------------------------------*/