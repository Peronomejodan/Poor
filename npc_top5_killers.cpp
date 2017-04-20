/*
* PERONOMEJODAN FIX
 */

#include "ScriptPCH.h"

/*Class E_Menu*/
#define E_Warrior "Ver el Top 5 Guerreros con mas Muertes"
#define E_Paladin "Ver el Top 5 Paladines con mas Muertes"
#define E_Hunter "Ver el Top 5 Cazadores con mas Muertes"
#define E_Rogue "Ver el Top 5 Picaros con mas Muertes"
#define E_Priest "Ver el Top 5 Sacerdotes con mas Muertes"
#define E_Shaman "Ver el Top 5 Chamanes con mas Muertes"
#define E_Mage "Ver el Top 5 Magos con mas Muertes"
#define E_Warlock "Ver el Top 5 Brujos con mas Muertes"
#define E_Druid "Ver el Top 5 Druidas con mas Muertes"
#define E_Death_knight "Ver el Top 5 DKs con mas Muertes"
/*Top 5 Message*/
#define M_Warrior "Aqui están los 5 Guerreros con mas Muertes"
#define M_Paladin "Aqui están los 5 Paladines con mas Muertes"
#define M_Hunter "Aqui están los 5 Cazadores con mas Muertes"
#define M_Rogue "Aqui están los 5 Picaros con mas Muertes"
#define M_Priest "Aqui están los 5 Sacerdotes con mas Muertes"
#define M_Shaman "Aqui están los 5 Chamanes con mas Muertes"
#define M_Mage "Aqui están los 5 Magos con mas Muertes"
#define M_Warlock "Aqui están los 5 Brujos con mas Muertes"
#define M_Druid "Aqui están los 5 Druidas con mas Muertes"
#define M_Death_knight "Aqui están los 5 DKs con mas Muertes"

class Top5_Killers : public CreatureScript
{
	public:
		Top5_Killers() : CreatureScript("Top5_Killers") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        AddGossipItemFor(player, 1, E_Warrior, GOSSIP_SENDER_MAIN, 1);
        AddGossipItemFor(player, 1, E_Paladin, GOSSIP_SENDER_MAIN, 2);
        AddGossipItemFor(player, 1, E_Hunter, GOSSIP_SENDER_MAIN, 3);
        AddGossipItemFor(player, 1, E_Rogue, GOSSIP_SENDER_MAIN, 4);
        AddGossipItemFor(player, 1, E_Priest, GOSSIP_SENDER_MAIN, 5);
        AddGossipItemFor(player, 1, E_Shaman, GOSSIP_SENDER_MAIN, 7);
        AddGossipItemFor(player, 1, E_Mage, GOSSIP_SENDER_MAIN, 8);
        AddGossipItemFor(player, 1, E_Warlock, GOSSIP_SENDER_MAIN, 9);
        AddGossipItemFor(player, 1, E_Druid, GOSSIP_SENDER_MAIN, 11);
        AddGossipItemFor(player, 1, E_Death_knight, GOSSIP_SENDER_MAIN, 6);
        SendGossipMenuFor(player, 1, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (sender != GOSSIP_SENDER_MAIN)
            return true; // wrong sender, something fisy

        switch(action)
        {
			case 1: ChatHandler(player->GetSession()).PSendSysMessage(M_Warrior);       break;
			case 2: ChatHandler(player->GetSession()).PSendSysMessage(M_Paladin);       break;
			case 3: ChatHandler(player->GetSession()).PSendSysMessage(M_Hunter);        break;
			case 4: ChatHandler(player->GetSession()).PSendSysMessage(M_Rogue);         break;
			case 5: ChatHandler(player->GetSession()).PSendSysMessage(M_Priest);        break;
			case 6: ChatHandler(player->GetSession()).PSendSysMessage(M_Death_knight);  break;
			case 7: ChatHandler(player->GetSession()).PSendSysMessage(M_Shaman);        break;
			case 8: ChatHandler(player->GetSession()).PSendSysMessage(M_Mage);          break;
			case 9: ChatHandler(player->GetSession()).PSendSysMessage(M_Warlock);       break;
			case 11: ChatHandler(player->GetSession()).PSendSysMessage(M_Druid);        break;
			default: return true; // invalid class, something fishy
        }

        QueryResult result = CharacterDatabase.PQuery("SELECT name, totalKills FROM characters WHERE class = %u ORDER BY totalKills DESC LIMIT 5", action);
        if(result)
        {
            do
            {
                Field * fields = result->Fetch();
                std::string name = fields[0].GetString();
                uint32 totalKills = fields[1].GetUInt32();
                ChatHandler(player->GetSession()).PSendSysMessage("Nombre: %s, con %u Muertes", name.c_str(), totalKills);
            } 
            while(result->NextRow());
        }
        OnGossipHello(player, creature); // volver al menu principal
        return true;
    }
};


void AddSC_Top5_Killers()
{
    new Top5_Killers();
}