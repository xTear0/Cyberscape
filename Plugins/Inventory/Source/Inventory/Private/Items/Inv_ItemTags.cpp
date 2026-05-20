// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Items/Inv_ItemTags.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Item Tag Definitions                                                  */
/*-------------------------------------------------------------------------*/
namespace TOTUItems
{
	namespace Equipment
	{
		namespace Weapons
		{
			namespace Swords
			{
				UE_DEFINE_GAMEPLAY_TAG(Peril, "TOTUItems.Equipment.Weapons.Swords.Peril")
				UE_DEFINE_GAMEPLAY_TAG(Hrunting, "TOTUItems.Equipment.Weapons.Swords.Hrunting")
				UE_DEFINE_GAMEPLAY_TAG(Deathripper, "TOTUItems.Equipment.Weapons.Swords.Deathripper")
				UE_DEFINE_GAMEPLAY_TAG(VorpalSword, "TOTUItems.Equipment.Weapons.Swords.VorpalSword")
				UE_DEFINE_GAMEPLAY_TAG(SpectralBlade, "TOTUItems.Equipment.Weapons.Swords.SpectralBlade")
				UE_DEFINE_GAMEPLAY_TAG(MoonlightCrescent, "TOTUItems.Equipment.Weapons.Swords.MoonlightCrescent")
				UE_DEFINE_GAMEPLAY_TAG(MoltenHilt, "TOTUItems.Equipment.Weapons.Swords.MoltenHilt")
				UE_DEFINE_GAMEPLAY_TAG(AncientSword, "TOTUItems.Equipment.Weapons.Swords.AncientSword")
			}

			namespace Hammers
			{
				UE_DEFINE_GAMEPLAY_TAG(HellforgeHammer, "TOTUItems.Equipment.Weapons.Hammers.HellforgeHammer")
				UE_DEFINE_GAMEPLAY_TAG(HammerOfLight, "TOTUItems.Equipment.Weapons.Hammers.HammerOfLight")
			}

			namespace Staffs
			{
				UE_DEFINE_GAMEPLAY_TAG(SceptreOfArcturus, "TOTUItems.Equipment.Weapons.Staffs.SceptreOfArcturus")
				UE_DEFINE_GAMEPLAY_TAG(RodOfRuin, "TOTUItems.Equipment.Weapons.Staffs.RodOfRuin")
				UE_DEFINE_GAMEPLAY_TAG(WandOfWarping, "TOTUItems.Equipment.Weapons.Staffs.WandOfWarping")
				UE_DEFINE_GAMEPLAY_TAG(ArcaneStaff, "TOTUItems.Equipment.Weapons.Staffs.ArcaneStaff")
			}

			namespace Maces
			{
				UE_DEFINE_GAMEPLAY_TAG(MaceOfAmethyst, "TOTUItems.Equipment.Weapons.Maces.MaceOfAmethyst")
				UE_DEFINE_GAMEPLAY_TAG(ScavengerMace, "TOTUItems.Equipment.Weapons.Maces.ScavengerMace")
			}

			namespace Bows
			{
				UE_DEFINE_GAMEPLAY_TAG(NightshadeRecurve, "TOTUItems.Equipment.Weapons.Bows.NightshadeRecurve")
			}
			
