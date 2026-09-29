// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "TINV_HeldItemSubsystem.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTINV_HoverItem;
class UTINV_InventoryGrid;
class UTINV_InventoryItem;
class UUserWidget;

DECLARE_MULTICAST_DELEGATE(FTINV_OnHeldItemChanged);
/*-------------------------------------------------------------------------*/

/*
 * The single item a local player is holding on the cursor, shared by every
 * inventory grid on screen. Grids read and write it; this subsystem owns the
 * cursor widget that draws it.
 */

/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_HeldItemSubsystem.h_Class
UCLASS()
class TECHYINV_API UTINV_HeldItemSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	// Lookup from any widget owned by a local player.
	static UTINV_HeldItemSubsystem* Get(const UUserWidget* Widget);

	virtual void Deinitialize() override;

	/* State */
	void Hold(UTINV_InventoryItem* Item, int32 StackCount, UTINV_InventoryGrid* InSourceGrid, int32 InSourceIndex);
	void SetHeldCount(int32 NewCount);
	void ClearHeld();

	bool IsHolding() const { return HeldItem.IsValid(); }
	UTINV_InventoryItem* GetHeldItem() const { return HeldItem.Get(); }
	int32 GetHeldCount() const { return HeldCount; }
	UTINV_InventoryGrid* GetSourceGrid() const { return SourceGrid.Get(); }
	int32 GetSourceIndex() const { return SourceIndex; }

	/* Drag distribute: one session spanning every grid */
	bool IsDragging() const { return bIsDragging; }
	void BeginDrag();
	bool CanAddDragTarget() const { return bIsDragging && DragTargets.Num() < DragSourceCount; }
	void AddDragTarget(UTINV_InventoryGrid* Grid, int32 Index);
	void UpdateDragPreview();
	void CommitDrag();
	void CancelDrag();

	/* Cursor */
	// The hover item is a software cursor, which Slate only re-evaluates on mouse movement.
	void RefreshCursor();

	// Fires whenever what's held, or how many, changes, from any grid.
	FTINV_OnHeldItemChanged OnHeldItemChanged;

private:
	struct FDragTarget
	{
		TWeakObjectPtr<UTINV_InventoryGrid> Grid;
		int32 Index = INDEX_NONE;
	};

	bool bIsDragging = false;
	int32 DragSourceCount = 0;
	TArray<FDragTarget> DragTargets;

	int32 GetDragShare() const;
	void EndDrag(); // Tells every involved grid to clear its previews, then resets.
	
	UPROPERTY()
	TObjectPtr<UTINV_HoverItem> HoverItemWidget;

	TWeakObjectPtr<UTINV_InventoryItem> HeldItem;
	int32 HeldCount = 0;

	// Where the held item came from, for putting it back later.
	TWeakObjectPtr<UTINV_InventoryGrid> SourceGrid;
	int32 SourceIndex = INDEX_NONE;

	APlayerController* GetPlayerController() const;
	UTINV_HoverItem* GetOrCreateWidget(const UTINV_InventoryGrid* VisualSource);
	void ShowWidget(const UTINV_InventoryGrid* VisualSource);
	void HideWidget();
};
#pragma endregion
/*-------------------------------------------------------------------------*/