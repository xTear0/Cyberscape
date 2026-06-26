// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OperatorPlayerController.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region OperatorPlayerController.h_Class
UCLASS()
class CYBERSCAPE_API AOperatorPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AOperatorPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputMappingContext> OperatorIMC;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> CrouchAction;


	void Input_Crouch();
	void Input_Jump();
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/