			namespace Shields
			{
				UE_DEFINE_GAMEPLAY_TAG(RuneworkShield, "TOTUItems.Equipment.Weapons.Shields.RuneworkShield")
				UE_DEFINE_GAMEPLAY_TAG(GuardKeeper, "TOTUItems.Equipment.Weapons.Shields.GuardKeeper")
			}
		}
		namespace Helmets
		{
			// Mythical
			UE_DEFINE_GAMEPLAY_TAG(EldritchDiadem, "TOTUItems.Equipment.Helmets.EldritchDiadem")
			// Legendary
			UE_DEFINE_GAMEPLAY_TAG(HelmetOfTheGreats, "TOTUItems.Equipment.Helmets.HelmetOfTheGreats")
			// Epic
			UE_DEFINE_GAMEPLAY_TAG(EyesFromLimbo, "TOTUItems.Equipment.Helmets.EyesFromLimbo")
			// Rare
			UE_DEFINE_GAMEPLAY_TAG(SilverHelmet, "TOTUItems.Equipment.Helmets.SilverHelmet")
			// Uncommon
			UE_DEFINE_GAMEPLAY_TAG(InfusedHelmet, "TOTUItems.Equipment.Helmets.InfusedHelmet")
			// Common
			UE_DEFINE_GAMEPLAY_TAG(AncientHelmet, "TOTUItems.Equipment.Helmets.AncientHelmet")
		}
		namespace Chestplates
		{
			// Supreme
			UE_DEFINE_GAMEPLAY_TAG(ShroudOfTheImperium, "TOTUItems.Equipment.Chestplates.ShroudOfTheImperium")
			// Mythical
			UE_DEFINE_GAMEPLAY_TAG(StrengthOfTheMountain, "TOTUItems.Equipment.Chestplates.StrengthOfTheMountain")
			// Legendary
			UE_DEFINE_GAMEPLAY_TAG(SpellthreadRobes, "TOTUItems.Equipment.Chestplates.SpellthreadRobes")
			// Epic
			UE_DEFINE_GAMEPLAY_TAG(RuneworkChestplate, "TOTUItems.Equipment.Chestplates.RuneworkChestplate")
			// Rare
			UE_DEFINE_GAMEPLAY_TAG(SilverCuirass, "TOTUItems.Equipment.Chestplates.SilverCuirass")
			// Uncommon
			UE_DEFINE_GAMEPLAY_TAG(Battleplate, "TOTUItems.Equipment.Chestplates.Battleplate")
			
		}
		namespace Gauntlets
		{
			// Supreme
			UE_DEFINE_GAMEPLAY_TAG(FromTheAbyss, "TOTUItems.Equipment.Gauntlets.FromTheAbyss")
			// Mythical
			UE_DEFINE_GAMEPLAY_TAG(HandsOfMidas, "TOTUItems.Equipment.Gauntlets.HandsOfMidas")
			// Legendary
			UE_DEFINE_GAMEPLAY_TAG(SpellthreadGloves, "TOTUItems.Equipment.Gauntlets.SpellthreadGloves")
			// Epic
			UE_DEFINE_GAMEPLAY_TAG(FlamingHands, "TOTUItems.Equipment.Gauntlets.FlamingHands")
			// Rare
			UE_DEFINE_GAMEPLAY_TAG(SilverGauntlets, "TOTUItems.Equipment.Gauntlets.SilverGauntlets")
		}
		namespace Greaves
		{
			// Legendary
			UE_DEFINE_GAMEPLAY_TAG(ChainmailOfTheGreats, "TOTUItems.Equipment.Greaves.ChainmailOfTheGreats")
			// Epic
			UE_DEFINE_GAMEPLAY_TAG(DarkStrides, "TOTUItems.Equipment.Greaves.DarkStrides")
		}
		namespace Belts
		{
			// Supreme
			UE_DEFINE_GAMEPLAY_TAG(BeltOfHeroes, "TOTUItems.Equipment.Belts.BeltOfHeroes")
			// Mythical
			UE_DEFINE_GAMEPLAY_TAG(BejeweledBelt, "TOTUItems.Equipment.Belts.BejeweledBelt")
		}

	}
	namespace Consumables
	{
		namespace Potions
		{
			UE_DEFINE_GAMEPLAY_TAG(HealthPotion, "TOTUItems.Consumables.Potions.HealthPotion") // Instantly restores health.
			UE_DEFINE_GAMEPLAY_TAG(ManaPotion, "TOTUItems.Consumables.Potions.ManaPotion") // Instantly restores mana.
			UE_DEFINE_GAMEPLAY_TAG(SurgePotion, "TOTUItems.Consumables.Potions.SurgePotion") // Instantly refreshes cooldowns.
			UE_DEFINE_GAMEPLAY_TAG(ExperiencePotion, "TOTUItems.Consumables.Potions.ExperiencePotion") // Instantly adds experience.
			UE_DEFINE_GAMEPLAY_TAG(DeathPotion, "TOTUItems.Consumables.Potions.DeathPotion") // Instantly destroys health and mana.
		}
		namespace Flasks
		{
			UE_DEFINE_GAMEPLAY_TAG(HealthFlask, "TOTUItems.Consumables.Flasks.HealthFlask") // Constant health regeneration.
			UE_DEFINE_GAMEPLAY_TAG(ManaFlask, "TOTUItems.Consumables.Flasks.ManaFlask") // Constant mana regeneration.
			UE_DEFINE_GAMEPLAY_TAG(FightingFlask, "TOTUItems.Consumables.Flasks.FightingFlask") // Constant boost to Strength, Crit Chance, and Crit Damage.
			UE_DEFINE_GAMEPLAY_TAG(ResistanceFlask, "TOTUItems.Consumables.Flasks.ResistanceFlask") // Constant boost to Resistance.
			UE_DEFINE_GAMEPLAY_TAG(GloryFlask, "TOTUItems.Consumables.Flasks.GloryFlask") // Constant boost to all stats.		
			UE_DEFINE_GAMEPLAY_TAG(DeathFlask, "TOTUItems.Consumables.Flasks.DeathFlask") // Constant destroy of health and mana.
		}
	}
	namespace Craftables
	{
		// Legendary
		UE_DEFINE_GAMEPLAY_TAG(PolytopicCrystal, "TOTUItems.Craftables.PolytopicCrystal")
		UE_DEFINE_GAMEPLAY_TAG(StarMetal, "TOTUItems.Craftables.StarMetal")
		UE_DEFINE_GAMEPLAY_TAG(VoidCore, "TOTUItems.Craftables.VoidCore")
		UE_DEFINE_GAMEPLAY_TAG(BeheadedSkull, "TOTUItems.Craftables.BeheadedSkull")
		// Epic
		UE_DEFINE_GAMEPLAY_TAG(MonsterClaws, "TOTUItems.Craftables.MonsterClaws")
		UE_DEFINE_GAMEPLAY_TAG(SpellforgedIngot, "TOTUItems.Craftables.SpellforgedIngot")
		UE_DEFINE_GAMEPLAY_TAG(MithrilLinks, "TOTUItems.Craftables.MithrilLinks")
		UE_DEFINE_GAMEPLAY_TAG(DrakeBlood, "TOTUItems.Craftables.DrakeBlood")
		// Rare
		UE_DEFINE_GAMEPLAY_TAG(UnstableRunes, "TOTUItems.Craftables.UnstableRunes")
		UE_DEFINE_GAMEPLAY_TAG(SilverThread, "TOTUItems.Craftables.SilverThread")
		UE_DEFINE_GAMEPLAY_TAG(EldritchResin, "TOTUItems.Craftables.EldritchResin")
		UE_DEFINE_GAMEPLAY_TAG(LivingMetal, "TOTUItems.Craftables.LivingMetal")
		// Uncommon
		UE_DEFINE_GAMEPLAY_TAG(BrokenWeapons, "TOTUItems.Craftables.BrokenWeapons")
		UE_DEFINE_GAMEPLAY_TAG(EnchantedAmythest, "TOTUItems.Craftables.EnchantedAmythest")
		UE_DEFINE_GAMEPLAY_TAG(OldScrolls, "TOTUItems.Craftables.OldScrolls")
		UE_DEFINE_GAMEPLAY_TAG(SealingWax, "TOTUItems.Craftables.SealingWax")
		// Common
		UE_DEFINE_GAMEPLAY_TAG(RuneFragment, "TOTUItems.Craftables.RuneFragment")
		UE_DEFINE_GAMEPLAY_TAG(ObsidianShard, "TOTUItems.Craftables.ObsidianShard")
		UE_DEFINE_GAMEPLAY_TAG(Bones, "TOTUItems.Craftables.Bones")
		UE_DEFINE_GAMEPLAY_TAG(MoltenSlag, "TOTUItems.Craftables.MoltenSlag")
		UE_DEFINE_GAMEPLAY_TAG(WroughtIron, "TOTUItems.Craftables.WroughtIron")
	}
}
/*-------------------------------------------------------------------------*/