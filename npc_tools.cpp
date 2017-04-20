/*
* PERONOMEJODAN FIX

SQL NPC

DELETE FROM `creature_template` WHERE (entry = 900000);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(900000, 0, 0, 0, 0, 0, 25795, 0, 0, 0, 'NPC TOOLS', 'PERONOMEJODAN', '', 0, 1, 80, 0, 35, 1, 1, 1.14286, 1.5, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 50, 50, 1, 0, 1, 0, 0, 1, 0, 0, 'NPC_TOOLS', 0);

 */

#include "Player.h"
#include "Define.h"
#include "Creature.h"
#include "ScriptMgr.h"
#include "WorldSession.h"
#include "ScriptedGossip.h"
#include "Language.h"

uint32 vAuras1[] = {59908,21562, 20217, 6673};

class NPC_TOOLS : public CreatureScript
{
public:
        NPC_TOOLS() : CreatureScript("NPC_TOOLS") { }
 
	bool OnGossipHello(Player * player, Creature * creature)
    {
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\Spell_Nature_Regenerate:30:30:-15|t Buffs y Restaurar Vida/Mana", GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\Spell_Shadow_UnstableAffliction_1:30:30:-15|t Quitar CDs de Mazmorras", GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\SPELL_HOLY_BORROWEDTIME:30:30:-15|t Quitar CDs de Habilidades", GOSSIP_SENDER_MAIN, 3);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\Achievement_BG_AB_defendflags:30:30:-15|t Quitar Combate", GOSSIP_SENDER_MAIN, 4);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\Spell_Shadow_DeathScream:30:30:-15|t Quitar Dolencia", GOSSIP_SENDER_MAIN, 5);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\INV_Hammer_24:30:30:-15|t Reparar Armadura", GOSSIP_SENDER_MAIN, 6);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\Achievement_WorldEvent_Lunar:30:30:-15|t Eliminar Talentos", GOSSIP_SENDER_MAIN, 7);
		AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "|TInterface\\icons\\Achievement_WorldEvent_Lunar:30:30:-15|t Salir", GOSSIP_SENDER_MAIN, 8);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
        }
	bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 actions)
    {
        ClearGossipMenuFor(player);

		switch (actions)
        {
			case 1: // Buff mana y vida
					if(player->IsInCombat())
					{
						player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFEstas en combate!");
						player->PlayerTalkClass->SendCloseGossip();
							return false;
					}
					else if(player->getPowerType() == POWER_MANA)
							player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
					for (uint32 i = 0; i < (sizeof(vAuras1) / sizeof(*vAuras1)); i++)
						player->AddAura(vAuras1[i], player);
						player->SetHealth(player->GetMaxHealth());
						player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFHas obtenido Buffos, vida y mana Correctamente!");
						player->CastSpell(player, 36400);
						CloseGossipMenuFor(player);
					break;

			case 2: // Cd de estancias
					for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
					{
							Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
							for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
							{
									player->UnbindInstance(itr, Difficulty(i));
							}
					}
					player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFTus CDs de Mazmorras/Raids han sido eliminados Correctamente!");
					player->CastSpell(player, 59908);
					CloseGossipMenuFor(player);
					break;

			case 3: // Cd de habilidades
					if(player->IsInCombat())
					{
						player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFEstas en combate!");
						player->PlayerTalkClass->SendCloseGossip();
							return false;
					}
 
					player->GetSpellHistory()->ResetAllCooldowns();
					player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFCDs de Habilidades restaurado Correctamente!");
					player->CastSpell(player, 463);
					CloseGossipMenuFor(player);
					break;

			case 4: // Quitar combate
					player->CombatStop();
					player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFHas salido de Combate Correctamente!");
					player->CastSpell(player, 24222);
					CloseGossipMenuFor(player);
					break;

			case 5: // Dolencia
					if(player->HasAura(15007))
					player->RemoveAura(15007);
					player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFDolencia de Resurrecion eliminada Correctamente!");
					player->CastSpell(player, 41300);
					CloseGossipMenuFor(player);
					break;

			case 6: // Reparar
					player->DurabilityRepairAll(false, 0, false);
					player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFObjetos reparados Correctamente!");
					player->CastSpell(player, 29541);
					CloseGossipMenuFor(player);
					break;

			case 7: // Quitar talentos
					player->ResetTalents(true);
					player->SendTalentsInfoData(false);
					player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFTus talentos han sido olvidados Correctamente!");
					player->CastSpell(player, 19484);
					CloseGossipMenuFor(player);
					break;

			case 8: // texto al cerrar menu
					player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFOVuelve pronto!");
					CloseGossipMenuFor(player);
					break;
		}
		return true;
	}
};
 
void AddSC_NPC_TOOLS()
{
        new NPC_TOOLS();
}