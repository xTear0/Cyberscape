// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_ItemDescriptionCompositeBase.generated.h"
/*-------------------------------------------------------------------------*/


// The Inv_ItemDescriptionCompositeBase is a base class that provides basic
// functionality to the leafs and the main item description. Namely, it allows
// for the sub objects to expand and collapse, as well as lays the groundwork
// for the ApplyFunction which allows the leaves to have the correct data.


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemDescriptionCompositeBase.h_Class
UCLASS()
class INVENTORY_API UInv_ItemDescriptionCompositeBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void Collapse();
	void Expand();

	//using FuncType = TFunction<void(UInv_CompositeBase*)>;
	//	virtual void ApplyFunction(FuncType Function) {}
};
#pragma endregion
/*-------------------------------------------------------------------------*/