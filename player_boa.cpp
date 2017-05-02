#include "Player.h"
#include "Chat.h"
#define Welcome_Name "Your Servername"

class Player_Boa : public PlayerScript
{

public:
    Player_Boa() : PlayerScript("Player_Boa") { }

    void OnLogin(Player* player, bool firstLogin) override
    {
        if (!firstLogin) // Run script only on first login
            return;
        std::ostringstream ss;
        ss << "|cffFF0000["<<Welcome_Name<<"]|r Welcome " << player->GetName() << " to the server! ";
        sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
        uint32 shoulders = 0, chest = 0, ring = 0, trinkett = 0, weapon = 0, weapon2 = 0;

        ring = 50255;
        switch (player->getClass())
        {
                case CLASS_WARRIOR:
                //Warrior
                shoulders = 42949;
                chest = 48685;
                trinkett = 42991;
                weapon = 42945;
                break;
                case CLASS_PALADIN:
                //Paladin
                shoulders = 42949;
                chest = 48685;
                trinkett = 42991;
                weapon = 42945;
                break;
                case CLASS_HUNTER:
                //Hunter
                shoulders = 42950;
                chest = 48677;
                trinkett = 42991;
                weapon = 42943;
                weapon2 = 42946;
                break;
                case CLASS_ROGUE:
                //Rogue
                shoulders = 42952;
                chest = 48689;
                trinkett = 42991;
                weapon = 42944;
                weapon2 = 42944;
                break;
                case CLASS_PRIEST:
                //Priest
                shoulders = 42985;
                chest = 48691;
                trinkett = 42992;
                weapon = 42947;
                break;
                case CLASS_DEATH_KNIGHT:
                //Death Knight
                shoulders = 42949;
                chest = 48685;
                trinkett = 42991;
                weapon = 42945;
                break;
                case CLASS_SHAMAN:
                //Shaman
                shoulders = 42951;
                chest = 48683;
                trinkett = 42992;
                weapon = 42948;
                break;
                case CLASS_MAGE:
                //Mage
                shoulders = 42985;
                chest = 48691;
                trinkett = 42992;
                weapon = 42947;
                break;
                case CLASS_WARLOCK:
                //Warlock
                shoulders = 42985;
                chest = 48691;
                trinkett = 42992;
                weapon = 42947;
                break;
                case CLASS_DRUID:
                //Druid
                shoulders = 42984;
                chest = 48687;
                trinkett = 42992;
                weapon = 42948;
                break;
                default:
                return;
            }
            switch(player->getClass())
                {
                    case CLASS_HUNTER:
                        player->AddItem(shoulders, 1);
                        player->AddItem(trinkett, 2);
                        player->AddItem(ring, 1);
                        player->AddItem(chest, 1);
                        player->AddItem(weapon, 1);
                        player->AddItem(weapon2, 1);
                        break;
                    case CLASS_ROGUE:
                        player->AddItem(shoulders, 1);
                        player->AddItem(trinkett, 2);
                        player->AddItem(ring, 1);
                        player->AddItem(chest, 1);
                        player->AddItem(weapon, 1);
                        player->AddItem(weapon2, 1);
                        break;
                    default:
                        player->AddItem(shoulders, 1);
                        player->AddItem(trinkett, 2);
                        player->AddItem(ring, 1);
                        player->AddItem(chest, 1);
                        player->AddItem(weapon, 1);
                    }
            }
};

void AddSC_Player_Boa()
{
    new Player_Boa();
}