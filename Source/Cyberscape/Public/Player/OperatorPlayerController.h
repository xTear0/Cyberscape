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
class UTINV_HUDWidget;
class UTINV_InventoryComponent;
class UTINV_ItemDataTable;
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
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "TECHY|Inventory")
	void Input_ToggleInventory();

	UFUNCTION(BlueprintCallable, Category = "TECHY|Inventory")
	bool IsInventoryOpen() const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

private:

	
	TWeakObjectPtr<UTINV_InventoryComponent> InventoryComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "CYBERSCAPE|Inventory")
	TSubclassOf<UTINV_HUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UTINV_HUDWidget> HUDWidget;

	UPROPERTY(EditDefaultsOnly, Category = "CYBERSCAPE|Inventory")
	double ItemTraceLength;
	
	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputMappingContext> OperatorIMC;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> PrimaryInteractAction;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> ToggleInventoryAction;
	
	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category = "CYBERSCAPE|Input")
	TObjectPtr<UInputAction> CrouchAction;

	void Input_PrimaryInteract();
	void Input_Crouch();
	void Input_Jump();
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);

	void CreateHUDWidget();
	void TraceForItem();

	UPROPERTY(EditDefaultsOnly, Category = "CYBERSCAPE|Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "TECHY|Inventory")
	TObjectPtr<UTINV_ItemDataTable> ItemDataTable;

	TWeakObjectPtr<AActor> ThisActor;
	TWeakObjectPtr<AActor> LastActor;
	
};
#pragma endregion
/*-------------------------------------------------------------------------*/