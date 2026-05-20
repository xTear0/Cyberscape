// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Items/Fragments/Inv_ItemFragment.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Interfaces/Inv_AbilitySystemInterface.h"
#include "EquipmentManagement/EquipActor/Inv_EquipActor.h"
#include "EquipmentManagement/Modifications/Inv_EquippedItemPayload.h"
#include "EquipmentManagement/Modifications/Inv_AttributeModificationHandler.h"
#include "GameFramework/PlayerState.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Widgets/Composite/Inv_CompositeBase.h"
#include "Widgets/Composite/Inv_Leaf_EnumValue.h"
#include "Widgets/Composite/Inv_Leaf_Image.h"
#include "Widgets/Composite/Inv_Leaf_LabeledValue.h"
#include "Widgets/Composite/Inv_Leaf_Text.h"
#include "Widgets/Composite/Inv_Leaf_ValuedLabel.h"
#include "Widgets/Utils/Inv_WidgetUtils.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemFragment.cpp_Functions
void FInv_LabeledNumberFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();	
}

void FInv_NumberedLabelFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
}

void FInv_EnumFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
}

void FInv_TextFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
}

FText FInv_ItemFragment::QueryManifestForItemName() const
{
	if (OwningManifest != nullptr)
	{
		return OwningManifest->GetItemName(); 
	}
	return FText::GetEmpty();
}

FText FInv_ItemFragment::QueryManifestForItemDescription() const
{
	if (OwningManifest != nullptr)
	{
		return OwningManifest->GetItemDescription(); 
	}
	return FText::GetEmpty();
}

EInv_ItemStar FInv_ItemFragment::QueryManifestForItemStars() const
{
	if (OwningManifest != nullptr)
	{
		return OwningManifest->GetItemStars(); 
	}
	return EInv_ItemStar::OneStar;
}

EInv_ItemRarity FInv_ItemFragment::QueryItemManifestForRarity() const
{
	if (OwningManifest != nullptr)
	{
		return OwningManifest->GetItemRarity(); 
	}
	return EInv_ItemRarity::Common;
}

int32 FInv_ItemFragment::QueryItemManifestForAttributeValue(FGameplayTag AttributeTag) const
{
	if (OwningManifest != nullptr)
	{
		return OwningManifest->GetItemAttributeValue(AttributeTag);
	}
	return 0;
}

int32 FInv_ItemFragment::QueryItemManifestForSellValue() const
{
	if (OwningManifest != nullptr)
	{
		return OwningManifest->GetItemSellValue();
	}
	return 0;
}


void FInv_InventoryItemFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	if (!MatchesWidgetTag(Composite)) return;
	Composite->Expand();
}

bool FInv_InventoryItemFragment::MatchesWidgetTag(const UInv_CompositeBase* Composite) const
{
	return Composite->GetFragmentTag().MatchesTagExact(GetFragmentTag());
}

void FInv_ImageFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return;

	UInv_Leaf_Image* Image = Cast<UInv_Leaf_Image>(Composite);
	if (!IsValid(Image)) return;
	Image->SetImage(Icon);
	Image->SetBoxSize(IconDimensions);
	Image->SetImageSize(IconDimensions);
}

void FInv_TextFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return;

	UInv_Leaf_Text* LeafText = Cast<UInv_Leaf_Text>(Composite);
	if (!IsValid(LeafText)) return;

	if (bPrefixWithRarity)
	{
		// Adds the Rarity of the Item to the Text with a space, i.e., Legendary Weapon. (Exact: "Legendary ")
		const FText RarityPrefix = UInv_WidgetUtils::GetPrefixFromRarityEnum(QueryItemManifestForRarity());
		LeafText->SetText(FText::Format(FText::FromString(TEXT("{0} {1}")), RarityPrefix, FragmentText));
	}
	if (!bPrefixWithRarity) LeafText->SetText(FragmentText);
	if (bUseItemNameForText) LeafText->SetText(QueryManifestForItemName());
	if (bUseItemDescriptionForText) LeafText->SetText(QueryManifestForItemDescription());
	if (bOverrideRarityTextColor) LeafText->SetColorAndOpacity(UInv_WidgetUtils::GetColorFromColorEnum(TextColor));
	if (!bOverrideRarityTextColor) LeafText->SetColorAndOpacity(UInv_WidgetUtils::GetColorFromRarityEnum(QueryItemManifestForRarity()));
}

