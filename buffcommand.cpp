/*
<--------------------------------------------------------------------------->
 - Developer(s): --------------- for fun ------
 - Made By: full fixed for TC 62 version
 - Complete: 100%
 - ScriptName: 'Buff Command'
 - Comment: Tested & Working fine
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"
#include "Chat.h"
 
 
uint32 auras[] = { 23735, 23736, 23737, 23738, 23766, 23767, 23768, 23769 };
 
class buffcommand : public CommandScript
{
public:
    buffcommand() : CommandScript("buffcommand") { }
 
    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> IngameCommandTable =
        {
            { "buff",           rbac::RBAC_PERM_COMMAND_BUFF,         true,  &HandleBuffCommand,                "" },
        };
       
        return IngameCommandTable;
    }
 
    static bool HandleBuffCommand(ChatHandler * handler, const char * args)
    {
        Player * pl = handler->GetSession()->GetPlayer();
       
        if (pl->InArena())
        {
            pl->GetSession()->SendNotification("No puedes hacer eso en arenas, tramposo");
            return false;
        }
       
        pl->RemoveAurasByType(SPELL_AURA_MOUNTED);
       
        for (int i = 0; i < 7; i++)
            pl->AddAura(auras[i], pl);
       
        handler->PSendSysMessage("|cffB400B4El poder en ti a aumentado");
        return true;
    }
};
 
void AddSC_buffcommand()
{
    new buffcommand();
}