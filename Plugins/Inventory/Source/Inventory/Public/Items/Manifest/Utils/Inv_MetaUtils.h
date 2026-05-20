// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Inv_MetaUtils.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
enum class EInv_AttributeScalarPower : uint8;
enum class EInv_SecondaryAttributeRules : uint8;
enum class EInv_AttributeEntry : uint8;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*  Class Functionality									                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_MetaUtils.h_Class
UCLASS()
class INVENTORY_API UInv_MetaUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Inventory|MetaUtils")
	static int GetRandIntFromBaseScalar(const EInv_AttributeScalarPower BaseScalar);

	UFUNCTION(BlueprintCallable, Category = "Inventory|MetaUtils")
	static int GetRandIntFromMultScalar(const EInv_AttributeScalarPower MultScalar);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|MetaUtils")
	static TArray<EInv_AttributeEntry> GetValidAttributeList(TArray<EInv_SecondaryAttributeRules> Rules);

private:
	static TMap<EInv_SecondaryAttributeRules, TArray<EInv_AttributeEntry>> GetRuleToAttributeMap();
};
#pragma endregion
/*-------------------------------------------------------------------------*/