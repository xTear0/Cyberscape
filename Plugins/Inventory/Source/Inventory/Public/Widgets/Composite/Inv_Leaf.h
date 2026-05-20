// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Inv_CompositeBase.h"
#include "Inv_Leaf.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Delcarations	                                                       */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_Leaf.h_Class
UCLASS()
class INVENTORY_API UInv_Leaf : public UInv_CompositeBase
{
	GENERATED_BODY()
public:
	virtual void ApplyFunction(FuncType Function) override;	
};
#pragma endregion
/*-------------------------------------------------------------------------*/