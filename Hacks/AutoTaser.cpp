#include "../Header/Includes.h"

void AutoTaser(uintptr_t gameModule, uintptr_t localPlayer) {
	int crosshairID = *(int*)(localPlayer + CROSSHAIRID);
	if ((crosshairID == 0) || (crosshairID >= 64)) {
		return;
	}
	uintptr_t entity = *(uintptr_t*)(gameModule + ENTITYLIST + ((crosshairID - 1) * 0x10));
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
	if (GetDistance(localPlayer, entity) >= 3.5f) {
		return;
	}
	if (GetWeaponID(gameModule, localPlayer) != W_TASER) {
		return;
	}
	Shoot(gameModule);
}