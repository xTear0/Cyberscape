// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "StructUtils/InstancedStruct.h"
#include "Types/Inv_EnumTypes.h"
#include "Inv_ItemFragment.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class APlayerController;
class UCurveTable;
class UInv_CompositeBase;
class AInv_EquipActor;

USTRUCT(BlueprintType)
struct FInv_ItemFragment
{
	GENERATED_BODY()
	
	// Following the Rule of 5, two copy functions, two move functions, and a destructor function.
	// We are only using this particular system because we want a struct that we can have childs made from.
	// If we end up deleting a child through a parent pointer, we need polymorphic destruction. So we add
	// a virtual destructor.
	/*----------------------------------------------------------------*/
	FInv_ItemFragment() {}
	FInv_ItemFragment(const FInv_ItemFragment&) =  default;
	FInv_ItemFragment& operator=(const FInv_ItemFragment&) = default;
	FInv_ItemFragment(FInv_ItemFragment&&) =  default;
	FInv_ItemFragment& operator=(FInv_ItemFragment&&) = default;
	virtual ~FInv_ItemFragment() {}
	/*----------------------------------------------------------------*/

	FGameplayTag GetFragmentTag() const { return FragmentTag; }
	void SetFragmentTag(FGameplayTag Tag) { FragmentTag = Tag; }
	
	void SetOwningManifest(FInv_ItemManifest* InManifest) { OwningManifest = InManifest; }
	FInv_ItemManifest* GetOwningManifest() const { return OwningManifest; }

	virtual void Manifest() {}

protected:
	// Reference to the original owning ItemManifest
	FInv_ItemManifest* OwningManifest{nullptr};

	// Query Data from Manifest
	FText QueryManifestForItemName() const;
	FText QueryManifestForItemDescription() const;
	EInv_ItemStar QueryManifestForItemStars() const;
	EInv_ItemRarity QueryItemManifestForRarity() const;
	int32 QueryItemManifestForAttributeValue(FGameplayTag AttributeTag) const;
	int32 QueryItemManifestForSellValue() const;
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Categories= "FragmentTags" ))
	FGameplayTag FragmentTag{FGameplayTag::EmptyTag};	
};


USTRUCT(BlueprintType)
struct FInv_GridFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	FIntPoint GetGridSize() const { return GridSize; }
	void SetGridSize(FIntPoint Size) { this->GridSize = Size; }
	float GetGridPadding() const { return GridPadding; }
	void SetGridPadding(float Padding) { this->GridPadding = Padding; }
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FIntPoint GridSize{1, 1};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	float GridPadding{0.f};
};

/*-------------------------------------------------------------------------*/
// Item Fragment Specifically for Assimilation into a widget.
/*-------------------------------------------------------------------------*/
USTRUCT(BlueprintType)
struct FInv_InventoryItemFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	virtual void Assimilate(UInv_CompositeBase* Composite) const;
protected:
	bool MatchesWidgetTag(const UInv_CompositeBase* Composite) const;

	// This is where we might want to fetch the original ItemComponent.
};
/*-------------------------------------------------------------------------*/

USTRUCT(BlueprintType)
struct FInv_ImageFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	UTexture2D* GetIcon() const { return Icon; }
	void SetIcon(UTexture2D* InIcon) { Icon = InIcon; }
	void SetIconDimensions(FVector2D Dimensions) { IconDimensions = Dimensions; }
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	UTexture2D* Icon{nullptr};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FVector2D IconDimensions{64.f, 64.f};
};

USTRUCT(BlueprintType)
struct FInv_TextFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()
	virtual void Manifest() override;
	FText GetText() const { return FragmentText; }
	void SetText(const FText& Text) { FragmentText = Text; }
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	bool bUseItemNameForText{false};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	bool bUseItemDescriptionForText{false};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	bool bPrefixWithRarity{false};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	bool bOverrideRarityTextColor{false};
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FText FragmentText;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	EInv_Colors TextColor{EInv_Colors::UITan};
};

USTRUCT(BlueprintType)
struct FInv_LabeledNumberFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	virtual void Manifest() override;
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;

	float GetValue() const;
	float GetEffectLevel() const { return EffectLevel; }

	void SetLabelText(const FText& InText) { Text_Label = InText; }
	void SetLabelValue(const float& InValue) { Value = InValue; }
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	EInv_Colors LabelColor{EInv_Colors::UIWhite};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	EInv_Colors ValueColor{EInv_Colors::UIWhite};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	bool bUseSellValueForValue{false};
	
	UPROPERTY(EditAnywhere, Category =  "Inventory")
	bool bCollapseLabel{false};

	UPROPERTY(EditAnywhere, Category =  "Inventory")
	bool bCollapseValue{false};
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	float Value{0.f};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float EffectLevel{0.f};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FText Text_Label;
};

