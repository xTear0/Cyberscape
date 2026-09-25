// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TINV_ActorItemBase.generated.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region TINV_ActorItemBase.h_Class
UCLASS()
class TECHYINV_API ATINV_ActorItemBase : public AActor
{
	GENERATED_BODY()

public:
	ATINV_ActorItemBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> BobPivot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Settings")
	float StartHeightOffset = 20.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TECHY|Settings")
	float BobHeight = 15.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TECHY|Settings")
	float BobSpeed = 2.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TECHY|Settings")
	float RotationSpeed = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TECHY|Settings")
	bool bRandomizeStartPhase = true;

private:
	float RunningTime = 0.f;
	FVector StartLocation = FVector::ZeroVector;

};
#pragma endregion
/*-------------------------------------------------------------------------*/
