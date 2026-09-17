// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TINV_ItemMetadata.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
USTRUCT()
struct FTINV_ItemMeta
{
	GENERATED_BODY()
	FTINV_ItemMeta() {}
	FTINV_ItemMeta(const FTINV_ItemMeta&) = default;
	FTINV_ItemMeta& operator=(const FTINV_ItemMeta&) = default;
	FTINV_ItemMeta(FTINV_ItemMeta&&) = default;
	FTINV_ItemMeta& operator=(FTINV_ItemMeta&&) = default;
	virtual ~FTINV_ItemMeta() {}

	FGameplayTag GetMetaTag() const { return MetaTag; }
	void SetMetaTag(FGameplayTag Tag) { MetaTag = Tag; }

private:
	UPROPERTY(EditAnywhere, Category = "TECHY|Inventory")
	FGameplayTag MetaTag;
};
/*-------------------------------------------------------------------------*/
