#include "../Header/Includes.h"

bool IsEntityMoving(uintptr_t entity) {
    Vector3 vel = *(Vector3*)(entity + m_vecVelocity);
    float pMoving = vel.x + vel.y + vel.z;
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

bool IsEntityValid(uintptr_t entity) {
    if (entity == NULL) {
        return false;
    }
    if (entity == ESP::Variables::localPlayer) {
        return false;
    }
    if (GetEntityHealth(entity) <= 0) {
        return false;
    }
    if (*(bool*)(entity + m_bDormant)) {
        return false;
    }
    return true;
}

bool IsClientInGame() {
    return (*(int*)(*(uintptr_t*)(engineModule + dwClientState) + dwClientState_State) == 6);
}

float GetDistance(uintptr_t originEntity, uintptr_t destinationEntity) {
    Vector3 myLoc = *(Vector3*)(originEntity + m_vecOrigin);
    Vector3 oppLoc = *(Vector3*)(destinationEntity + m_vecOrigin);
    return (float)(sqrt(pow(myLoc.x - oppLoc.x, 2) + pow(myLoc.y - oppLoc.y, 2) + pow(myLoc.z - oppLoc.z, 2)) * 0.0254f);
}

int GetWeaponID(uintptr_t entity) {
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

Vector3 GetEntityVelocity(uintptr_t entity) {
    return *(Vector3*)(entity + m_vecVelocity);
}