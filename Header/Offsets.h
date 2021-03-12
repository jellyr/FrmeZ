#pragma once

#include "Includes.h"

uintptr_t dwLocalPlayer;

uintptr_t lPlayer = LOCALPLAYER;

void GetOffsets(uintptr_t gameModule) {
	std::cout << "getting lp" << std::endl;
	dwLocalPlayer = (FindPattern("client.dll", "8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF") + 0x7);
	std::cout << std::to_string(dwLocalPlayer) << std::endl;
	std::cout << std::to_string(lPlayer) << std::endl; 
	std::cout << std::to_string(gameModule + lPlayer) << std::endl;
}