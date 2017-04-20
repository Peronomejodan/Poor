/*
* PERONOMEJODAN FIX
* SQL: 

-- BEASTMASTER ITEM SQL
DELETE FROM `item_template` WHERE (entry = 900000);
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `StatsCount`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `ScalingStatDistribution`, `ScalingStatValue`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `flagsCustom`, `VerifiedBuild`) VALUES
(900000, 15, 0, -1, 'Mascotas de Cazador', 61687, 5, 2147483681, 0, 1, 0, 0, 0, 4, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 24228, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 1, 'Usala para tener tu mascota', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 'item_beastmaster', 0, 0, 0, 0, 0, 12340);
 */
 
#include "ScriptMgr.h"
#include "Chat.h"
#include "Define.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Pet.h"
#include "ObjectMgr.h"
#include "WorldSession.h"
 
//      Creature        entry
#define CHIMERA         21879
#define CORE_HOUND      21108
#define DEVILSAUR       20931
#define RHINO           30445
#define SILITHID        5460
#define WORM            30148
#define LOQUE_NAHAK     32517
#define SKOLL           35189
#define GONDRIA         33776
#define SPIDER          2349
#define DRAGONHAWK      27946
#define BAT             28233
#define RAVAGER         17199
#define RAPTOR          14821
#define SERPENT         28358
#define BEAR            29319
#define BOAR            29996
#define WASP            28085
#define CAT             28097
#define CARRION_BIRD    26838
#define CRAB            24478
#define CROCOLISK       1417
#define GORILLA         28213
#define BLIGHT_HOUND    29452
#define HYENA           13036
#define MOTH            27421
#define OWL             23136
#define TALLSTRIDER     22807
#define SCORPID         9698
#define TURTLE          25482
 
//Gossip Menu
#define NORMAL_PET_PAGE_1           GOSSIP_ACTION_INFO_DEF + 1
#define NORMAL_PET_PAGE_2           GOSSIP_ACTION_INFO_DEF + 2
#define EXOTIC_PET                  GOSSIP_ACTION_INFO_DEF + 3
#define STABLE_PET                  GOSSIP_ACTION_INFO_DEF + 4
#define RESET_PET_TALENTS           GOSSIP_ACTION_INFO_DEF + 5
#define RENAME_PET                  GOSSIP_ACTION_INFO_DEF + 6
#define MAIN_MENU                   GOSSIP_ACTION_INFO_DEF + 7
 
 
class item_beastmaster : public ItemScript
{
    public:
        item_beastmaster() : ItemScript("item_beastmaster") {}
 
