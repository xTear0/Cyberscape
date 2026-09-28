// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/TINV_EnumTypes.h"
#include "TINV_GlintedIcon.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UImage;
class UMaterialInstanceDynamic;
class UMaterialInterface;
class UTexture2D;
class UTINV_InventoryItem;
class UTINV_ItemComponent;
class UTINV_ItemDataTable;
struct FTINV_ItemManifest;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_GlintedIcon.h_Class
UCLASS()
class TECHYINV_API UTINV_GlintedIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	UTINV_GlintedIcon(const FObjectInitializer& ObjectInitializer);

	/** Sets the icon texture and glint tier directly. Scrap = no glint by default. */
	UFUNCTION(BlueprintCallable, Category = "TECHY|Inventory|Glint")
	void SetIcon(UTexture2D* Icon, ETINV_ItemTier GlintTier = ETINV_ItemTier::Scrap);

	/** Looks up icon + tier in the ItemDataTable. Returns false (and clears) if no data was found. */
	UFUNCTION(BlueprintCallable, Category = "TECHY|Inventory|Glint")
	bool SetFromItemComponent(const UTINV_ItemComponent* ItemComponent);

	UFUNCTION(BlueprintCallable, Category = "TECHY|Inventory|Glint")
	bool SetFromInventoryItem(const UTINV_InventoryItem* Item);

	bool SetFromManifest(const FTINV_ItemManifest& Manifest);

	UFUNCTION(BlueprintCallable, Category = "TECHY|Inventory|Glint")
	void SetGlintTier(ETINV_ItemTier GlintTier);

	UFUNCTION(BlueprintCallable, Category = "TECHY|Inventory|Glint")
	void ClearIcon();

	void SetItemDataTable(UTINV_ItemDataTable* InItemDataTable) { ItemDataTable = InItemDataTable; }

	ETINV_ItemTier GetGlintTier() const { return CurrentGlintTier; }
	UTexture2D* GetIcon() const { return CurrentIcon; }
	UImage* GetIconImage() const { return Image_Icon; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TECHY|Inventory|Glint")
	FName GlintTextureParam = TEXT("Texture");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TECHY|Inventory|Glint")
	FName GlintTextureObjectParam = TEXT("Texture Object");

protected:
	virtual void NativeOnInitialized() override;

private:
	UMaterialInstanceDynamic* GetGlintMID();
	void ApplyGlint();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Glint;

	/** One glint material per tier. Missing or null entry = that tier shows no glint. */
	UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory|Glint", meta = (ForceInlineRow))
	TMap<ETINV_ItemTier, TObjectPtr<UMaterialInterface>> GlintMaterials;

	/** Used by the SetFrom* helpers. Can be set here or injected with SetItemDataTable. */
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory|Glint")
	TObjectPtr<UTINV_ItemDataTable> ItemDataTable;

	UPROPERTY(Transient)
	TObjectPtr<UMaterialInstanceDynamic> GlintMID;

	UPROPERTY(Transient)
	TObjectPtr<UTexture2D> CurrentIcon;

	ETINV_ItemTier CurrentGlintTier = ETINV_ItemTier::Scrap;
	ESlateVisibility IconVisibility = ESlateVisibility::HitTestInvisible;
};
#pragma endregion
/*-------------------------------------------------------------------------*/