// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_PlayerLabel.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UTextBlock;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_PlayerLabel.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_PlayerLabel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetUsername(const FString& Username) const;
	FString GetUsername() const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Username; 
};
#pragma endregion
/*-------------------------------------------------------------------------*/