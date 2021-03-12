#pragma once

struct Vector3 {
    float x, y, z;
};

bool IsEntityMoving(uintptr_t entity);
bool IsEntityFlashed(uintptr_t entity);

float GetDistance(uintptr_t originEntity, uintptr_t destinationEntity);

int GetWeaponID(uintptr_t gameModule, uintptr_t entity);
int GetClassID(uintptr_t entity);
int GetEntityTeam(uintptr_t entity);
int GetEntityHealth(uintptr_t entity);

void Shoot(uintptr_t gameModule);

uintptr_t GetLocalPlayer(uintptr_t gameModule);