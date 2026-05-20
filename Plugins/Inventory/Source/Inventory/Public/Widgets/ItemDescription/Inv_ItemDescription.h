// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "IDetailTreeNode.h"
#include "Types/Inv_EnumTypes.h"
#include "Widgets/Composite/Inv_Composite.h"
#include "Widgets/Inventory/SlottedItems/Inv_SlottedItem.h"
#include "Inv_ItemDescription.generated.h"
/*-------------------------------------------------------------------------*/


/* The Item Description widget that shows up when hovering over an item. */


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class USizeBox;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*  Class Functionality									                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemDescription.h_Class
UCLASS()
class INVENTORY_API UInv_ItemDescription : public UInv_Composite
{
	GENERATED_BODY()

public:

	FVector2D GetBoxSize() const;
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FInv_ItemData& GetItemData() { return ItemData; }

	void SetItemData(const FInv_ItemData& InData) { ItemData = InData; }
	
private:
	
	FInv_ItemData ItemData;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
};
#pragma endregion
/*-------------------------------------------------------------------------*/