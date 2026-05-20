// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "EquipmentManagement/ProxyMesh/Inv_ProxyMesh.h"
#include "EquipmentManagement/Components/Inv_EquipmentComponent.h"
#include "GameFramework/Character.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions			                                                   */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ProxyMesh.cpp_Functions
AInv_ProxyMesh::AInv_ProxyMesh()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(false);

	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	EquipmentComponent = CreateDefaultSubobject<UInv_EquipmentComponent>("Equipment");
	EquipmentComponent->SetOwningSkeletalMesh(Mesh);
	EquipmentComponent->SetIsProxy(true);
}

void AInv_ProxyMesh::BeginPlay()
{
	Super::BeginPlay();

	DelayedInitialization();
}

void AInv_ProxyMesh::DelayedInitializedOwner()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		DelayedInitialization();
		return;
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!IsValid(PC))
	{
		DelayedInitialization();
		return;
	}

	ACharacter* Character = Cast<ACharacter>(PC->GetPawn());
	if (!IsValid(Character))
	{
		DelayedInitialization();
		return;
	}

	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	if (!IsValid(CharacterMesh))
	{
		DelayedInitialization();
		return;
	}

	// Find the Mesh Component with "BindMesh" Component Tag, ensuring clean integration with GASP.
	TArray<UActorComponent*> Components = Character->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), FName("BindMesh"));
	if (Components.Num() > 0)
	{
		SourceMesh = Cast<USkeletalMeshComponent>(Components[0]);
	}
	else
	{
		SourceMesh = Character->GetMesh();
	}
	
	Mesh->SetSkeletalMesh(SourceMesh->GetSkeletalMeshAsset());
	Mesh->ComponentTags.Add(FName("BindMesh"));
	Mesh->SetAnimInstanceClass(AnimClass);

	EquipmentComponent->InitializeOwner(PC);
}

void AInv_ProxyMesh::DelayedInitialization()
{
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &ThisClass::DelayedInitializedOwner);
	GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
}
#pragma endregion
/*-------------------------------------------------------------------------*/