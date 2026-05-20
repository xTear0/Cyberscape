// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "NativeGameplayTags.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Namespace Item Declarations										   */
/*-------------------------------------------------------------------------*/



namespace TOTUItems
{
	namespace Equipment
	{
		namespace Weapons
		{
			namespace Swords
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Peril)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Deathripper)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Hrunting)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(MoltenHilt)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(SpectralBlade)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(VorpalSword)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(MoonlightCrescent)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(AncientSword)
			}

			namespace Hammers
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cursebreaker)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(HammerOfLight)
			}
			
			namespace Staffs
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(ArcaneStaff)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(SceptreOfArcturus)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(RodOfRuin)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(WandOfWarping)
			}

			namespace Maces
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaceOfAmethyst)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(ScavengerMace)
			}

			namespace Bows
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(NightshadeRecurve)
			}
			
			namespace Shields
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(RuneworkShield)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(GuardKeeper)
			}
		}
		namespace Helmets
		{
			// Mythical
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(EldritchDiadem)	
			// Legendary
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HelmetOfTheGreats)
			// Epic
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(EyesFromLimbo)
			// Rare
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(SilverHelmet)
			// Uncommon
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InfusedHelmet)
			// Common
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(AncientHelmet)
		}
		namespace Chestplates
		{
			// Supreme
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ShroudOfTheImperium)
			// Mythical
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(StrengthOfTheMountain)
			// Legendary
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(SpellthreadRobes)
			// Epic
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(RuneworkChestplate)
			// Rare
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(SilverCuirass)
			// Uncommon
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Battleplate)
			
		}
		namespace Gauntlets
		{
			// Supreme
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(FromTheAbyss)
			// Mythical
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HandsOfMidas)
			// Legendary
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(SpellthreadGloves)
			// Epic
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(FlamingHands)
		}
		namespace Greaves
		{
			// Legendary
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ChainmailOfTheGreats)
			// Epic
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(DarkStrides)
		}
		namespace Belts
		{
			// Supreme
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(BeltOfHeroes)
			// Mythical
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(BejeweledBelt)
		}

	}
	namespace Consumables
	{
		namespace Potions
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HealthPotion) // Instantly restores health.
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ManaPotion) // Instantly restores mana.
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(SurgePotion) // Instantly refreshes cooldowns.
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ExperiencePotion) // Instantly adds experience.
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(DeathPotion) // Instantly destroys health and mana.
		}
		namespace Flasks
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HealthFlask) // Constant health regeneration.
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ManaFlask) // Constant mana regeneration.
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(FightingFlask) // Constant boost to Strength, Crit Chance, and Crit Damage.
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ResistanceFlask) // Constant boost to Resistance.
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(GloryFlask) // Constant boost to all stats.		
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(DeathFlask) // Constant destroy of health and mana.
		}
	}
	namespace Craftables
	{
		// Legendary
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(PolytopicCrystal)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(StarMetal)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(VoidCore)
		// Epic
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(MonsterHeart)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(SpellforgedIngot)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(MithrilLinks)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DrakeBlood)
		// Rare
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(UnstableRunes)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(SilverThread)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(EldritchResin)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(LivingMetal)
		// Uncommon
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(GraveMoss)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(EnchantedAmythest)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(OldScrolls)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(SealingWax)
		// Common
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(RuneFragment)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ObsidianShard)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Bones)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(MoltenSlag)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(WroughtIron)
	}
}
/*-------------------------------------------------------------------------*/