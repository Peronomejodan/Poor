/*
*PERONOMEJODAN FIX


SQL

DELETE FROM `item_template` WHERE (entry = 900001);
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `StatsCount`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `ScalingStatDistribution`, `ScalingStatValue`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `flagsCustom`, `VerifiedBuild`) VALUES
(900001, 15, 0, -1, 'Resurreción en Masa', 48042, 5, 33, 0, 1, 228800000, 34, 0, -1, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 14093, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 'Revive a todos los miembros del grupo o banda con el 35% de vida y mana. Solo se puede usar cada 15 minutos.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 'item_res_group', 0, 0, 0, 0, 0, 0);

 */
 
#include "ScriptMgr.h"
#include "Player.h"
#include "Group.h"
#include "ObjectAccessor.h"
#include "ScriptedGossip.h"
#include "WorldSession.h"

class item_res_group : public ItemScript
{
public:
	item_res_group() : ItemScript("item_res_group") { }

	bool DistanceIsValid(Position* playerWhoUsesTheItem, Position* deadPlayersInGroup)
	{
		if (std::abs(deadPlayersInGroup->GetPositionX() - playerWhoUsesTheItem->GetPositionX()) <= 91.44) //91.44 meters = 100 yards
			return true;
		return false;
	}

	bool OnUse(Player* playerWhoUsesTheItem, Item* /*item*/, SpellCastTargets const& /*targets*/)
	{
		Group* group = playerWhoUsesTheItem->GetGroup();
		Group::MemberSlotList const &members = group->GetMemberSlots();

		if (playerWhoUsesTheItem->HasAura(38910)) //Fel Weakness 
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("Debes esperar 15 minutos antes de volver a usar este objeto!");
			return false;
		}

		if (!playerWhoUsesTheItem->GetGroup())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("No estas en un grupo o raid!");
			return false;
		}
		/* //What if the leader is dead?
		if (playerWhoUsesTheItem->GetGroup()->GetLeaderGUID() != playerWhoUsesTheItem->GetGUID())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("You are not the group leader!");
			return false;
		}
		*/
		if (playerWhoUsesTheItem->InBattleground())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("No está permitido usar este objeto en: Campos de Batalla!");
			return false;
		}

		if (playerWhoUsesTheItem->InArena())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("No está permitido usar este objeto en: Arenas!");
			return false;
		}

		if (playerWhoUsesTheItem->IsInCombat())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("No está permitido usar este objeto en: Combate!");
			return false;
		}
		
		else
		{
			for (Group::MemberSlotList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
			{
				//Group::MemberSlot const& slot = *itr;
				Player* deadPlayersInGroup = ObjectAccessor::FindPlayer((*itr).guid);

				//skip if player/s is/are offline //--This check is mandatory. the server will crash without it
				if (!deadPlayersInGroup || deadPlayersInGroup->GetSession()->PlayerDisconnected())
				{
					CloseGossipMenuFor(playerWhoUsesTheItem);
				}

				if (deadPlayersInGroup && deadPlayersInGroup->GetSession() && deadPlayersInGroup->isDead() && playerWhoUsesTheItem->GetSession() && DistanceIsValid(playerWhoUsesTheItem, deadPlayersInGroup))
				{
					deadPlayersInGroup->ResurrectPlayer(0.75f, false); //75% hp and mana, don't apply Resurrection Sickness
					deadPlayersInGroup->CastSpell(deadPlayersInGroup, 48171, true); //Visual Spell Resurrect (priest)
					deadPlayersInGroup->DurabilityRepairAll(0, 0, false); //Repair All - upon resurrection
					playerWhoUsesTheItem->CastSpell(playerWhoUsesTheItem, 38910, true); //Fel Weakness //Cast a debuff on player To prevent the item being used over and over again	
				}
			}
		}
		return true;
	}
};

void AddSC_item_res_group()
{
	new item_res_group;
}