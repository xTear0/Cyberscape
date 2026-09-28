// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TINV_SlottedItem.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;
class UTINV_GlintedIcon;
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
    void SetIsStackable(bool bStackable) { bIsStackable = bStackable; }
    bool GetIsStackable() const { return bIsStackable; }
    void SetGridIndex(int32 Index) { GridIndex = Index; }
    int32 GetGridIndex() const { return GridIndex; }
    void SetInventoryItem(UTINV_InventoryItem* Item);
    UTINV_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
    UTINV_GlintedIcon* GetGlintedIcon() const { return GlintedIcon; }
    void UpdateStackCount(int32 StackCount) const;
    void SetPreview(bool bPreview) const;

protected:
    virtual void NativeOnInitialized() override;    

private:
    UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
    float PreviewIconOpacity = 0.65f;
	
    UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
    FSlateColor PreviewStackTextColor = FLinearColor(1.f, 0.85f, 0.f);

    FSlateColor DefaultStackTextColor;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> Text_StackCount;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTINV_GlintedIcon> GlintedIcon;

    int32 GridIndex = INDEX_NONE;
    TWeakObjectPtr<UTINV_InventoryItem> InventoryItem;
    bool bIsStackable = false;
};
#pragma endregion
/*-------------------------------------------------------------------------*/