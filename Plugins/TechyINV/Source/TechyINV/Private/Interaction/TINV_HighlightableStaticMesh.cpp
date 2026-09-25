// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Interaction/TINV_HighlightableStaticMesh.h"
#include "Core/CUI_StyleAsset.h"
#include "ItemData/TINV_ItemDataTable.h"
#include "Items/Components/TINV_ItemComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Widgets/Utils/TINV_WidgetUtils.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_HighlightableStaticMesh.cpp_Functions
void UTINV_HighlightableStaticMesh::Highlight_Implementation()
{
    ITINV_Highlightable::Highlight_Implementation();

    UMaterialInstanceDynamic* MID = GetOrCreateHighlightMID();
    if (!MID)
    {
        return;
    }
    
    if (!bColorApplied)
    {
        ApplyTierColor();
    }

    SetOverlayMaterial(MID);
}

void UTINV_HighlightableStaticMesh::UnHighlight_Implementation()
{
    ITINV_Highlightable::UnHighlight_Implementation();
    SetOverlayMaterial(nullptr);
}

UMaterialInstanceDynamic* UTINV_HighlightableStaticMesh::GetOrCreateHighlightMID()
{
    if (HighlightMID)
    {
        return HighlightMID;
    }

    if (!IsValid(HighlightMaterial))
    {
        return nullptr;
    }

    HighlightMID = UMaterialInstanceDynamic::Create(HighlightMaterial, this);
    return HighlightMID;
}

void UTINV_HighlightableStaticMesh::ApplyTierColor()
{
    UMaterialInstanceDynamic* MID = GetOrCreateHighlightMID();
    if (!MID || !IsValid(StyleAsset))
    {
        return;
    }

    const ETINV_ItemTier Tier = ResolveItemTier();
    const TCHAR* Token = UTINV_WidgetUtils::GetTierColorToken(Tier);

    const FString ColorToken = Token ? FString(Token) : FallbackColorToken;
    if (ColorToken.IsEmpty())
    {
        return;
    }

    MID->SetVectorParameterValue(ColorParameterName, StyleAsset->GetColorByName(ColorToken));
    bColorApplied = true;
}

ETINV_ItemTier UTINV_HighlightableStaticMesh::ResolveItemTier() const
{
    const AActor* Owner = GetOwner();
    if (!IsValid(Owner) || !IsValid(ItemDataTable))
    {
        return ETINV_ItemTier::Scrap;
    }

    const UTINV_ItemComponent* ItemComp = Owner->FindComponentByClass<UTINV_ItemComponent>();
    if (!IsValid(ItemComp))
    {
        return ETINV_ItemTier::Scrap;
    }

    const FGameplayTag ItemID = ItemComp->GetItemManifest().GetItemID();
    if (!ItemID.IsValid())
    {
        return ETINV_ItemTier::Scrap;
    }

    if (const FTINV_ItemDataDefinition* ItemData = ItemDataTable->GetDataByTag(ItemID))
    {
        return ItemData->ItemTier;
    }

    UE_LOG(LogTemp, Warning, TEXT("%s: no data table entry for item '%s' — using the fallback highlight color."),
        *GetName(), *ItemID.ToString());

    return ETINV_ItemTier::Scrap;
}

TArray<FString> UTINV_HighlightableStaticMesh::GetColorTokenOptions() const
{
    return IsValid(StyleAsset) ? StyleAsset->GetActiveColorNames() : TArray<FString>{};
}
#pragma endregion
/*-------------------------------------------------------------------------*/