void FInv_LabeledNumberFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return;
	
	UInv_Leaf_LabeledValue* LabeledValue = Cast<UInv_Leaf_LabeledValue>(Composite);
	if (!IsValid(LabeledValue)) return;

	LabeledValue->SetText_Label(Text_Label, bCollapseLabel);
	LabeledValue->SetText_LabelColorAs(UInv_WidgetUtils::GetColorFromColorEnum(LabelColor));
	
	FNumberFormattingOptions Options;

	// Creae a sign prefix depending on if the value is Positive or Negative:
	
	FText NumberText = FText::AsNumber(Value, &Options);

	FText Prefix = Value < 0
	? FText::FromString(TEXT("-"))
	: FText::FromString(TEXT("+"));

	FText DisplayValueText = FText::Format(NSLOCTEXT("MyNamespace", "PlusMinusFmt", "{0}{1}"),Prefix,NumberText);
	
	FText DisplaySellText = FText::AsNumber(QueryItemManifestForSellValue(), &Options);
	
	if (!bUseSellValueForValue) LabeledValue->SetText_Value(DisplayValueText, bCollapseValue);
	if (bUseSellValueForValue) LabeledValue->SetText_Value(DisplaySellText, bCollapseValue);
	LabeledValue->SetText_ValueColorAs(UInv_WidgetUtils::GetColorFromColorEnum(ValueColor));
}

void FInv_NumberedLabelFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return;
	
	UInv_Leaf_ValuedLabel* ValuedLabel = Cast<UInv_Leaf_ValuedLabel>(Composite);
	if (!IsValid(ValuedLabel)) return;
	
	FText AttributeText = UInv_WidgetUtils::GetAttributeTextLabel(AttributeTag);
	int32 AttributeValue = QueryItemManifestForAttributeValue(AttributeTag);
	FText SignedAttributeValue = UInv_WidgetUtils::GetSignedAttributeValueFromInt(AttributeValue);
	FLinearColor AttributeColor = UInv_WidgetUtils::GetColorFromAttributeTag(AttributeTag);
	
	ValuedLabel->SetAttributeValueAndTextWithColor(SignedAttributeValue, AttributeText, AttributeColor);
}

void FInv_EnumFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return;

	UInv_Leaf_EnumValue* EnumValueLabel = Cast<UInv_Leaf_EnumValue>(Composite);
	if (!IsValid(EnumValueLabel)) return;

	EnumValueLabel->SetEnumStarValue(QueryManifestForItemStars());
}

float FInv_LabeledNumberFragment::GetValue() const
{
	return Value;
}

void FInv_ConsumableFragment::OnConsume(APlayerController* PC)
{
	for (auto& Modifier : ConsumeModifers)
	{
		auto& ModRef = Modifier.GetMutable();
		ModRef.OnConsume(PC);
	}
}

void FInv_ConsumableFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	for (const auto& Modifier : ConsumeModifers)
	{
		const auto& ModRef = Modifier.Get();
		ModRef.Assimilate(Composite);
	}
}

void FInv_ConsumableFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
	for (auto& Modifier : ConsumeModifers)
	{
		auto& ModRef = Modifier.GetMutable();
		ModRef.Manifest();
	}
}

void FInv_PotionFragment::OnConsume(APlayerController* PC)
{
	if (!GameplayEffectClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid GameplayEffectClass"));
		return;
	}

	UAbilitySystemComponent* TargetASC = PC->GetPlayerState<APlayerState>()->GetComponentByClass<UAbilitySystemComponent>();
	if (!TargetASC)
	{
		UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponent not found on PC"));
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, GetEffectLevel(), EffectContextHandle);

	if (!EffectSpecHandle.IsValid() || !EffectSpecHandle.Data.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid EffectSpecHandle"));
		return;
	}

	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(
		TEXT("Health Potion Consumed! +%f HP"), GetValue()));
}

/*-------------------------------------------------------------------------*/
/*   Unequip and Equip Functions for Equipment							   */
/*-------------------------------------------------------------------------*/

// For each subfragment, call OnEquip and Unequip
void FInv_EquipmentFragment::OnEquip(APlayerController* PC)
{
    if (bEquipped) return;
    bEquipped = true;
    
    // Create Equipped Item Payload
    FInv_EquippedItemPayload Payload = FInv_EquippedItemPayload::Create(
        FName(*OwningManifest->GetItemName().ToString()),
        UInv_WidgetUtils::GetColorFromRarityEnum(OwningManifest->GetItemRarity()),
        OwningManifest->GetItemAttributes(),
        OwningManifest->GetItemAbilities()
    );
    
    // Keep track of Payload for Unequip Removal.
    EquippedPayloadID = Payload.PayloadID;

    // Get PlayerState through interface
    APlayerState* PlayerState = PC->GetPlayerState<APlayerState>();
    if (!PlayerState)
    {
        UE_LOG(LogTemp, Warning, TEXT("OnEquip: No PlayerState found"));
        return;
    }
    
    IInv_AbilitySystemInterface* AbilityInterface = Cast<IInv_AbilitySystemInterface>(PlayerState);
    if (!AbilityInterface)
    {
        UE_LOG(LogTemp, Warning, TEXT("OnEquip: PlayerState does not implement IInv_AbilitySystemInterface"));
        return;
    }
    
    UInv_AttributeModificationHandler* AttributeHandler = AbilityInterface->GetAttributeModificationHandlerForInventory();
    if (IsValid(AttributeHandler))
    {
        AttributeHandler->AddPayload(Payload.PayloadID, Payload);
    }
}

