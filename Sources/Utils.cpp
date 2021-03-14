#include "../Header/Includes.h"

bool IsEntityMoving(uintptr_t entity) {
    Vector3 pVel = *(Vector3*)(entity + m_vecVelocity);
    float pMoving = pVel.x + pVel.y + pVel.z;
    if (pMoving != 0.0f) {
        return true;
    }
    return false;
}

bool IsEntityFlashed(uintptr_t entity) {
    float flashDur = *(float*)(entity + m_flFlashDuration);
    if (flashDur >= 2.5f) {
        return true;
    }
    return false;
}

float GetDistance(uintptr_t originEntity, uintptr_t destinationEntity) {
    Vector3 myLoc = *(Vector3*)(originEntity + m_vecOrigin);
    Vector3 oppLoc = *(Vector3*)(destinationEntity + m_vecOrigin);
    return sqrt(pow(myLoc.x - oppLoc.x, 2) + pow(myLoc.y - oppLoc.y, 2) + pow(myLoc.z - oppLoc.z, 2)) * 0.0254f;
}

int GetWeaponID(uintptr_t gameModule, uintptr_t entity) {
    int weaponID = *(int*)(entity + m_hActiveWeapon);
    int weaponEntity = *(int*)(gameModule + dwEntityList + ((weaponID & 0xFFF) - 1) * 0x10);
    if (weaponEntity != NULL) {
        return *(int*)(weaponEntity + m_iItemDefinitionIndex);
    }
    return -1;
}

int GetClassID(uintptr_t entity) {
    uintptr_t dwClientNetworkable = *(uintptr_t*)(entity + 0x8);
    uintptr_t dwGetClientClassFn = *(uintptr_t*)(dwClientNetworkable + 2 * 0x4);
    uintptr_t dwEntityClientClass = *(uintptr_t*)(dwGetClientClassFn + 1);
    return *(int*)(dwEntityClientClass + 20);
}

int GetEntityTeam(uintptr_t entity) {
    return *(int*)(entity + m_iTeamNum);
}

int GetEntityHealth(uintptr_t entity) {
    return *(int*)(entity + m_iHealth);
}

void Shoot(uintptr_t gameModule) {
    Sleep(20);
    *(int*)(gameModule + dwForceAttack) = 5;
    Sleep(20);
    *(int*)(gameModule + dwForceAttack) = 4;
}

void Shoot2(uintptr_t gameModule) {
    Sleep(20);
    *(int*)(gameModule + dwForceAttack2) = 5;
    Sleep(20);
    *(int*)(gameModule + dwForceAttack2) = 4;
}

uintptr_t GetLocalPlayer(uintptr_t gameModule) {
    return *(uintptr_t*)(gameModule + dwLocalPlayer);
}