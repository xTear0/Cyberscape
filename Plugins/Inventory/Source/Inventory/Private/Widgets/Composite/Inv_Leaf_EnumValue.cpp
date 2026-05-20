// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/Composite/Inv_Leaf_EnumValue.h"

#include "Components/Image.h"
#include "Types/Inv_EnumTypes.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_Leaf_EnumValue.cpp_Functions
void UInv_Leaf_EnumValue::NativePreConstruct()
{
	Super::NativePreConstruct();
	// Create a static function that takes an enum and spits out the correct image to use.
	// Sudo Code: set the image to the correct enum value.
}

void UInv_Leaf_EnumValue::SetEnumStarValue(EInv_ItemStar Stars)
{
	EnumStarValue = Stars;
	StarImage->SetBrushFromTexture(GetStarTextureFromEnum(Stars));
}

UTexture2D* UInv_Leaf_EnumValue::GetStarTextureFromEnum(EInv_ItemStar StarEnum) const
{
	if (StarEnum == EInv_ItemStar::NoStars) return nullptr;
	if (StarEnum == EInv_ItemStar::OneStar) return OneStar;
	if (StarEnum == EInv_ItemStar::TwoStar) return TwoStars;
	if (StarEnum == EInv_ItemStar::ThreeStar) return ThreeStars;
	if (StarEnum == EInv_ItemStar::FourStar) return FourStars;
	if (StarEnum == EInv_ItemStar::FiveStar) return FiveStars;
	if (StarEnum == EInv_ItemStar::SixStar) return SixStars;
	if (StarEnum == EInv_ItemStar::SevenStar) return SevenStars;

	return nullptr;
}

#pragma endregion
/*-------------------------------------------------------------------------*/