void FInv_EquipmentFragment::OnUnequip(APlayerController* PC)
{
    if (!bEquipped) return;
    bEquipped = false;

    // Get PlayerState through interface
    APlayerState* PlayerState = PC->GetPlayerState<APlayerState>();
    if (!PlayerState)
    {
        UE_LOG(LogTemp, Warning, TEXT("OnUnequip: No PlayerState found"));
        return;
    }
    
    IInv_AbilitySystemInterface* AbilityInterface = Cast<IInv_AbilitySystemInterface>(PlayerState);
    if (!AbilityInterface)
    {
        UE_LOG(LogTemp, Warning, TEXT("OnUnequip: PlayerState does not implement IInv_AbilitySystemInterface"));
        return;
    }
    
    UInv_AttributeModificationHandler* AttributeHandler = AbilityInterface->GetAttributeModificationHandlerForInventory();
    if (IsValid(AttributeHandler))
    {
        AttributeHandler->RemovePayload(EquippedPayloadID);
    }
        
    EquippedPayloadID.Invalidate();
}
/*-------------------------------------------------------------------------*/

void FInv_EquipmentFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	for (const auto& Modifier : EquipModifiers)
	{
		const auto& ModRef = Modifier.Get();
		ModRef.Assimilate(Composite);
	}
}

void FInv_EquipmentFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest(); // Set manifest/component on this
	
	// Add to the Array of EquipAttributeModifiers:
	if (!OwningManifest) return;

	// Loop through AttributePairs in the Manifest
	for (const FInv_ItemAttributePair& Pair : OwningManifest->GetItemAttributes())
	{
		// Add a new instance to the internal array
		TInstancedStruct<FInv_EquipModifier>& NewMod = EquipModifiers.Add_GetRef(TInstancedStruct<FInv_EquipModifier>());
		NewMod.InitializeAs<FInv_EquipModifier>();

		// Fill it in
			FInv_EquipModifier& Mod = NewMod.GetMutable();
			Mod.SetAttribute(Pair.AttributeTag);
			Mod.SetFragmentTag(Pair.FragmentTag);
			Mod.SetOwningManifest(GetOwningManifest());
			Mod.Manifest();
	}
}

AInv_EquipActor* FInv_EquipmentFragment::SpawnAttachedActor(USkeletalMeshComponent* AttachMesh, bool bProxy) const
{
    // Early validation
    if (!IsValid(EquipActorClass) || !IsValid(AttachMesh))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid EquipActorClass or AttachMesh in SpawnAttachedActor"));
        return nullptr;
    }

    // Create the equipment actor
    AInv_EquipActor* SpawnedActor = CreateEquipmentActor(AttachMesh);
    if (!IsValid(SpawnedActor))
    {
        return nullptr;
    }

    // Attach actor to the mesh
    AttachActorToMesh(SpawnedActor, AttachMesh);

    // Handle binding logic based on proxy state
    if (bProxy)
    {
        HandleProxyBinding(SpawnedActor, AttachMesh);
    }
    else
    {
        HandleStandardBinding(SpawnedActor, AttachMesh);
    }

    return SpawnedActor;
}

AInv_EquipActor* FInv_EquipmentFragment::CreateEquipmentActor(USkeletalMeshComponent* AttachMesh) const
{
    UWorld* World = AttachMesh->GetWorld();
    if (!IsValid(World))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid World when spawning equipment actor"));
        return nullptr;
    }

    AInv_EquipActor* SpawnedActor = World->SpawnActor<AInv_EquipActor>(EquipActorClass);
    if (!IsValid(SpawnedActor))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn equipment actor of class: %s"), 
               EquipActorClass ? *EquipActorClass->GetName() : TEXT("NULL"));
    }

    return SpawnedActor;
}

USkeletalMeshComponent* FInv_EquipmentFragment::FindComponentByTag(AActor* Owner, const FName& Tag) const
{
    if (!IsValid(Owner))
    {
        return nullptr;
    }

    UActorComponent* FoundComponent = Owner->FindComponentByTag(USkeletalMeshComponent::StaticClass(), Tag);
    return Cast<USkeletalMeshComponent>(FoundComponent);
}