USTRUCT(BlueprintType)
struct FInv_NumberedLabelFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	virtual void Manifest() override;
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	
protected:

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Categories= "Attributes" ))
	FGameplayTag AttributeTag{FGameplayTag::EmptyTag};
};

USTRUCT(BlueprintType)
struct FInv_EnumFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	virtual void Manifest() override;
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
};

USTRUCT(BlueprintType)
struct FInv_StackableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	int32 GetMaxStackSize() const { return MaxStackSize; }
	int32 GetStackCount() const { return StackCount; }
	void SetStackCount(int32 Count) { this->StackCount = Count; }
private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 StackCount{1};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 MaxStackSize{1};
};


// Consume Fragments

USTRUCT(BlueprintType)
struct FInv_ConsumeModifer : public FInv_LabeledNumberFragment 
{
	GENERATED_BODY()
	virtual void OnConsume(APlayerController* PC) {};
};

USTRUCT(BlueprintType)
struct FInv_ConsumableFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	virtual void OnConsume(APlayerController* PC);
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	virtual void Manifest() override;
private:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FInv_ConsumeModifer>> ConsumeModifers;
};

USTRUCT(BlueprintType)
struct FInv_PotionFragment : public FInv_ConsumeModifer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	// Consume potions will directly affect stats like Health or Mana, or other potions added later. They will explicitly
	// NOT affect the Attribute Modification Handler. I hate how Hypixel Skyblock requires potion effects to do everything.
	
	virtual void OnConsume(APlayerController* PC) override;
};

// Equipment
USTRUCT(BlueprintType)
struct FInv_EquipModifier : public FInv_NumberedLabelFragment
{
	GENERATED_BODY()
	void SetAttribute(FGameplayTag InAttributeTag) {AttributeTag = InAttributeTag;};
	virtual void OnEquip(APlayerController* PC) {};
	virtual void OnUnequip(APlayerController* PC) {};
};

USTRUCT(BlueprintType)
struct FInv_AttributeEquipModifier : public FInv_EquipModifier
{
	GENERATED_BODY()
	// TODO: Delete or change this to be useful later.
};

USTRUCT(BlueprintType)
struct FInv_EquipmentFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	bool bEquipped{false};
	void OnEquip(APlayerController* PC);
	void OnUnequip(APlayerController* PC);
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	virtual void Manifest() override;

	AInv_EquipActor* SpawnAttachedActor(USkeletalMeshComponent* AttachMesh, bool bProxy = {false}) const;
	void DestroyAttachedActor() const;
	FGameplayTag GetEquipmentType() const { return EquipmentTag; }
	bool GetIsWeapon() const { return bIsWeapon; }
	void SetEquippedActor(AInv_EquipActor* EquipActor);
	
private:

	AInv_EquipActor* CreateEquipmentActor(USkeletalMeshComponent* AttachMesh) const;
	USkeletalMeshComponent* FindComponentByTag(AActor* Owner, const FName& Tag) const;
	void AttachActorToMesh(AInv_EquipActor* Actor, USkeletalMeshComponent* AttachMesh) const;
	void HandleProxyBinding(AInv_EquipActor* SpawnedActor, USkeletalMeshComponent* AttachMesh) const;
	void HandleStandardBinding(AInv_EquipActor* SpawnedActor, USkeletalMeshComponent* AttachMesh) const;
	void SetupMasterPoseBinding(USkeletalMeshComponent* ActorMesh, USkeletalMeshComponent* LeaderMesh) const;
	void HandleWeaponOverride(USkeletalMeshComponent* ActorMesh, USkeletalMeshComponent* WeaponBindMesh) const;

	
	UPROPERTY()
	TArray<TInstancedStruct<FInv_EquipModifier>> EquipModifiers;

	UPROPERTY()
	FGuid EquippedPayloadID;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<AInv_EquipActor> EquipActorClass = nullptr;

	
	TWeakObjectPtr<AInv_EquipActor> EquippedActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FName SocketAttachPoint{NAME_None};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	bool bIsWeapon{false}; // TODO: Items should be smart enough to know if they are a weapon without this bool.
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag EquipmentTag = FGameplayTag::EmptyTag;
};
/*-------------------------------------------------------------------------*/


