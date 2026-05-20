// Copyright xTear Studios
// /*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Widgets/NewItemDescription/Inv_ItemDescriptionComposite.h"
#include "Inv_ItemDescriptionWidget.generated.h"
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
#pragma region Inv_ItemDescriptionWidget.h_Class
UCLASS()
class INVENTORY_API UInv_ItemDescriptionWidget : public UInv_ItemDescriptionComposite
{
	GENERATED_BODY()

public:

	FVector2D GetBoxSize() const;
	virtual void SetVisibility(ESlateVisibility InVisibility) override;
	
private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
};
#pragma endregion
/*-------------------------------------------------------------------------*/