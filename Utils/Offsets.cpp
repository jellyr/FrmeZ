#include "../Header/Includes.h"

uintptr_t gameModule = (uintptr_t)GetModuleHandle("client.dll");
uintptr_t engineModule = (uintptr_t)GetModuleHandle("engine.dll");
uintptr_t shaderModule = (uintptr_t)GetModuleHandle("shaderapidx9.dll");

IBaseClientDLL* BaseClientDLL = (IBaseClientDLL*)GetInterface("client.dll", "VClient018");
ClientClass* clientClass = BaseClientDLL->GetAllClasses();

uintptr_t m_vecOrigin = GetNetVarOffset("DT_BasePlayer", "m_vecOrigin", clientClass);
uintptr_t m_vecVelocity = GetNetVarOffset("DT_CSPlayer", "m_vecVelocity", clientClass);
uintptr_t m_aimPunchAngle = GetNetVarOffset("DT_BasePlayer", "m_aimPunchAngle", clientClass);
uintptr_t m_hActiveWeapon = GetNetVarOffset("DT_BasePlayer", "m_hActiveWeapon", clientClass);
uintptr_t m_iItemDefinitionIndex = GetNetVarOffset("DT_BaseCombatWeapon", "m_iItemDefinitionIndex", clientClass);
uintptr_t m_flFlashDuration = GetNetVarOffset("DT_CSPlayer", "m_flFlashDuration", clientClass);
uintptr_t m_iHealth = GetNetVarOffset("DT_BasePlayer", "m_iHealth", clientClass);
uintptr_t m_iTeamNum = GetNetVarOffset("DT_CSPlayer", "m_iTeamNum", clientClass);
uintptr_t m_totalHitsOnServer = GetNetVarOffset("DT_CSPlayer", "m_totalHitsOnServer", clientClass);
uintptr_t m_dwBoneMatrix = GetNetVarOffset("DT_BaseAnimating", "m_nForceBone", clientClass, 0x1C);

uintptr_t dwLocalPlayer = FindPattern("client.dll", "8D 34 85 ?? ?? ?? ?? 89 15 ?? ?? ?? ?? 8B 41 08 8B 48 04 83 F9 FF", true, 0x3, 0x4);
uintptr_t m_bDormant = FindPattern("client.dll", "8A 81 ?? ?? ?? ?? C3 32 C0", false, 0x2, 0x8);
uintptr_t dwEntityList = FindPattern("client.dll", "BB ?? ?? ?? ?? 83 FF 01 0F 8C ?? ?? ?? ?? 3B F8", true, 0x1);
uintptr_t dwViewMatrix = FindPattern("client.dll", "0F 10 05 ?? ?? ?? ?? 8D 85 ?? ?? ?? ?? B9", true, 0x3, 0xB0);
uintptr_t dwClientState = FindPattern("engine.dll", "A1 ?? ?? ?? ?? 33 D2 6A 00 6A 00 33 C9 89 B0", true, 0x1);
uintptr_t dwClientState_State = FindPattern("engine.dll", "83 B8 ?? ?? ?? ?? ?? 0F 94 C0 C3", false, 0x2);
uintptr_t dwppDirect3DDevice9 = FindPattern("shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C", true, 0x1);