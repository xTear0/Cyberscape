// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inv_Highlightable.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
UINTERFACE()
class INVENTORY_API UInv_Highlightable : public UInterface
{
	GENERATED_BODY()
};
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_Highlightable.h_Functions
class INVENTORY_API IInv_Highlightable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Inv_Highlightable")
	void Highlight();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Inv_Highlightable")
	void UnHighlight();

};
#pragma endregion
/*-------------------------------------------------------------------------*/