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
enum class ETINV_ItemTier : uint8;
enum class ECUI_ItemTier : uint8;
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
	static FIntPoint GetPositionFromIndex(const int32 Index, const int32 Columns);
	static ECUI_ItemTier GetCUIItemTier(const ETINV_ItemTier Tier);
	static const TCHAR* GetTierColorToken(const ETINV_ItemTier Tier);
    
protected:

private:
};
#pragma endregion
/*-------------------------------------------------------------------------*/