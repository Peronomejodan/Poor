/*
* PERONOMEJODAN FIX
 */

#include "ScriptPCH.h"

class npc_promo : public CreatureScript 
{
	public:
		npc_promo() : CreatureScript("npc_promo") { } 
 
    bool OnGossipHello(Player* player, Creature* creature) 
    {
        AddGossipItemFor(player, 7, "Elige una promocion: ", GOSSIP_SENDER_MAIN, 99);//Message Translation - "Choose Promotion: "
		switch (player->getClass())
		{
			case CLASS_DRUID: 
				AddGossipItemFor(player, 10, "Druid Balance", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+30); 
				AddGossipItemFor(player, 10, "Druid Feral", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+44); 
				AddGossipItemFor(player, 10, "Druida Restoration", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+45); 
				break;

			case CLASS_SHAMAN: 
				AddGossipItemFor(player, 10, "Shaman Elemental", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+31); 
				AddGossipItemFor(player, 10, "Shaman Enhancement", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+46); 
				AddGossipItemFor(player, 10, "Shaman Restoration", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+47); 
				break;

			case CLASS_PALADIN: 
				AddGossipItemFor(player, 10, "Paladin Retribution", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+32); 
				AddGossipItemFor(player, 10, "Paladin Holy", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+40); 
				AddGossipItemFor(player, 10, "Paladin Protection", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+41); 
				break;

			case CLASS_WARRIOR: 
				AddGossipItemFor(player, 10, "Warrior Fury", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+33); 
				AddGossipItemFor(player, 10, "Warrior Arms", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+48); 
				AddGossipItemFor(player, 10, "Warrior Protection", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+50); 
				break;

			case CLASS_PRIEST: 
				AddGossipItemFor(player, 10, "Priest Shadow", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+34); 
				AddGossipItemFor(player, 10, "Priest Holy", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+42); 
				AddGossipItemFor(player, 10, "Priest Dicipline", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+49); 
				break;

			case CLASS_DEATH_KNIGHT: 
				AddGossipItemFor(player, 10, "Death Knight DPS", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+35); 
				AddGossipItemFor(player, 10, "Death Knight Tank", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+43); 
				break;

			case CLASS_ROGUE: 
				AddGossipItemFor(player, 10, "Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+36); 
				break;

			case CLASS_HUNTER: 
				AddGossipItemFor(player, 10, "Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+37); 
				break;

			case CLASS_MAGE: 
				AddGossipItemFor(player, 10, "Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+38); 
				break;

			case CLASS_WARLOCK: 
				AddGossipItemFor(player, 10, "Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+39); 
				break;
		}
        SendGossipMenuFor(player, 1, creature->GetGUID()); 
        return true;
    }
 
    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 actions)
    {
	    
		if (player->getLevel() == 80) 
		{
            player->GetSession()->SendAreaTriggerMessage("No puedes recibir la promocion mas de una vez.");//Message Translation - "You can only recieve one promotion"
			CloseGossipMenuFor(player);
			return true;
        }
		
        if (player->getLevel() >= 1) 
        {
            uint32 accountID = player->GetSession()->GetAccountId();
            QueryResult result = CharacterDatabase.PQuery("SELECT COUNT(`guid`) FROM `characters` WHERE `account`=%u", accountID);
            Field *fields = result->Fetch();
            uint32 character = fields[0].GetUInt32();

            if (character == 1)
			{
				if (actions == 99)
				{
					CloseGossipMenuFor(player);
					return false;
				}
				player->GetSession()->SendAreaTriggerMessage("Has recibido la promocion correctamente.");// Message Translation - "Promotion delivered with sucess"
                player->GiveLevel(80); //Nivel Otorgado al Personaje
				player->SetMoney(800000000); //Oro
				//player->AddItem(41599, 4); //Bolsas de 20 Casillas
			    //player->LearnSpell(34092, true);	//Experto jinete
			    //player->LearnSpell(54197, true);	//Vuelo clima frio
			    //player->LearnSpell(39450, false);	//Montura Terrestre
			    //player->LearnSpell(64927, false);	//Montura voladora
			    //player->CastSpell(player, 63680, true);	//Enseñar Aprender a Alternar Especialización de Talentos
			    //player->CastSpell(player, 63624, true);	//Aprender Segunda Especialización de Talentos
				switch(actions)
                {								  
					case GOSSIP_ACTION_INFO_DEF+30: // Druid Balance
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;
								  
					case GOSSIP_ACTION_INFO_DEF+44: // Druid Feral
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;
								  
					case GOSSIP_ACTION_INFO_DEF+45: // Druid Restoration
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;

					case GOSSIP_ACTION_INFO_DEF+31: // Shaman Elemental
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;
								  
					case GOSSIP_ACTION_INFO_DEF+46: // Shaman Enhancement
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;
								  
					case GOSSIP_ACTION_INFO_DEF+47: // Shaman Restoration
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;

					case GOSSIP_ACTION_INFO_DEF+32: // Paladin Retribution
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;
								  
					case GOSSIP_ACTION_INFO_DEF+40: // Paladin Holy
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;
								  
					case GOSSIP_ACTION_INFO_DEF+41: // Paladin Protection
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;

					case GOSSIP_ACTION_INFO_DEF+33: // Warrior Fury
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;
								  
					case GOSSIP_ACTION_INFO_DEF+48: // Warrior Arms
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;
								  
					case GOSSIP_ACTION_INFO_DEF+50: // Warrior Protection
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
					break;
								  
					case GOSSIP_ACTION_INFO_DEF+49: // Priest Dicipline
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;

					case GOSSIP_ACTION_INFO_DEF+34: // Priest Shadow
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;
								  
					case GOSSIP_ACTION_INFO_DEF+42: // Priest Holy
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;

					case GOSSIP_ACTION_INFO_DEF+35: // Death Knight DPS
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;
								  
					case GOSSIP_ACTION_INFO_DEF+43: // Death Knight Tank
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;

					case GOSSIP_ACTION_INFO_DEF+36: // Rogue
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
					break;

					case GOSSIP_ACTION_INFO_DEF+37: // Hunter
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;

					case GOSSIP_ACTION_INFO_DEF+38: // Mage
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;

					case GOSSIP_ACTION_INFO_DEF+39: // Warlock
						player->AddItem(49284, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						player->AddItem(0, 1);
						CloseGossipMenuFor(player);
						break;
				}
            }			
			
			if (character > 1)
			{
                player->GetSession()->SendAreaTriggerMessage("Solo puedes usar esto en un personaje por cuenta.");
															//Message Translation - "You can only use the promotion in one of your characters of"
				CloseGossipMenuFor(player);
				return true;
            }
			
		    CloseGossipMenuFor(player);
        }
        return true;
    }
};
 
void AddSC_npc_promo() 
{
    new npc_promo(); 
}