// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TINV_WidgetUtils.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_WidgetUtils.h_Class
UCLASS()
class TECHYINV_API UTINV_WidgetUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static int32 GetIndexFromPosition(const FIntPoint& Position, const int32 Columns);

protected:

private:
};
#pragma endregion
/*-------------------------------------------------------------------------*/
