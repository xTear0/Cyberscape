// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "TINV_Highlightable.h"
#include "Components/StaticMeshComponent.h"
#include "TINV_HighlightableStaticMesh.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_HighlightableStaticMesh.h_Class
UCLASS

()
class TECHYINV_API UTINV_HighlightableStaticMesh : public UStaticMeshComponent, public ITINV_Highlightable
{
	GENERATED_BODY()

public:
	virtual void Highlight_Implementation() override;
	virtual void UnHighlight_Implementation() override;

private:
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	TObjectPtr<UMaterialInterface> HighlightMaterial;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
