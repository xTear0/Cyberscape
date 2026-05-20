// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Items/Inv_ItemDataAsset.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Inv_JsonConversionUtils.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
struct FInv_ItemDefinition;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*  Class Functionality									                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_JsonConversionUtils.h_Class
UCLASS()
class INVENTORY_API UInv_JsonConversionUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Json Utils")
	FInv_ItemDefinition GetItemDefinition(FName ItemID);
	
	UFUNCTION(BlueprintCallable, Category = "Json Utils")
	static EInv_ItemRarity GetRarityEnumFromString(FString RarityString);

	/*UFUNCTION(BlueprintCallable, Category = "Json Utils")
	static int32 GetInt32FromString(FString Int32String);

	UFUNCTION(BlueprintCallable, Category = "Json Utils")
	static int GetIntFromString(FString IntString);*/

	UFUNCTION(BlueprintCallable, Category = "Json Utils")
	static FGameplayTag GetGameplayTagFromString(FString GameplayTagString);
};
#pragma endregion
/*-------------------------------------------------------------------------*/