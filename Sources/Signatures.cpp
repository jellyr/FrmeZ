#include "../Header/Includes.h"

uintptr_t gameModule = (DWORD)GetModuleHandle("client.dll");
uintptr_t shaderModule = (DWORD)GetModuleHandle("shaderapidx9.dll");

uintptr_t dwLocalPlayer = FindPattern("client.dll", "8D 34 85 ?? ?? ?? ?? 89 15 ?? ?? ?? ?? 8B 41 08 8B 48 04 83 F9 FF", 0x3, 0x4);
uintptr_t dwEntityList = FindPattern("client.dll", "BB ?? ?? ?? ?? 83 FF 01 0F 8C ?? ?? ?? ?? 3B F8", 0x1);
uintptr_t dwForceJump = FindPattern("client.dll", "8B 0D ?? ?? ?? ?? 8B D6 8B C1 83 CA 02", 0x2);
uintptr_t dwForceAttack = FindPattern("client.dll", "89 0D ?? ?? ?? ?? 8B 0D ?? ?? ?? ?? 8B F2 8B C1 83 CE 04", 0x2);
uintptr_t dwForceAttack2 = FindPattern("client.dll", "89 0D ?? ?? ?? ?? 8B 0D ?? ?? ?? ?? 8B F2 8B C1 83 CE 04", 0x2, 0xC);
uintptr_t dwppDirect3DDevice9 = FindPattern("shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C", 0x1);