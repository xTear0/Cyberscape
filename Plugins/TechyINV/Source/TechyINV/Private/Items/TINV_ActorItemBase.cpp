// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Items/TINV_ActorItemBase.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region TINV_ActorItemBase.cpp_Functions
ATINV_ActorItemBase::ATINV_ActorItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
 
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BobPivot = CreateDefaultSubobject<USceneComponent>(TEXT("BobPivot"));
	BobPivot->SetupAttachment(Root);

	// Hey! Make sure I get:
	// - BP_TINV_Item_Component (with Tag)
	// - BP_HighlightableStaticMesh
}

void ATINV_ActorItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = BobPivot->GetRelativeLocation() + FVector(0.f, 0.f, StartHeightOffset);
	
	if (bRandomizeStartPhase)
	{
		RunningTime = FMath::FRandRange(0.f, 10.f);
	}
}

void ATINV_ActorItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
 
	RunningTime += DeltaTime;
	
	const float ZOffset = FMath::Sin(RunningTime * BobSpeed) * BobHeight;
	BobPivot->SetRelativeLocation(StartLocation + FVector(0.f, 0.f, ZOffset));
	BobPivot->AddLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
}
#pragma endregion
/*-------------------------------------------------------------------------*/
