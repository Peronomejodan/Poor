/*
<--------------------------------------------------------------------------->
 - Developer(s): Ghostcrawler336
 - Updated 2017: Beimax76
 - Complete: 100%
 - ScriptName: 'Exchange NPC' 
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

class npc_exchanger : public CreatureScript
{
public:
    npc_exchanger() : CreatureScript("npc_exchanger") { }
	
	class exchangerAI : public ScriptedAI
    {
				
		public:
		exchangerAI(Creature* creature) : ScriptedAI(creature) {}
		
		 void CreatureWhisperBasedOnBool(const char *text, Creature *creature, Player *player, bool value)
				{
					if (value)
					creature->TextEmote(text, player);
				}
				
			   bool GossipHello(Player* player) override
				{
					
						return OnGossipHello(player, me);
				}

		 bool OnGossipHello(Player *player, Creature *_creature)
		{
			
					ClearGossipMenuFor(player);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Inv_misc_coin_02:35:35|t400 Gold -> 20000 Honor", GOSSIP_SENDER_MAIN, 5);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Inv_misc_coin_02:35:35|t800 Gold -> 40000 Honor", GOSSIP_SENDER_MAIN, 6);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Inv_misc_coin_02:35:35|t1200 Gold -> 60000 Honor", GOSSIP_SENDER_MAIN, 7);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Achievement_pvp_a_16:35:35|t80000 Honor -> 250 Arena points", GOSSIP_SENDER_MAIN, 8);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Achievement_pvp_a_16:35:35|t100000 Honor -> 350 Arena points", GOSSIP_SENDER_MAIN, 9);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Achievement_pvp_a_16:35:35|t200000 Honor -> 450 Arena points", GOSSIP_SENDER_MAIN, 10);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Inv_misc_coin_02:35:35|t1000 Gold -> 100 Arena points", GOSSIP_SENDER_MAIN, 11);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Inv_misc_coin_02:35:35|t2000 Gold -> 250 Arena points", GOSSIP_SENDER_MAIN, 12);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Inv_misc_coin_02:35:35|t3000 Gold -> 350 Arena points", GOSSIP_SENDER_MAIN, 13);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Achievement_pvp_a_h:35:35|t400 Arena Points -> 40000 Honor", GOSSIP_SENDER_MAIN, 14);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Achievement_pvp_a_h:35:35|t500 Arena Points -> 50000 Honor", GOSSIP_SENDER_MAIN, 15);
					AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Achievement_pvp_a_h:35:35|t600 Arena Points -> 60000 Honor", GOSSIP_SENDER_MAIN, 16);
					SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
					return true;
		

		}
    bool GossipSelect(Player* player, uint32 /*menu_id*/, uint32 gossipListId) override
		{
			uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
			uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
			return OnGossipSelect(player, me, sender, action);
		}
    bool OnGossipSelect(Player *player, Creature *creature, uint32 uiSender, uint32 uiAction)
    {
		    ClearGossipMenuFor(player);
			
            if (uiSender == GOSSIP_SENDER_MAIN)
        {
             
				
 
				switch(uiAction)
			
			{					

				case 5: // 400 Gold -> 20000 Honor
                if (player->GetMoney() >= 400)
                {
                    
					player->ModifyMoney(-400);
                    player->ModifyHonorPoints(+20000);
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough gold points to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;
				case 6: //800 Gold -> 40000 Honor
                if (player->GetMoney() >= 800)
                {
                    
					player->ModifyMoney(-800);
                    player->ModifyHonorPoints(+40000);                    
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough gold points to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;
				case 7: //1200 Gold -> 60000 Honor
                if (player->GetMoney() >= 1200)
                {
                    
					player->ModifyMoney(-1200);
                    player->ModifyHonorPoints(+60000);
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough gold points to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;
				case 8: //80000 Honor -> 250 Arena points
                if (player->GetHonorPoints() >= 80000)
                {
                    
                    player->ModifyHonorPoints(-80000);
                    player->ModifyArenaPoints(+250);
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough honor points to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;
				case 9: //100000 Honor -> 350 Arena points
                if (player->GetHonorPoints() >= 100000)
                {
                    
                    player->ModifyHonorPoints(-10000);
                    player->ModifyArenaPoints(+350);
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough honor points to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;
				case 10: //200000 Honor -> 450 Arena points
                if (player->GetHonorPoints() >= 200000)
                {
                    
                    player->ModifyHonorPoints(-200000);
                    player->ModifyArenaPoints(+450);
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough honor points to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;

				case 11: //1000 Gold -> 100 Arena points
                if (player->GetMoney() >= 1000)
                {
                    
					player->ModifyMoney(-1000);
                    player->ModifyArenaPoints(+100);                   
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough arena gold to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;
				case 12: //2000 Gold -> 250 Arena points 
                if (player->GetMoney() >= 2000)
                {
                    
					player->ModifyMoney(-2000);
                    player->ModifyArenaPoints(+250);                   
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough gold points to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;
				case 13: //3000 Gold -> 350 Arena points 
                if (player->GetMoney() >= 3000)
                {
                    
					player->ModifyMoney(-3000);
                    player->ModifyArenaPoints(+350);                  
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough gold points to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;
				case 14: //400 Arena Points -> 40000 Honor 
                if (player->GetArenaPoints() >= 400)
                {
                    
                    player->ModifyArenaPoints(-400);
                    player->ModifyHonorPoints(+40000);
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough arena points to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;
				case 15: //500 Arena Points -> 50000 Honor
                if (player->GetArenaPoints() >= 500)
                {
                    
                    player->ModifyArenaPoints(-500);
                    player->ModifyHonorPoints(+50000);
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough arena points to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;
				case 16: //600 Arena Points -> 60000 Honor
                if (player->GetArenaPoints() >= 600)
                {
                    
                    player->ModifyArenaPoints(-600);
                    player->ModifyHonorPoints(+60000);
                    creature->TextEmote("You exchanged succesfully!", player);
					OnGossipHello(player, creature);
                }
                else
                {
                    
                    creature->TextEmote("I'm sorry, but you don't have enough arena points to make this exchange.", player);
                    OnGossipHello(player, creature);
                }break;
		    
			}
		
		}
		return true;
    }
	
  };
  
  CreatureAI* GetAI(Creature* creature) const override
	{
		return  new exchangerAI(creature);
	}
	
};

void AddSC_npc_exchanger()
{
    new npc_exchanger();
}