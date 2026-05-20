// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Chaos/Deformable/MuscleActivationConstraints.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"
#include "Widgets/Inventory/SlottedItems/Inv_SlottedItem.h"
#include "Inv_SpatialInventory.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class AHeroPlayerState;
class UInv_AttributeModificationHandler;
class UInv_InventoryGrid;
class UInv_ItemDescription;
class UWidgetSwitcher;
class UButton;
class UCanvasPanel;
class UInv_EquippedGridSlot;
class UInv_EquippedSlottedItem;
class UInv_HoverItem;
class UInv_ItemAttributeBreakdown;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_SpatialInvetory.h_Class
UCLASS()
class INVENTORY_API UInv_SpatialInventory : public UInv_InventoryBase
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual FInv_SlotAvailabilityResult HasRoomForItem(UInv_ItemComponent* ItemComponent) const override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeTick(const  FGeometry& MyGeometry, float DeltaTime) override;
	
	virtual void OnItemHovered(UInv_InventoryItem* Item) override;
	virtual void OnItemUnhovered() override;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void OnAttributeHovered(bool bShow, FGameplayTag AttributeTag, FHoverInspectResult BreakdownInfo);
	
	virtual bool HasHoverItem() const override;
	virtual UInv_HoverItem* GetHoverItem() const override;
	virtual float GetTileSize() const override;
	
private:

	// Private Properties
	UPROPERTY()
	TArray<TObjectPtr<UInv_EquippedGridSlot>> EquippedGridSlots;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> GridSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> BackgroundSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InventoryGrid> Grid_Equippables;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InventoryGrid> Grid_Consumables;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InventoryGrid> Grid_Craftables;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Equippables;
	
	UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Button_Consumables;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Craftables;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidget> Background_Equippables;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidget> Background_Consumables;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidget> Background_Craftables;

	UPROPERTY(EditAnywhere, Category =  "Inventory")
	TSubclassOf<UInv_ItemDescription> ItemDescriptionClass;

	UPROPERTY(EditAnywhere, Category =  "Attribute Inspection")
	TSubclassOf<UInv_ItemAttributeBreakdown> AttributeInspectionClass;

	UPROPERTY()
	TObjectPtr<UInv_ItemDescription> ItemDescription;

	UPROPERTY()
	TObjectPtr<UInv_ItemAttributeBreakdown> AttributeInspectBreakdown;

	static FInv_ItemData MakeItemData(UInv_InventoryItem* InventoryItem);
	static FInv_ItemData MakeEmptyItemData();
	
	UInv_ItemDescription* GetItemDescription(const FInv_ItemData& InData = MakeEmptyItemData(), bool UseRarity = {false});
	UInv_ItemAttributeBreakdown* GetAttributeBreakdown();
	
	FTimerHandle DescriptionTimer;				// Item Description timer handle, the delay before showing it.
	FTimerHandle AttributeBreakdownTimer;		// Attribute Breakdown timer handle, the delay before showing it.

	UPROPERTY(EditAnywhere, Category =  "Inventory")
	float DescriptionTimerDelay = 0.5f;

	UPROPERTY(EditAnywhere, Category =  "Attribute Inspection")
	float AttributeInspectionTimerDelay = 0.5f;


	// Callbacks
	UFUNCTION()
	void ShowEquippables();
	
	UFUNCTION()
	void ShowConsumables();
	
	UFUNCTION()
	void ShowCraftables();

	UFUNCTION()
	void EquippedGridSlotClicked(UInv_EquippedGridSlot* EquippedGridSlot, const FGameplayTag& EquipmentTypeTag);

	UFUNCTION()
	void EquippedSlottedItemClicked(UInv_EquippedSlottedItem* EquippedSlottedItem);
	// End Callbacks

	UFUNCTION()
	void OnGlobalAttributeHover(bool bShow, FGameplayTag AttributeTag);
    
	void BindToAttributeHoverSubsystem();

	UPROPERTY()
	TObjectPtr<class UAttributeHoverSubsystem> AttributeHoverSubsystem;
	
	
	void DisableButton(UButton* Button);
	void SetActiveGrid(UInv_InventoryGrid* Grid, UWidget* Background, UButton* Button);
		void SetItemDescriptionSizeAndPosition(UInv_ItemDescription* Description, UCanvasPanel* Canvas) const;
		void SetAttributeBreakdownSizeAndPosition(UInv_ItemAttributeBreakdown* AttributeBreakdown, UCanvasPanel* Canvas) const;
	bool CanEquipHoverItem(UInv_EquippedGridSlot* EquippedGridSlot, const FGameplayTag& EquipmentTypeTag) const;
	UInv_EquippedGridSlot* FindSlotWithEquippedItem(UInv_InventoryItem* EquippedItem) const;
	void ClearSlotOfItem(UInv_EquippedGridSlot* EquippedGridSlot);
	void RemoveEquippedSlottedItem(UInv_EquippedSlottedItem* EquippedSlottedItem);
	void MakeEquippedSlottedItem(UInv_EquippedSlottedItem* EquippedSlottedItem, UInv_EquippedGridSlot* EquippedGridSlot, UInv_InventoryItem* ItemToEquip);
	void BroadcastSlotClickedDelegates(UInv_InventoryItem* ItemToEquip, UInv_InventoryItem* ItemToUnequip) const;
	bool CanSwapItems(FGameplayTag ItemToEquipTag, FGameplayTag ItemToUnequipTag, FGameplayTag EquippedGridSlotTag) const;
	
	TWeakObjectPtr<UInv_InventoryGrid> ActiveGrid;
};
#pragma endregion
/*-------------------------------------------------------------------------*/