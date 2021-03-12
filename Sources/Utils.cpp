#include "../Header/Includes.h"
//#include "../Header/Offsets.h"

bool IsEntityMoving(uintptr_t entity) {
    Vector3 pVel = *(Vector3*)(entity + VELOCITY);
    float pMoving = pVel.x + pVel.y + pVel.z;
    if (pMoving != 0.0f) {
        return true;
    }
    return false;
}

bool IsEntityFlashed(uintptr_t entity)
{
    float flashDur = *(float*)(entity + FLASHDURATION);
    if (flashDur >= 2.5f) {
        return true;
    }
    return false;
}

float GetDistance(uintptr_t originEntity, uintptr_t destinationEntity) {
    Vector3 myLoc = *(Vector3*)(originEntity + ORIGIN);
    Vector3 oppLoc = *(Vector3*)(destinationEntity + ORIGIN);
    return sqrt(pow(myLoc.x - oppLoc.x, 2) + pow(myLoc.y - oppLoc.y, 2) + pow(myLoc.z - oppLoc.z, 2)) * 0.0254f;
}

int GetWeaponID(uintptr_t gameModule, uintptr_t entity)
{
    int weaponID = *(int*)(entity + ACTIVEWEAPON);
    int weaponEntity = *(int*)(gameModule + ENTITYLIST + ((weaponID & 0xFFF) - 1) * 0x10);
    if (weaponEntity != NULL) {
        return *(int*)(weaponEntity + ITEMDEFINITIONINDEX);
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
    return *(int*)(entity + TEAMNUM);
}

int GetEntityHealth(uintptr_t entity) {
    return *(int*)(entity + HEALTH);
}

void Shoot(uintptr_t gameModule) {
    Sleep(20);
    *(int*)(gameModule + FORCEATTACK) = 5;
    Sleep(20);
    *(int*)(gameModule + FORCEATTACK) = 4;
}

uintptr_t GetLocalPlayer(uintptr_t gameModule) {
    return *(uintptr_t*)(gameModule + LOCALPLAYER);
}