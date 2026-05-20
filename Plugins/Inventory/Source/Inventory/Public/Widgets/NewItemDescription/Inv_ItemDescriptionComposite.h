// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Inv_ItemDescriptionCompositeBase.h"
#include "Inv_ItemDescriptionComposite.generated.h"
/*-------------------------------------------------------------------------*/


// The Inv_ItemDescriptionComposite is a subclass of the Inv_ItemDescriptionCompositeBase
// which has basic functions, and this one is specifically designed to be the
// item information display carrier.



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemDescriptionComposite.h_Class
UCLASS()
class INVENTORY_API UInv_ItemDescriptionComposite : public UInv_ItemDescriptionCompositeBase
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	//virtual void ApplyFunction(FuncType Function) override;
	virtual void Collapse() override;
	TArray<UInv_ItemDescriptionCompositeBase*> GetChildren() { return Children; }
	
private:
	UPROPERTY()
	TArray<TObjectPtr<UInv_ItemDescriptionCompositeBase>> Children;
};
#pragma endregion
/*-------------------------------------------------------------------------*/