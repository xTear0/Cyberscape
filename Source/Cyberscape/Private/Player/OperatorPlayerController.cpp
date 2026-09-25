// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Cyberscape/Public/Player/OperatorPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/OperatorCharacter.h"
#include "GameFramework/Character.h"
#include "Widgets/HUD/TINV_HUDWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interaction/TINV_Highlightable.h"
#include "InventoryManagement/Components/TINV_InventoryComponent.h"
#include "ItemData/TINV_ItemDataTable.h"
#include "Items/Components/TINV_ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Notifications/CUI_NotificationManager.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region OperatorPlayerController.cpp_Functions
AOperatorPlayerController::AOperatorPlayerController()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	ItemTraceLength = 1000.0;
	ItemTraceChannel = ECC_GameTraceChannel2;
}

void AOperatorPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsInventoryOpen())
	{
		TraceForItem();
	}
}

void AOperatorPlayerController::Input_ToggleInventory()	
{
	if (!InventoryComponent.IsValid()) return;
	InventoryComponent->ToggleInventoryMenu();
	if (AOperatorCharacter* LocalOperatorCharacter = Cast<AOperatorCharacter>(GetPawn()))
	{
		LocalOperatorCharacter->ReleaseCombatInput();
	}
}

bool AOperatorPlayerController::IsInventoryOpen() const
{
	if (!IsValid(InventoryComponent.Get())) return false;
	return InventoryComponent.Get()->IsInventoryOpen();
}

void AOperatorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(OperatorIMC, 0);
	}

	InventoryComponent = FindComponentByClass<UTINV_InventoryComponent>();
	check(ItemDataTable); // Ensure that the Item Data is available.
	
	CreateHUDWidget();
}

void AOperatorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* OperatorInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	OperatorInputComponent->BindAction(PrimaryInteractAction, ETriggerEvent::Started, this, &AOperatorPlayerController::Input_PrimaryInteract);
	OperatorInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &AOperatorPlayerController::Input_ToggleInventory);
	OperatorInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOperatorPlayerController::Input_Move);
	OperatorInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOperatorPlayerController::Input_Look);
	OperatorInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AOperatorPlayerController::Input_Jump);
	OperatorInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AOperatorPlayerController::Input_Crouch);
}

void AOperatorPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (APawn* P = GetPawn())
	{
		InventoryComponent = P->FindComponentByClass<UTINV_InventoryComponent>();
	}
}

void AOperatorPlayerController::Input_PrimaryInteract()
{
	if (!ThisActor.IsValid()) return;
	
	UTINV_ItemComponent* ItemComponent = ThisActor->FindComponentByClass<UTINV_ItemComponent>();
	if (!IsValid(ItemComponent) || !InventoryComponent.IsValid()) return;
	
	InventoryComponent->TryAddItem(ItemComponent);
}

void AOperatorPlayerController::Input_Crouch()
{
	if (!IsValid(GetCharacter())) return;
	if (UCharacterMovementComponent* CMC = GetCharacter()->GetCharacterMovement(); IsValid(CMC))
	{
		CMC->bWantsToCrouch = !CMC->bWantsToCrouch;
	}
}

void AOperatorPlayerController::Input_Jump()
{
	if (!IsValid(GetCharacter())) return;
	UCharacterMovementComponent* CMC = GetCharacter()->GetCharacterMovement();
	if (!IsValid(CMC)) return;

	if (CMC->bWantsToCrouch)
	{
		CMC->bWantsToCrouch = false;
	}
	else
	{
		GetCharacter()->Jump();
	}
}

void AOperatorPlayerController::Input_Move(const FInputActionValue& Value)
{
	/*if (bDisableGameplay) return;*/
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
	const FVector RightDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AOperatorPlayerController::Input_Look(const FInputActionValue& Value)
{
	if (InventoryComponent->IsInventoryOpen()) return;
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AOperatorPlayerController::CreateHUDWidget()
{
	if (!IsLocalController()) return;

	HUDWidget = CreateWidget<UTINV_HUDWidget>(this, HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}

void AOperatorPlayerController::TraceForItem()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return;
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize/2.f;

	FVector TraceStart;
	FVector Forward;
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return;

	const FVector TraceEnd = TraceStart + Forward * ItemTraceLength;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ItemTraceChannel);

	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();

	if (!ThisActor.IsValid())
	{	
		if (IsValid(HUDWidget)) HUDWidget->HidePickupMessagePrompt();
	}

	if (ThisActor == LastActor) return;
	if (ThisActor.IsValid())
	{
		if (UActorComponent* Highlightable = ThisActor->FindComponentByInterface(UTINV_Highlightable::StaticClass()); IsValid(Highlightable))
		{
			ITINV_Highlightable::Execute_Highlight(Highlightable);
		}

		UTINV_ItemComponent* ItemComponent = ThisActor->FindComponentByClass<UTINV_ItemComponent>();
		if (!IsValid(ItemComponent) || !ItemDataTable) return;

		const FGameplayTag ItemID = ItemComponent->GetItemManifest().GetItemID();

		const FTINV_ItemDataDefinition* ItemData = ItemDataTable->GetDataByTag(ItemID);
		if (!ItemData) return;

		// CyberscapeItems.Weapons.Rifle.Sublight -> "Rifle"
		FText ItemTypeText;
		if (const FGameplayTag ParentTag = ItemID.RequestDirectParent(); ParentTag.IsValid())
		{
			FString ItemTypeString = ParentTag.ToString();
			FString Left, Right;
			if (ItemTypeString.Split(TEXT("."), &Left, &Right, ESearchCase::CaseSensitive, ESearchDir::FromEnd))
			{
				ItemTypeString = Right;
			}
			ItemTypeText = FText::FromString(ItemTypeString);
		}

		if (IsValid(HUDWidget)) HUDWidget->ShowPickupMessagePrompt(*ItemData, ItemTypeText);
	}

	if (LastActor.IsValid())
	{
		if (UActorComponent* Highlightable = LastActor->FindComponentByInterface(UTINV_Highlightable::StaticClass()); IsValid(Highlightable))
		{
			ITINV_Highlightable::Execute_UnHighlight(Highlightable);
		}
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
