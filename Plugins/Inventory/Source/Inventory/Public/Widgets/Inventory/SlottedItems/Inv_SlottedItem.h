// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_EnumTypes.h"
#include "Inv_SlottedItem.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UImage;
class UInv_InventoryItem;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSlottedItemClick, int32, GridIndex, const FPointerEvent&, MouseEvent);

USTRUCT(BlueprintType)
struct FInv_ItemData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	EInv_ItemRarity Rarity;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	EInv_ItemSpecialType SpecialType;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	EInv_ItemEnhancement Enhancement;
};
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_SlottedItem.h_Class
UCLASS()
class INVENTORY_API UInv_SlottedItem : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;

	// Blueprint Getters
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FVector2D GetImageIconSize() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FVector2D GetImageGlowSize() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetGlowSize(FVector2D& NewGlowSize);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FInv_ItemData GetItemData() { return ItemData; }
	
	bool IsStackable() const { return bIsStackable; }
	void SetIsStackable(bool bStackable) { bIsStackable = bStackable; }
	UImage* GetImageIcon() const { return Image_Icon; }
	UImage* GetImageGlow() const { return Image_Glow; }
	void SetGridIndex(int32 Index) { GridIndex = Index; }
	int32 GetGridIndex() const { return GridIndex; }
	void SetGridDimensions(const FIntPoint& Dimensions) { GridDimensions = Dimensions; }
	FIntPoint GetGridDimensions() const { return GridDimensions; }
	void SetInventoryItem(UInv_InventoryItem* Item);
	UInv_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
	virtual void SetImageBrush(const UTexture2D& Texture2D, const FVector2D& DrawSize) const;
	void UpdateStackCount(int32 StackCount) const;

	FSlottedItemClick OnSlottedItemClick;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UMaterialInterface* BaseGlowMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	mutable UMaterialInterface* BaseGlintMaterial;

private:
	
	// Material Management
	void CreateGlowDynamicMaterialInstance() const;
	void CreateGlintDynamicMaterialInstance(const UTexture2D& Texture2D) const;

	UPROPERTY()
	mutable UMaterialInstanceDynamic* GlowDynamicMaterialInstance; // Item Glow

	UPROPERTY()
	mutable UMaterialInstanceDynamic* GlintDynamicMaterialInstance; // Item Glint
	
	void SetItemData(EInv_ItemRarity Rarity, EInv_ItemSpecialType Type, EInv_ItemEnhancement Enhancement);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Glow;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_StackCount;
	
	FInv_ItemData ItemData;
	int32 GridIndex;
	FIntPoint GridDimensions;
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	bool bIsStackable{false};
};
#pragma endregion
/*-------------------------------------------------------------------------*/