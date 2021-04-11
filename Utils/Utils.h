#pragma once

struct Vector2 {
    float x, y;
};

struct Vector3 {
    float x, y, z;
};

struct Vector4 {
    float x, y, z, w;
};

bool IsEntityMoving(uintptr_t entity);
bool IsEntityFlashed(uintptr_t entity);
bool IsEntityValid(uintptr_t entity);
bool IsClientInGame();

float GetDistance(uintptr_t originEntity, uintptr_t destinationEntity);

int GetWeaponID(uintptr_t entity);
int GetClassID(uintptr_t entity);
int GetEntityTeam(uintptr_t entity);
int GetEntityHealth(uintptr_t entity);

Vector3 GetEntityVelocity(uintptr_t entity);