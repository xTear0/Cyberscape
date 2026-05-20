// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Inv_Leaf.h"
#include "Inv_Leaf_EnumValue.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Delcarations	                                                       */
/*-------------------------------------------------------------------------*/
class UTexture2D;
class UImage;
enum class EInv_ItemStar : uint8;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_Leaf_EnumValue.h_Class
UCLASS()
class INVENTORY_API UInv_Leaf_EnumValue : public UInv_Leaf
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	void SetEnumStarValue(EInv_ItemStar Stars);
	UTexture2D* GetStarTextureFromEnum(EInv_ItemStar StarEnum) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory|Widgets")
	EInv_ItemStar GetEnumValue() { return EnumStarValue; };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayProperties")
	UTexture2D* OneStar;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayProperties")
	UTexture2D* TwoStars;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayProperties")
	UTexture2D* ThreeStars;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayProperties")
	UTexture2D* FourStars;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayProperties")
	UTexture2D* FiveStars;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayProperties")
	UTexture2D* SixStars;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayProperties")
	UTexture2D* SevenStars;

private:

	UPROPERTY()
	EInv_ItemStar EnumStarValue;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> StarImage;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
