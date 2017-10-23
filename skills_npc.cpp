/*
created: ???
Updated 2017: beimax76
*/
#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GameEventMgr.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Unit.h"
#include "GameObject.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "InstanceScript.h"
#include "CombatAI.h"
#include "PassiveAI.h"
#include "Chat.h"
#include "DBCStructure.h"
#include "DBCStores.h"
#include "ObjectMgr.h"
#include "SpellScript.h"
#include "SpellInfo.h"
#include "SpellAuraEffects.h"
#include "Language.h"

#include "Bag.h"
#include "Common.h"
#include "Config.h"
#include "Creature.h"
#include "DatabaseEnv.h"
#include "DBCStructure.h"
#include "Define.h"
#include "Field.h"
#include "GameEventMgr.h"
#include "GossipDef.h"
#include "Item.h"
#include "ItemTemplate.h"
#include "Language.h"
#include "Log.h"
#include "Player.h"
#include "ObjectGuid.h"
#include "ObjectMgr.h"
#include "QueryResult.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "SharedDefines.h"
#include "Transaction.h"
#include "WorldSession.h"
#include <sstream>
#include <string>

enum SkillSpells
{
        SPELL_BLOCK = 107,
        SPELL_BOWS = 264,
        SPELL_CROSSBOWS = 5011,
        SPELL_DAGGERS = 1180,
        SPELL_DUAL_WIELD = 674,
        SPELL_FIST_WEAPONS = 15590,
        SPELL_GUNS = 266,
        SPELL_MAIL = 8737,
        SPELL_PLATE = 750,
        SPELL_ONE_HANDED_AXES = 196,
        SPELL_ONE_HANDED_MACES = 198,
        SPELL_ONE_HANDED_SWORDS = 201,
        SPELL_TWO_HANDED_AXES = 197,
        SPELL_TWO_HANDED_MACES = 199,
        SPELL_TWO_HANDED_SWORDS = 202,
        SPELL_STAVES = 227,
        SPELL_THROW = 2764,
        SPELL_THROWN = 2567,
        SPELL_POLEARMS = 200,
        SPELL_RELIC = 52665,
        SPELL_RELIC_2 = 27764,
        SPELL_RELIC_3 = 27762,
        SPELL_RELIC_4 = 27763,
        SPELL_SHIELD = 9116,
        SPELL_SHOOT = 3018,
        SPELL_SHOOT_WANDS = 5019,
        SPELL_WANDS = 5009
};

class skills_npc : public CreatureScript
{
public:
	skills_npc() : CreatureScript("skills_npc") { }

	class skillsAI : public ScriptedAI
	{
		public:
			skillsAI(Creature* creature) : ScriptedAI(creature) {}
			
		void CreatureWhisperBasedOnBool(const char *text, Creature *creature, Player *player, bool value)
		{
			if (value)
			creature->TextEmote(text, player);
		}
			
		bool GossipHello(Player* player) override
		{
			return OnGossipHello(player, me);
		}
		
		bool OnGossipHello(Player* player, Creature* creature)
		{
			ClearGossipMenuFor(player);
			AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "Learn All Ability.", GOSSIP_SENDER_MAIN, 1);
			SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			return true;
		}
		
		bool GossipSelect(Player* player, uint32 /*menu_id*/, uint32 gossipListId) override
		{
			uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
			uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
			return OnGossipSelect(player, me, sender, action);
		}
		
		bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
		{
			ClearGossipMenuFor(player);
			if(uiSender == GOSSIP_SENDER_MAIN)
			{
				switch(uiAction)
				{
					case 1:
					
						switch(player->getClass())
                                {
                                   case CLASS_PALADIN:
                                           {
                                                   player->LearnSpell(SPELL_BLOCK, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
                                                   player->LearnSpell(SPELL_PLATE, true);
                                                   player->LearnSpell(SPELL_POLEARMS, true);
                                                   player->LearnSpell(SPELL_RELIC_3, true);
                                                   player->LearnSpell(SPELL_SHIELD, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_AXES, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_MACES, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_SWORDS, true);
                                           }break;
 
                                   case CLASS_SHAMAN:
                                           {
                                                   player->LearnSpell(SPELL_BLOCK, true);
                                                   player->LearnSpell(SPELL_FIST_WEAPONS, true);
                                                   player->LearnSpell(SPELL_MAIL, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
                                                   player->LearnSpell(SPELL_RELIC_4, true);
                                                   player->LearnSpell(SPELL_SHIELD, true);
                                                   player->LearnSpell(SPELL_STAVES, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_AXES, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_MACES, true);
                                           }break;
 
                                   case CLASS_WARRIOR:
                                           {
                                                   player->LearnSpell(SPELL_BLOCK, true);
                                                   player->LearnSpell(SPELL_BOWS, true);
                                                   player->LearnSpell(SPELL_CROSSBOWS, true);
                                                   player->LearnSpell(SPELL_DUAL_WIELD, true);
                                                   player->LearnSpell(SPELL_FIST_WEAPONS, true);
                                                   player->LearnSpell(SPELL_GUNS, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
                                                   player->LearnSpell(SPELL_PLATE, true);
                                                   player->LearnSpell(SPELL_POLEARMS, true);
                                                   player->LearnSpell(SPELL_SHIELD, true);
                                                   player->LearnSpell(SPELL_SHOOT, true);
                                                   player->LearnSpell(SPELL_STAVES, true);
                                                   player->LearnSpell(SPELL_THROW, true);
                                                   player->LearnSpell(SPELL_THROWN, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_AXES, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_MACES, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_SWORDS, true);
                                           }break;
 
                                   case CLASS_HUNTER:
                                           {
                                                   player->LearnSpell(SPELL_BOWS, true);
                                                   player->LearnSpell(SPELL_CROSSBOWS, true);
                                                   player->LearnSpell(SPELL_DUAL_WIELD, true);
                                                   player->LearnSpell(SPELL_FIST_WEAPONS, true);
                                                   player->LearnSpell(SPELL_GUNS, true);
                                                   player->LearnSpell(SPELL_MAIL, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
                                                   player->LearnSpell(SPELL_POLEARMS, true);
                                                   player->LearnSpell(SPELL_STAVES, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_AXES, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_SWORDS, true);
                                           }break;
 
                                   case CLASS_ROGUE:
                                           {
                                                   player->LearnSpell(SPELL_BOWS, true);
                                                   player->LearnSpell(SPELL_CROSSBOWS, true);
                                                   player->LearnSpell(SPELL_DUAL_WIELD, true);
                                                   player->LearnSpell(SPELL_FIST_WEAPONS, true);
                                                   player->LearnSpell(SPELL_GUNS, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
                                                   player->LearnSpell(SPELL_SHOOT, true);
                                                   player->LearnSpell(SPELL_THROW, true);
                                                   player->LearnSpell(SPELL_THROWN, true);
                                           }break;
 
                                   case CLASS_DRUID:
                                           {
                                                   player->LearnSpell(SPELL_DAGGERS, true);
                                                   player->LearnSpell(SPELL_FIST_WEAPONS, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
                                                   player->LearnSpell(SPELL_POLEARMS, true);
                                                   player->LearnSpell(SPELL_RELIC_2, true);
                                                   player->LearnSpell(SPELL_STAVES, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_MACES, true);
                                           }break;
 
                                   case CLASS_MAGE:
                                           {
                                                   player->LearnSpell(SPELL_DAGGERS, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
                                                   player->LearnSpell(SPELL_SHOOT_WANDS, true);
                                                   player->LearnSpell(SPELL_STAVES, true);
                                                   player->LearnSpell(SPELL_WANDS, true);
                                           }break;
 
                                   case CLASS_WARLOCK:
                                           {
                                                   player->LearnSpell(SPELL_DAGGERS, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
                                                   player->LearnSpell(SPELL_SHOOT_WANDS, true);
                                                   player->LearnSpell(SPELL_STAVES, true);
                                                   player->LearnSpell(SPELL_WANDS, true);
                                           }break;
 
                                   case CLASS_PRIEST:
                                           {
                                                   player->LearnSpell(SPELL_DAGGERS, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
                                                   player->LearnSpell(SPELL_SHOOT_WANDS, true);
                                                   player->LearnSpell(SPELL_STAVES, true);
                                                   player->LearnSpell(SPELL_WANDS, true);
                                           }break;
 
                                   case CLASS_DEATH_KNIGHT:
                                           {
                                                   player->LearnSpell(SPELL_DUAL_WIELD, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
                                                   player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
                                                   player->LearnSpell(SPELL_PLATE, true);
                                                   player->LearnSpell(SPELL_POLEARMS, true);
                                                   player->LearnSpell(SPELL_RELIC, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_AXES, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_MACES, true);
                                                   player->LearnSpell(SPELL_TWO_HANDED_SWORDS, true);
                                           }break;
                                }
						creature->TextEmote("You Already now all your abilities", player);	
						player->UpdateWeaponsSkillsToMaxSkillsForLevel();
						CloseGossipMenuFor(player);
				
					break;
				}
			
			}

			return true;
			
		}
		
	};
	
		CreatureAI* GetAI(Creature* creature) const override
	{
		return  new skillsAI(creature);
	}
	
};

void AddSC_skills_npc()
{
	new skills_npc();
}