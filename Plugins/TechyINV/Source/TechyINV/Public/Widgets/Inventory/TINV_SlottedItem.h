// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/TINV_EnumTypes.h"
#include "TINV_SlottedItem.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UImage;
class UMaterialInstanceDynamic;
class UMaterialInterface;
class UTexture2D;
class UTextBlock;
class UTINV_InventoryItem;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_SlottedItem.h_Class
UCLASS()
class TECHYINV_API UTINV_SlottedItem : public UUserWidget
{
    GENERATED_BODY()

public:
    UTINV_SlottedItem(const FObjectInitializer& ObjectInitializer);

    void SetIsStackable(bool bStackable) { bIsStackable = bStackable; }
    bool GetIsStackable() const { return bIsStackable; }
    UImage* GetImageIcon() { return Image_Icon; }
    void SetGridIndex(int32 Index) { GridIndex = Index; }
    int32 GetGridIndex() const { return GridIndex; }
    void SetInventoryItem(UTINV_InventoryItem* Item);
    UTINV_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
    void UpdateStackCount(int32 StackCount);

    /** Sets the icon and applies the glint for the given tier (Scrap = no glint by default). */
    void LoadIcon(UTexture2D* Icon, ETINV_ItemTier GlintTier = ETINV_ItemTier::Scrap);

    /** Swaps the glint tier without touching the icon. */
    void SetGlintTier(ETINV_ItemTier GlintTier);
    ETINV_ItemTier GetGlintTier() const { return CurrentGlintTier; }

    /** Material texture parameter fed with the item icon. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TECHY|Inventory|Glint")
    FName GlintTextureParam = TEXT("Texture");

    /** Material texture-object parameter fed with the item icon. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TECHY|Inventory|Glint")
    FName GlintTextureObjectParam = TEXT("Texture Object");

protected:

private:
    UMaterialInstanceDynamic* GetGlintMID();
    void ApplyGlint();

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> Text_StackCount;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Image_Icon;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Image_Glint;

    /** One glint material per tier. Missing or null entry = that tier shows no glint. */
    UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory|Glint", meta = (ForceInlineRow))
    TMap<ETINV_ItemTier, TObjectPtr<UMaterialInterface>> GlintMaterials;

    UPROPERTY(Transient)
    TObjectPtr<UMaterialInstanceDynamic> GlintMID;

    UPROPERTY(Transient)
    TObjectPtr<UTexture2D> CurrentIcon;

    ETINV_ItemTier CurrentGlintTier = ETINV_ItemTier::Scrap;
    int32 GridIndex = INDEX_NONE;
    TWeakObjectPtr<UTINV_InventoryItem> InventoryItem;
    bool bIsStackable = false;
};
#pragma endregion
/*-------------------------------------------------------------------------*/