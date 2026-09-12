// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TINV_GridSlot.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UImage;
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_GridSlot.h_Class
UCLASS

()
class TECHYINV_API UTINV_GridSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTileIndex(int32 Index) { TileIndex = Index; };
	int32 GetTileIndex() const { return TileIndex; };
protected:

private:

	int32 TileIndex;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_GridSlot;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
