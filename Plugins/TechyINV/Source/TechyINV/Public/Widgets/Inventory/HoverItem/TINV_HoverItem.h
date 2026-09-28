// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TINV_HoverItem.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;
class USizeBox;
class UTINV_GlintedIcon;
class UTINV_InventoryItem;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_HoverItem.h_Class
UCLASS()
class TECHYINV_API UTINV_HoverItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInventoryItem(UTINV_InventoryItem* Item);
	UTINV_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
	UTINV_GlintedIcon* GetGlintedIcon() const { return GlintedIcon; }
	void UpdateStackCount(const int32 NewStackCount);
	void SetDisplaySize(float Size);
	int32 GetStackCount() const { return StackCount; }
	void SetPreviousGridIndex(const int32 NewIndex) { PreviousGridIndex = NewIndex; }
	int32 GetPreviousGridIndex() const { return PreviousGridIndex; }
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_StackCount;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTINV_GlintedIcon> GlintedIcon;

	int32 PreviousGridIndex{INDEX_NONE};
	TWeakObjectPtr<UTINV_InventoryItem> InventoryItem;
	bool bIsStackable{false};
	int32 StackCount{0};
};
#pragma endregion
/*-------------------------------------------------------------------------*/