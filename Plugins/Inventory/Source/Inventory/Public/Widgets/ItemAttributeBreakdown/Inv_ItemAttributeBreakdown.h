// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "EquipmentManagement/Modifications/Inv_AttributeModificationHandler.h"
#include "Inv_ItemAttributeBreakdownLine.h"
#include "Inv_ItemAttributeBreakdown.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations		                                                   */
/*-------------------------------------------------------------------------*/
class USizeBox;
class UTextBlock;
class UVerticalBox;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemAttributeBreakdown.h_Class
UCLASS()
class INVENTORY_API UInv_ItemAttributeBreakdown : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category =  "Attribute Inspection")
	TSubclassOf<UInv_ItemAttributeBreakdownLine> BreakdownLineEntry;

	void ClearAllEntries() const;
	
	FVector2D GetBoxSize() const;
	virtual void SetVisibility(ESlateVisibility InVisibility) override;
	void SetAttributeTag(FGameplayTag InTag) { AttributeTag = InTag; }
	
	void SetItemAttributeBreakdownData(const FHoverInspectResult& InResult) const;
	
	UFUNCTION(BlueprintCallable)
	FGameplayTag GetAttributeTag() const { return AttributeTag; }
	
private:
	void CreateLineEntry(const FInv_ItemPayloadDataEntry& DataEntry) const;
	
	FGameplayTag AttributeTag;
		
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AttributeName;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TotalValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TotalText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> LineContainer;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
