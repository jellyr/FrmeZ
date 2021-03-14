#include "../Header/Includes.h"

int knifes[] = { 41, 42, 59, 74, 500, 503, 505, 506, 507, 508, 509, 512, 514, 515, 516, 517, 518, 519, 520, 521, 522, 523, 525 };

void Knifebot(uintptr_t gameModule, uintptr_t localPlayer) {
	int crosshairID = *(int*)(localPlayer + m_iCrosshairId);
	if ((crosshairID == 0) || (crosshairID >= 64)) {
		return;
	}
	uintptr_t entity = *(uintptr_t*)(gameModule + dwEntityList + ((crosshairID - 1) * 0x10));
	int localPlayerTeam = GetEntityTeam(localPlayer);
	int entityTeam = GetEntityTeam(entity);
	int entityHealth = GetEntityHealth(entity);
	if (entityTeam == localPlayerTeam) {
		return;
	}
	if (entityHealth <= 0) {
		return;
	}
	if (IsEntityFlashed(localPlayer)) {
		return;
	}
	if (std::find(knifes, knifes + (sizeof(knifes) / sizeof(knifes[0])), GetWeaponID(gameModule, localPlayer)) == std::end(knifes)) {
		return;
	}
	if (GetDistance(localPlayer, entity) >= 1.60f) {
		return;
	}
	if (entityHealth < 55) {
		Shoot2(gameModule);
	} else {
		Shoot(gameModule);
	}
}