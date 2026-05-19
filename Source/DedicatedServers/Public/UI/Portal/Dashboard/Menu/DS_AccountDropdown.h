// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "DS_MenuDropdown.h"
#include "DS_AccountDropdown.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UDS_LocalPlayerSubsystem;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_AccountDropdown.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_AccountDropdown : public UDS_MenuDropdown
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	
private:
	UDS_LocalPlayerSubsystem* GetLocalPlayerSubsystem() const;
};
#pragma endregion
/*-------------------------------------------------------------------------*/