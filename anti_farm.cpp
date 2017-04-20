/*
* PERONOMEJODAN FIX
 */
 
#include "ScriptPCH.h"

using namespace std;
 
class anti_farm : public PlayerScript
{
public: anti_farm() : PlayerScript("anti_farm") {}
 
	void OnPVPKill(Player * killer, Player * killed)
	{
		if (killer->GetGUID() == killed->GetGUID())
		{
				return;
		}
 
		if (killer->GetSession()->GetRemoteAddress() == killed->GetSession()->GetRemoteAddress() || killed->GetMaxHealth() <= 10000) // Normally players try farm with new characters with low health then modify the Health according your server.
		{
			string str = "";
			SessionMap ss = sWorld->GetAllSessions();
			for (SessionMap::const_iterator itr = ss.begin(); itr != ss.end(); ++itr)
					if (itr->second->GetSecurity() > 0)
			str = "|cFFFFFC00[Aviso de Anti Farm]|cFF00FFFF[|cFF60FF00" + string(killer->GetName()) + "|cFF00FFFF] Es un posible farmer |CFFEE0000 [ALERTA MJS!]";
			WorldPacket data(SMSG_NOTIFICATION, (str.size()+1));
			data << str;
			sWorld->SendGlobalGMMessage(&data);
		}
		else return;
	}
 
};
void AddSC_anti_farm()
{
   new anti_farm;
}