    void CreatePet(Player* player, Item* /*item*/, uint32 entry)
    {
        if (player->GetPet())
        {
            player->GetSession()->SendAreaTriggerMessage("Você deve deixar ou guardar seu pet atual, a fim de ganhar um novo pet.");
            player->PlayerTalkClass->SendCloseGossip();
            return;
        }
 
        Creature *creatureTarget = player->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
        if (!creatureTarget) return;
 
        Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
 
        if (!pet)
            return;
 
        creatureTarget->setDeathState(JUST_DIED);
        creatureTarget->RemoveCorpse();
        creatureTarget->SetHealth(0);                      
 
        pet->SetPower(POWER_HAPPINESS, 1048000);
        pet->SetUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUID());
        pet->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, player->getFaction());
        pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
        pet->GetMap()->AddToMap(pet->ToCreature());
        pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());
 
        pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);
        if (!pet->InitStatsForLevel(player->getLevel()))
            pet->UpdateAllStats();
 
        player->SetMinion(pet, true);
 
        pet->SavePetToDB(PET_SAVE_AS_CURRENT);
        pet->InitTalentForLevel();
        player->PetSpellInitialize();
 
        player->PlayerTalkClass->SendCloseGossip();
    }
 
 
    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override
    {
        if (player->IsInCombat())
        {
            player->GetSession()->SendAreaTriggerMessage("Você não pode usar esse item em combate!");
            CloseGossipMenuFor(player);
            return true;
        }
        ClearGossipMenuFor(player);
 
        AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_BeastTaming:30|t Novo Pet", GOSSIP_SENDER_MAIN, NORMAL_PET_PAGE_1);
        if (player->CanTameExoticPets())
        {
            AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_BeastMastery:30|t Novo pet Exótico", GOSSIP_SENDER_MAIN, EXOTIC_PET);
        }
        AddGossipItemFor(player, 4, "|TInterface\\Icons\\INV_Box_PetCarrier_01:30|t Stable Pet", GOSSIP_SENDER_MAIN, STABLE_PET);
        AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_GoForTheThroat:30|t Resetar o talento do Pet", GOSSIP_SENDER_MAIN, RESET_PET_TALENTS);
        AddGossipItemFor(player, 4, "|TInterface\\Icons\\INV_Scroll_11:30|t Renomear seu pet", GOSSIP_SENDER_MAIN, RENAME_PET);
        SendGossipMenuFor(player, 1, item->GetGUID());
        return true;
    }
 
    void OnGossipSelect(Player* player, Item* item, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);
 
        switch(action)
        {
			case MAIN_MENU:
				ClearGossipMenuFor(player);
 
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_BeastTaming:30|t Novo Pet", GOSSIP_SENDER_MAIN, NORMAL_PET_PAGE_1);
				if (player->CanTameExoticPets())
				{
					AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_BeastMastery:30|t Novo pet Exótico", GOSSIP_SENDER_MAIN, EXOTIC_PET);
				}
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\INV_Box_PetCarrier_01:30|t Guardar Pet", GOSSIP_SENDER_MAIN, STABLE_PET);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_GoForTheThroat:30|t Resetar o talento do Pet", GOSSIP_SENDER_MAIN, RESET_PET_TALENTS);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\INV_Scroll_11:30|t Renomear seu pet", GOSSIP_SENDER_MAIN, RENAME_PET);
				SendGossipMenuFor(player, 1, item->GetGUID());
				break;
 
			case NORMAL_PET_PAGE_1:
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Bat:30|t Bat", GOSSIP_SENDER_MAIN,                   1);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Bear:30|t Bear", GOSSIP_SENDER_MAIN,                 2);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Boar:30|t Boar", GOSSIP_SENDER_MAIN,                 3);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Cat:30|t Cat", GOSSIP_SENDER_MAIN,                   4);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Vulture:30|t Carrion Bird", GOSSIP_SENDER_MAIN,      5);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Crab:30|t Crab", GOSSIP_SENDER_MAIN,                 6);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Crocolisk:30|t Crocolisk", GOSSIP_SENDER_MAIN,       7);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_DragonHawk:30|t DragonHawk", GOSSIP_SENDER_MAIN,     8);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Gorilla:30|t Gorilla", GOSSIP_SENDER_MAIN,           9);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Wolf:30|t BlightHound", GOSSIP_SENDER_MAIN,          10);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Hyena:30|t Hyena", GOSSIP_SENDER_MAIN,               11);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Moth:30|t Moth", GOSSIP_SENDER_MAIN,                 12);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Owl:30|t Owl", GOSSIP_SENDER_MAIN,                   13);
				AddGossipItemFor(player, 2, "|TInterface\\Icons\\Trade_Engineering:30|t Próximo ->", GOSSIP_SENDER_MAIN, NORMAL_PET_PAGE_2);
				AddGossipItemFor(player, 2, "|TInterface\\Icons\\Trade_Engineering:30|t Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
				SendGossipMenuFor(player, 1, item->GetGUID());
				break;
 
			case NORMAL_PET_PAGE_2:
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Raptor:30|t Raptor", GOSSIP_SENDER_MAIN,             14);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Ravager:30|t Ravager", GOSSIP_SENDER_MAIN,           15);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_TallStrider:30|t Tallstrider", GOSSIP_SENDER_MAIN,   16);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Scorpid:30|t Scorpid", GOSSIP_SENDER_MAIN,           17);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Spider:30|t Spider", GOSSIP_SENDER_MAIN,             18);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_WindSerpent:30|t Serpent", GOSSIP_SENDER_MAIN,       19);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Turtle:30|t Turtle", GOSSIP_SENDER_MAIN,             20);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Wasp:30|t Wasp", GOSSIP_SENDER_MAIN,                 21);
				AddGossipItemFor(player, 2, "|TInterface\\Icons\\Trade_Engineering:30|t <- Anterior", GOSSIP_SENDER_MAIN, NORMAL_PET_PAGE_1);
				AddGossipItemFor(player, 2, "|TInterface\\Icons\\Trade_Engineering:30|t Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
				SendGossipMenuFor(player, 1, item->GetGUID());
				break;
 
			case EXOTIC_PET:
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Chimera:30|t Chimera", GOSSIP_SENDER_MAIN,           22);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_CoreHound:30|t Core Hound", GOSSIP_SENDER_MAIN,      23);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Devilsaur:30|t Devilsaur", GOSSIP_SENDER_MAIN,       24);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Rhino:30|t Rhino", GOSSIP_SENDER_MAIN,               25);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Silithid:30|t Silithid", GOSSIP_SENDER_MAIN,         26);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Worm:30|t Worm", GOSSIP_SENDER_MAIN,                 27);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\INV_Misc_Head_Tiger_01:30|t Loque'nahak", GOSSIP_SENDER_MAIN,           28);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\Ability_Hunter_Pet_Wolf:30|t Skoll", GOSSIP_SENDER_MAIN,                29);
				AddGossipItemFor(player, 4, "|TInterface\\Icons\\ability_mount_spectraltiger:30|t Spectral Tiger", GOSSIP_SENDER_MAIN,   30);
				AddGossipItemFor(player, 2, "|TInterface\\Icons\\Trade_Engineering:30|t Back to Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
				SendGossipMenuFor(player, 1, item->GetGUID());
				break;
               
			case 1:
				CreatePet(player, item, BAT);
				break;
 
			case 2:
				CreatePet(player, item, BEAR);
				break;
 
			case 3:
				CreatePet(player, item, BOAR);
				break;
 
			case 4:
				CreatePet(player, item, CAT);
				break;
 
			case 5:
				CreatePet(player, item, CARRION_BIRD);
				break;
 
			case 6:
				CreatePet(player, item, CRAB);
				break;
 
			case 7:
				CreatePet(player, item, CROCOLISK);
				break;
 
			case 8:
				CreatePet(player, item, DRAGONHAWK);
				break;
 
			case 9:
				CreatePet(player, item, GORILLA);
				break;
 
			case 10:
				CreatePet(player, item, BLIGHT_HOUND);
				break;
 
			case 11:
				CreatePet(player, item, HYENA);
				break;
 
			case 12:
				CreatePet(player, item, MOTH);
				break;
 
			case 13:
				CreatePet(player, item, OWL);
				break;
 
			case 14:
				CreatePet(player, item, RAPTOR);
				break;
 
			case 15:
				CreatePet(player, item, RAVAGER);
				break;
 
			case 16:
				CreatePet(player, item, TALLSTRIDER);
				break;
 
			case 17:
				CreatePet(player, item, SCORPID);
				break;
 
			case 18:
				CreatePet(player, item, SPIDER);
				break;
 
			case 19:
				CreatePet(player, item, SERPENT);
				break;
 
			case 20:
				CreatePet(player, item, TURTLE);
				break;
 
			case 21:
				CreatePet(player, item, WASP);
				break;
 
			case 22:
				CreatePet(player, item, CHIMERA);
				break;
           
			case 23:
				CreatePet(player, item, CORE_HOUND);
				break;
           
			case 24:
				CreatePet(player, item, DEVILSAUR);
				break;
 
			case 25:
				CreatePet(player, item, RHINO);
				break;
 
			case 26:
				CreatePet(player, item, SILITHID);
				break;
 
			case 27:
				CreatePet(player, item, WORM);
				break;
 
			case 28:
				CreatePet(player, item, LOQUE_NAHAK);
				break;
 
			case 29:
				CreatePet(player, item, SKOLL);
				break;

			case 30:
				CreatePet(player, item, GONDRIA);
				break;
           
			case RESET_PET_TALENTS:
				if (player->GetPet())
				{
					player->ResetPetTalents();
					player->GetSession()->SendAreaTriggerMessage("Os pontos de talentos de seu Pet foi resetado.");
					CloseGossipMenuFor(player);
				}
				else
				{
					player->GetSession()->SendNotification("Você não tem pet!");
					CloseGossipMenuFor(player);
				}
				break;
 
                       
			case STABLE_PET:
					player->CastSpell(player, 62757, true); // Call Stabled Pet
					CloseGossipMenuFor(player);
				break;
 
                       
			case RENAME_PET:
					player->CastSpell(player, 59385, true); //Certificate of Ownership Spell - no cast time
					CloseGossipMenuFor(player);
				break;
		}
    }
};
 
void AddSC_item_beastmaster()
{
    new item_beastmaster;
}