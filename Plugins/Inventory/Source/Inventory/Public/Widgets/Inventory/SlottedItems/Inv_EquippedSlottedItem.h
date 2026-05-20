// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_SlottedItem.h"
#include "Inv_EquippedSlottedItem.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquippedSlottedItemClicked, class UInv_EquippedSlottedItem*, SlottedItem);
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_EquippedSlottedItem.h_Class
UCLASS()
class INVENTORY_API UInv_EquippedSlottedItem : public UInv_SlottedItem
{
	GENERATED_BODY()

public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void SetImageBrush(const UTexture2D& Texture2D, const FVector2D& DrawSize);
	
	void SetEquipmentTypeTag(const FGameplayTag& Tag) { EquippmentTypeTag = Tag; }
	FGameplayTag GetEquipmentTypeTag() const { return EquippmentTypeTag; }

	FEquippedSlottedItemClicked OnEquippedSlottedItemClicked;
	
private:

	void SetWidgetSize();
	
	UPROPERTY()
	FGameplayTag EquippmentTypeTag;
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/