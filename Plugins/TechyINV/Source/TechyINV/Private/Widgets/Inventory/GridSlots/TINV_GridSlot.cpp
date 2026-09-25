// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Inventory/GridSlots/TINV_GridSlot.h"
#include "Components/Image.h"
#include "Items/TINV_InventoryItem.h"
#include "Core/CUI_StyleAsset.h"
#include "Core/CUI_StyleServiceComponent.h"
#include "Extensions/UIComponentUserWidgetExtension.h"
#include "Types/TINV_StructTypes.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_GridSlot.cpp_Functions
void UTINV_GridSlot::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    // One lookup per slot for its whole lifetime.
    CachedStyle_Background = FindStyleComponent(Image_GridSlot);
    CachedStyle_Stroke = FindStyleComponent(Image_GridSlotStroke);
    
    UCUI_StyleServiceComponent* StyleBackground = CachedStyle_Background.Get();
    if (!StyleBackground)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: Image_GridSlot has no CUI Style Service Component — slot colors won't change."), *GetName());
        return;
    }

    UCUI_StyleServiceComponent* StyleStroke = CachedStyle_Stroke.Get();
    if (!StyleStroke)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: Image_GridSlotStroke has no CUI Style Service Component — slot colors won't change."), *GetName());
        return;
    }
    
    if (!IsValid(StyleBackground->StyleAsset) && IsValid(StyleAsset))
    {
        StyleBackground->SetStyleAsset(StyleAsset, /*bRefresh*/ false);
    }
    if (!IsValid(StyleStroke->StyleAsset) && IsValid(StyleAsset))
    {
        StyleStroke->SetStyleAsset(StyleAsset, /*bRefresh*/ false);
    }
    
    SetUnoccupiedTexture();
}

void UTINV_GridSlot::SetInventoryItem(UTINV_InventoryItem* NewItem)
{
    InventoryItem = NewItem;
}

void UTINV_GridSlot::SetUnoccupiedTexture()
{
    GridSlotState = ETINV_GridSlotState::Unoccupied;
    ApplyColorToken(UnoccupiedColorToken);
}

void UTINV_GridSlot::SetOccupiedTexture(ETINV_ItemTier Tier)
{
    GridSlotState = ETINV_GridSlotState::Occupied;

    UCUI_StyleServiceComponent* StyleBackground = CachedStyle_Background.Get();
    UCUI_StyleServiceComponent* StyleStroke = CachedStyle_Stroke.Get();
    if (!StyleBackground && !StyleStroke) return;

    // Scrap maps to nullptr; SetColorToken also rejects tokens missing from the asset,
    // so either case falls back to OccupiedColorToken.
    const TCHAR* TierToken = bRarityOverridesOccupiedSlot ? GetTierColorToken(Tier) : nullptr;
    const bool bUsedTier = TierToken && StyleStroke->SetColorToken(TierToken) && StyleBackground->SetColorToken(TierToken);

    if (!bUsedTier)
    {
        StyleStroke->SetColorToken(OccupiedColorToken);
        StyleBackground->SetColorToken(OccupiedColorToken);
    }
}

void UTINV_GridSlot::SetSelectedTexture()
{
    GridSlotState = ETINV_GridSlotState::Selected;
    ApplyColorToken(SelectedColorToken);
}

void UTINV_GridSlot::SetGrayedOutTexture()
{
    GridSlotState = ETINV_GridSlotState::GrayedOut;
    ApplyColorToken(GrayedOutColorToken);
}

void UTINV_GridSlot::ApplyColorToken(const FString& Token) const
{
    if (UCUI_StyleServiceComponent* StyleBackground = CachedStyle_Background.Get())
    {
        StyleBackground->SetColorToken(Token);
    }
    if (UCUI_StyleServiceComponent* StyleStroke = CachedStyle_Stroke.Get())
    {
        StyleStroke->SetColorToken(Token);
    }
}

const TCHAR* UTINV_GridSlot::GetTierColorToken(ETINV_ItemTier Tier)
{
    switch (Tier)
    {
        case ETINV_ItemTier::Tier1: return TEXT("Common");
        case ETINV_ItemTier::Tier2: return TEXT("Uncommon");
        case ETINV_ItemTier::Tier3: return TEXT("Rare");
        case ETINV_ItemTier::Tier4: return TEXT("Legendary");
        case ETINV_ItemTier::Tier5: return TEXT("Omega");
        case ETINV_ItemTier::Prem:  return TEXT("Premium");
        case ETINV_ItemTier::Scrap:
        default:                    return nullptr;
    }
}

UCUI_StyleServiceComponent* UTINV_GridSlot::FindStyleComponent(UWidget* Target) const
{
    if (!Target)
    {
        return nullptr;
    }

    if (UUIComponentUserWidgetExtension* Ext = GetExtension<UUIComponentUserWidgetExtension>())
    {
        for (UUIComponent* Comp : Ext->GetComponentsFor(Target))
        {
            if (UCUI_StyleServiceComponent* Style = Cast<UCUI_StyleServiceComponent>(Comp))
            {
                return Style;
            }
        }
    }
    return nullptr;
}

TArray<FString> UTINV_GridSlot::GetColorTokenOptions() const
{
    return IsValid(StyleAsset) ? StyleAsset->GetActiveColorNames() : TArray<FString>{};
}
#pragma endregion
/*-------------------------------------------------------------------------*/