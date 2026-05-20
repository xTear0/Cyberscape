// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/Inv_EnumTypes.h"
#include "Inv_WidgetUtils.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
struct FGameplayTag;
struct FInv_ItemData;
enum class EInv_ItemAttribute : uint8;


USTRUCT(BlueprintType, Category = "Inventory")
struct FInv_ItemGlowMaterialData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FLinearColor RarityColor;

	UPROPERTY(BlueprintReadOnly)
	float GodRayIntensity = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float GodRayPow = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float DistortionGlow = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float StarsBrightness = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float PrismaticBlend = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float PrismaticIntensity = 0.f;
};

USTRUCT(BlueprintType, Category = "Inventory")
struct FInv_ItemGlintMaterialData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FLinearColor GlintColor;

	UPROPERTY(BlueprintReadOnly)
	float ColorOpacity = 1.f;
	
	UPROPERTY(BlueprintReadOnly)
	float PrismaticBlend = 0.f;
};
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*  Class Functionality									                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_WidgetUtils.h_Class
UCLASS()
class INVENTORY_API UInv_WidgetUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Static Functions for Fetching Material Data for Item Displays

	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FInv_ItemGlowMaterialData GetItemGlowData(FInv_ItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FInv_ItemGlintMaterialData GetItemGlintData(FInv_ItemData ItemData);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FVector2D GetWidgetPosition(UWidget* Widget);

	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FVector2D GetWidgetSize(UWidget* Widget);

	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FLinearColor GetColorFromColorEnum(EInv_Colors RequestedColor);

	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FLinearColor GetColorFromRarityEnum(EInv_ItemRarity RequestedRarity);

	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FLinearColor GetHalfOpacityColorFromRarityEnum(EInv_ItemRarity RequestedRarity);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FLinearColor GetColorFromAttributeTag(FGameplayTag RequestedAttributeTag);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FText GetPrefixFromRarityEnum(EInv_ItemRarity RequestedRarity);

	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FText GetItemTypeNameFromTag(FGameplayTag ItemType);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FText GetAttributeTextLabel(FGameplayTag RequestedAttributeTag);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FText GetAttributeTextName(FGameplayTag RequestedAttributeTag);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static FText GetSignedAttributeValueFromInt(int32 RequestedValue);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static bool IsWithinBounds(const FVector2D& BoundaryPos, const FVector2D& WidgetSize, const FVector2D& MousePos);

	UFUNCTION(BlueprintCallable, Category = "Inventory|WidgetUtils")
	static bool IsWithinWidgetBounds(const FVector2D& WidgetPos, const FVector2D& WidgetSize, const FVector2D& MousePos);
	
	static FVector2D GetClampedWidgetPosition(const FVector2D& Boundary, const FVector2D& WidgetSize, const FVector2D& MousePosition);
	static int32 GetIndexFromPosition(const FIntPoint& Position, const int32 Columns);
	static FIntPoint GetPositionFromIndex(const int32 Index, const int32 Columns);
};
#pragma endregion
/*-------------------------------------------------------------------------*/