#include "../Header/Includes.h"

int hitShots = 0;

void Hitmarker(HMODULE hModule, uintptr_t localPlayer) {
    int totalHitShots = *(int*)(localPlayer + m_totalHitsOnServer);
    if (totalHitShots > hitShots) {
        PlaySound("hitmarker", hModule, SND_RESOURCE | SND_ASYNC);
        hitShots = totalHitShots;
    }
    if (totalHitShots == 0) {
        hitShots = 0;
    }
}