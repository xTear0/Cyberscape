// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "Widgets/Inventory/SlottedItems/Inv_SlottedItem.h"
#include "Inv_HoverItem.generated.h"
/*-------------------------------------------------------------------------*/


// The HoverItem is the widget that will appear and follow the mouse when
// an inventory item on the grid has been clicked.


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UImage;
class UTextBlock;
class UInv_InventoryItem;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*  Class Functionality									                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_HoverItem.h_Class
UCLASS()
class INVENTORY_API UInv_HoverItem : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FInv_ItemData GetItemData() { return ItemData; }
	
	void SetImageBrush(const UTexture2D& Texture2D, const FVector2D& DrawSize) const;
	void UpdateStackCount(const int32 Count);

	FGameplayTag GetItemType() const;
	int32 GetStackCount() const { return StackCount; };
	bool IsStackable() const { return bIsStackable; };
	void SetIsStackable(bool bStacks);
	int32 GetPreviousGridIndex() const { return PreviousGridIndex; };
	void SetPreviousGridIndex(int32 Index) { PreviousGridIndex = Index; };
	FIntPoint GetGridDimensions() const { return GridDimensions; };
	void SetGridDimensions(const FIntPoint& Dimensions) { GridDimensions = Dimensions; }
	UInv_InventoryItem* GetInventoryItem() const;
	void SetInventoryItem(UInv_InventoryItem* Item);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	mutable UMaterialInterface* BaseGlintMaterial;
	
private:

	// Material Management
	void CreateGlintDynamicMaterialInstance(const UTexture2D& Texture2D) const;
	
	UPROPERTY()
	mutable UMaterialInstanceDynamic* GlintDynamicMaterialInstance; // Item Glint

	void SetItemData(EInv_ItemRarity Rarity, EInv_ItemSpecialType Type, EInv_ItemEnhancement Enhancement);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_StackCount;

	FInv_ItemData ItemData;
	int32 PreviousGridIndex;
	FIntPoint GridDimensions;
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	bool bIsStackable{false};
	int32 StackCount{0};
};
#pragma endregion
/*-------------------------------------------------------------------------*/