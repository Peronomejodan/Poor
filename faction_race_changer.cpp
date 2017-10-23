/*
<--------------------------------------------------------------------------->
 - Developer(s): Ghostcrawler336
 - Updated 2017: beimax76
 - Complete: 100%
 - ScriptName: 'Faction / Race Changer' 
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

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

enum  defines
{
 faction_token = 100005, // Faction Change Token
 race_token = 100006 // Race Change Token
};

class npc_changer : public CreatureScript
{
	public:
		npc_changer() : CreatureScript("npc_changer"){}
		
	class changerAI : public ScriptedAI
    {
				
	    public:
		changerAI(Creature* creature) : ScriptedAI(creature) {}
		
		 void CreatureWhisperBasedOnBool(const char *text, Creature *creature, Player *player, bool value)
				{
					if (value)
					creature->TextEmote(text, player);
				}
				
			   bool GossipHello(Player* pPlayer) override
				{
						return OnGossipHello(pPlayer, me);
				}

		 bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			
			
			    ClearGossipMenuFor(pPlayer);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_CHAT, "|TInterface/ICONS/Achievement_character_human_female:35:35|tChange My Race ", GOSSIP_SENDER_MAIN, 0);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_CHAT, "|TInterface/ICONS/Achievement_character_orc_male:35:35|tChange My Faction", GOSSIP_SENDER_MAIN, 1);
			    SendGossipMenuFor(pPlayer, DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
			    return true;


		}
		
	bool GossipSelect(Player* pPlayer, uint32 /*menu_id*/, uint32 gossipListId) override
		{
			uint32 sender = pPlayer->PlayerTalkClass->GetGossipOptionSender(gossipListId);
			uint32 action = pPlayer->PlayerTalkClass->GetGossipOptionAction(gossipListId);
			return OnGossipSelect(pPlayer, me, sender, action);
		}

		bool OnGossipSelect(Player * pPlayer, Creature * Creature, uint32 uiSender, uint32 uiAction)
    {
		
	    ClearGossipMenuFor(pPlayer);
			   
	    if (uiSender == GOSSIP_SENDER_MAIN)
	    {
				
				
			switch(uiAction)
			{
				case 0:
					if(pPlayer->HasItemCount(race_token, 1))
					{
						pPlayer->DestroyItemCount(race_token, 1, true, false);
						pPlayer->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
						pPlayer->GetSession()->SendNotification("You need to relog, to change your race!");
						CloseGossipMenuFor(pPlayer);
					}
					else
					{
						pPlayer->GetSession()->SendNotification("You need atleast one race change token!");
						CloseGossipMenuFor(pPlayer);
					}
					break;
				case 1:
					if(pPlayer->HasItemCount(faction_token, 1))
					{
						pPlayer->DestroyItemCount(faction_token, 1, true, false);
						pPlayer->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
						pPlayer->GetSession()->SendNotification("You need to relog, to change your faction!");
						CloseGossipMenuFor(pPlayer);
					}
					else
					{
						pPlayer->GetSession()->SendNotification("You need atleast one faction change token!");
						CloseGossipMenuFor(pPlayer);
					}
					break;
			}
			
			
		  
		}
		
		return true;
	}	
		
};
	
	CreatureAI* GetAI(Creature* creature) const override
	{
		return  new changerAI(creature);
	}

};

void AddSC_npc_changer()
{
	new npc_changer();
}