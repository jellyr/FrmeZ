#include "../Header/Includes.h"

IBaseClientDLL* BaseClientDLL = (IBaseClientDLL*)GetInterface("client.dll", "VClient018");
ClientClass* clientClass = BaseClientDLL->GetAllClasses();

uintptr_t m_fFlags = GetNetVarOffset("DT_CSPlayer", "m_fFlags", clientClass);
uintptr_t m_vecOrigin = GetNetVarOffset("DT_BasePlayer", "m_vecOrigin", clientClass);
uintptr_t m_vecVelocity = GetNetVarOffset("DT_CSPlayer", "m_vecVelocity", clientClass);
uintptr_t m_hActiveWeapon = GetNetVarOffset("DT_BasePlayer", "m_hActiveWeapon", clientClass);
uintptr_t m_flFlashDuration = GetNetVarOffset("DT_CSPlayer", "m_flFlashDuration", clientClass);
uintptr_t m_iItemDefinitionIndex = GetNetVarOffset("DT_BaseCombatWeapon", "m_iItemDefinitionIndex", clientClass);
uintptr_t m_iHealth = GetNetVarOffset("DT_BasePlayer", "m_iHealth", clientClass);
uintptr_t m_iTeamNum = GetNetVarOffset("DT_CSPlayer", "m_iTeamNum", clientClass);
uintptr_t m_iCrosshairId = GetNetVarOffset("DT_CSPlayer", "m_bHasDefuser", clientClass, 0x5C);
uintptr_t m_totalHitsOnServer = GetNetVarOffset("DT_CSPlayer", "m_totalHitsOnServer", clientClass);