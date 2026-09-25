// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "TINV_Highlightable.h"
#include "Components/StaticMeshComponent.h"
#include "Types/TINV_StructTypes.h" // ETINV_ItemTier
#include "TINV_HighlightableStaticMesh.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UCUI_StyleAsset;
class UMaterialInstanceDynamic;
class UTINV_ItemDataTable;
/*-------------------------------------------------------------------------*/

/*
 * A static mesh that highlights with an overlay material tinted by the owning
 * item's tier color, pulled from the CUI style asset.
 */

/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_HighlightableStaticMesh.h_Class
UCLASS()
class TECHYINV_API UTINV_HighlightableStaticMesh : public UStaticMeshComponent, public ITINV_Highlightable
{
    GENERATED_BODY()

public:
    virtual void Highlight_Implementation() override;
    virtual void UnHighlight_Implementation() override;

private:

    UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
    TObjectPtr<UMaterialInterface> HighlightMaterial;

    // Where the tier colors come from. Must match the one the inventory UI uses.
    UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory|Style")
    TObjectPtr<UCUI_StyleAsset> StyleAsset;

    // Resolves the owning item's ItemID gameplay tag to its tier.
    UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory|Style")
    TObjectPtr<UTINV_ItemDataTable> ItemDataTable;

    // Vector parameter on the highlight material instance that takes the tier color.
    UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory|Style")
    FName ColorParameterName = TEXT("Glow Color");

    // Used when the item has no tier color (Scrap) or the tier can't be resolved.
    UPROPERTY(EditAnywhere, Category = "TECHY|Inventory|Style", meta = (GetOptions = "GetColorTokenOptions"))
    FString FallbackColorToken = TEXT("Common");

    // Created on first highlight so each mesh can hold its own color.
    UPROPERTY(Transient)
    TObjectPtr<UMaterialInstanceDynamic> HighlightMID;

    // Whether HighlightMID's color is up to date. Reset if the item changes.
    bool bColorApplied = false;

    UMaterialInstanceDynamic* GetOrCreateHighlightMID();
    void ApplyTierColor();

    // Reads the owner's item component, then the data table. Scrap if either is missing.
    ETINV_ItemTier ResolveItemTier() const;

    UFUNCTION()
    TArray<FString> GetColorTokenOptions() const;
};
#pragma endregion
/*-------------------------------------------------------------------------*/