void FInv_EquipmentFragment::AttachActorToMesh(AInv_EquipActor* Actor, USkeletalMeshComponent* AttachMesh) const
{
    if (!IsValid(Actor) || !IsValid(AttachMesh))
    {
        return;
    }

    // Use consistent attachment rules
    const FAttachmentTransformRules AttachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
    Actor->AttachToComponent(AttachMesh, AttachRules);
}

void FInv_EquipmentFragment::HandleProxyBinding(AInv_EquipActor* SpawnedActor, USkeletalMeshComponent* AttachMesh) const
{
    if (!IsValid(SpawnedActor) || !IsValid(AttachMesh))
    {
        return;
    }

    AActor* Owner = AttachMesh->GetOwner();
    USkeletalMeshComponent* BindMeshProxy = FindComponentByTag(Owner, FName("BindMesh"));
    
    if (!IsValid(BindMeshProxy))
    {
        UE_LOG(LogTemp, Warning, TEXT("BindMesh component not found for proxy binding"));
        return;
    }

    // Reattach to the bind mesh with the correct socket
    const FAttachmentTransformRules SocketAttachRules = FAttachmentTransformRules::SnapToTargetIncludingScale;
    SpawnedActor->AttachToComponent(BindMeshProxy, SocketAttachRules, SocketAttachPoint);

    // Set up master pose for non-weapon items
    if (!bIsWeapon)
    {
        USkeletalMeshComponent* ActorMesh = Cast<USkeletalMeshComponent>(
            SpawnedActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
        
        SetupMasterPoseBinding(ActorMesh, BindMeshProxy);
    }
}

void FInv_EquipmentFragment::HandleStandardBinding(AInv_EquipActor* SpawnedActor, USkeletalMeshComponent* AttachMesh) const
{
    if (!IsValid(SpawnedActor) || !IsValid(AttachMesh))
    {
        return;
    }

    USkeletalMeshComponent* ActorMesh = Cast<USkeletalMeshComponent>(
        SpawnedActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
    
    if (!IsValid(ActorMesh))
    {
        UE_LOG(LogTemp, Warning, TEXT("No SkeletalMeshComponent found on spawned equipment actor"));
        return;
    }

    AActor* Owner = AttachMesh->GetOwner();
    USkeletalMeshComponent* BindMesh = FindComponentByTag(Owner, FName("BindMesh"));
    
    // Set up master pose binding if BindMesh exists
    if (IsValid(BindMesh))
    {
        // If we have a socket attachment point, reattach with proper scaling
        if (SocketAttachPoint != NAME_None)
        {
            const FAttachmentTransformRules SocketAttachRules = FAttachmentTransformRules::SnapToTargetIncludingScale;
            SpawnedActor->AttachToComponent(BindMesh, SocketAttachRules, SocketAttachPoint);
        }
        
        SetupMasterPoseBinding(ActorMesh, BindMesh);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BindMesh component not found for standard binding"));
    }

    // Handle weapon-specific logic
    if (bIsWeapon)
    {
        USkeletalMeshComponent* WeaponBindMesh = FindComponentByTag(Owner, FName("BindWeapon"));
        if (IsValid(WeaponBindMesh))
        {
            HandleWeaponOverride(ActorMesh, WeaponBindMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("BindWeapon component not found for weapon binding"));
        }
    }
}

void FInv_EquipmentFragment::SetupMasterPoseBinding(USkeletalMeshComponent* ActorMesh, USkeletalMeshComponent* LeaderMesh) const
{
    if (!IsValid(ActorMesh) || !IsValid(LeaderMesh))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid components for master pose binding"));
        return;
    }

    ActorMesh->SetLeaderPoseComponent(LeaderMesh);
}

void FInv_EquipmentFragment::HandleWeaponOverride(USkeletalMeshComponent* ActorMesh, USkeletalMeshComponent* WeaponBindMesh) const
{
    if (!IsValid(ActorMesh) || !IsValid(WeaponBindMesh))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid components for weapon override"));
        return;
    }

    USkeletalMesh* WeaponMesh = ActorMesh->GetSkeletalMeshAsset();
    if (!IsValid(WeaponMesh))
    {
        UE_LOG(LogTemp, Warning, TEXT("No skeletal mesh asset found on weapon actor"));
        return;
    }

    // Transfer the mesh to the bind component and hide the original
    WeaponBindMesh->SetSkeletalMesh(WeaponMesh);
    ActorMesh->SetVisibility(false);
    WeaponBindMesh->SetVisibility(true);
}


void FInv_EquipmentFragment::DestroyAttachedActor() const
{
	if (EquippedActor.IsValid())
	{
		EquippedActor->Destroy();
	}
}

void FInv_EquipmentFragment::SetEquippedActor(AInv_EquipActor* EquipActor)
{
	EquippedActor = EquipActor;
}
#pragma endregion
/*-------------------------------------------------------------------------*/