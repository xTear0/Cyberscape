// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TINV_Highlightable.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
UINTERFACE()
class UTINV_Highlightable : public UInterface
{
	GENERATED_BODY()
};

/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_Highlightable.h_Class
class TECHYINV_API ITINV_Highlightable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "TECHY|Inventory")
	void Highlight();

	UFUNCTION(BlueprintNativeEvent, Category = "TECHY|Inventory")
	void UnHighlight();
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/
