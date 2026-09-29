// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Widgets/Inventory/InventoryBase/TINV_InventoryBase.h"
#include "TINV_SpatialInventory.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTINV_InventoryGrid;
class UTINV_InventoryItem;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_SpatialInventory.h_Class
UCLASS()
class TECHYINV_API UTINV_SpatialInventory : public UTINV_InventoryBase
{
	GENERATED_BODY()

public:
	virtual FTINV_SlotAvailabilityResult HasRoomForItem(UTINV_ItemComponent* ItemComponent) const override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void SetMenuOpen(bool bOpen, bool bInstant = false) override;
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;

	// Blueprint decides what else hides or fades. Use Hidden, not Collapsed,
	// so the vertical box keeps its shape and the hotbar doesn't move.
	UFUNCTION(BlueprintImplementableEvent, Category = "TECHY|Inventory")
	void BP_OnMenuOpenChanged(bool bOpen, bool bInstant);
	
private:
	bool bDockOffsetReady = false;
	bool TryComputeDockOffsetY(float& OutOffsetY) const;
	
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory|Hotbar Dock", meta = (ClampMin = "0.0"))
	float DockDuration = 0.25f;

	// Gap between the docked hotbar and the bottom of the screen, in slate units.
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory|Hotbar Dock")
	float DockBottomMargin = 24.f;

	bool bMenuOpen = false;
	float DockAlpha = 1.f;   // 0 = in the menu, 1 = docked at the bottom.
	float DockOffsetY = 0.f;
	
	void ReturnHeldItem();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTINV_InventoryGrid> InventoryGrid;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTINV_InventoryGrid> InventoryHotbar;

	// Placement priority: inventory first, then hotbar.
	TArray<const UTINV_InventoryGrid*> GetGridsInPriorityOrder() const { return { InventoryGrid, InventoryHotbar }; }
	void ApplyToAllGrids(const FTINV_SlotAvailabilityResult& Result) const;

	UFUNCTION()
	void OnItemAdded(UTINV_InventoryItem* Item);

	UFUNCTION()
	void OnStackChange(const FTINV_SlotAvailabilityResult& Result);

	UFUNCTION()
	void OnHotbarSwapRequested(int32 HotbarIndex);

	UTINV_InventoryGrid* GetHoveredGrid() const;
	static void SwapSlots(UTINV_InventoryGrid* GridA, int32 IndexA, UTINV_InventoryGrid* GridB, int32 IndexB);
};
#pragma endregion
/*-------------------------------------------------------------------------*/
