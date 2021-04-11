#include "../Header/Includes.h"

Vector3 Geometrics::GetBonePosition(uintptr_t entity, int bone) {
	uintptr_t bonePtr = *(uintptr_t*)(entity + m_dwBoneMatrix);
	Vector3 bonePos;
	bonePos.x = *(float*)(bonePtr + 0x30 * bone + 0x0C);
	bonePos.y = *(float*)(bonePtr + 0x30 * bone + 0x1C);
	bonePos.z = *(float*)(bonePtr + 0x30 * bone + 0x2C);
	return bonePos;
}

bool Geometrics::WorldToScreen(Vector3 pos, Vector2& screen, float viewMatrix[16]) {
	Vector4 clipCoords;
	clipCoords.x = pos.x * viewMatrix[0] + pos.y * viewMatrix[1] + pos.z * viewMatrix[2] + viewMatrix[3];
	clipCoords.y = pos.x * viewMatrix[4] + pos.y * viewMatrix[5] + pos.z * viewMatrix[6] + viewMatrix[7];
	clipCoords.z = pos.x * viewMatrix[8] + pos.y * viewMatrix[9] + pos.z * viewMatrix[10] + viewMatrix[11];
	clipCoords.w = pos.x * viewMatrix[12] + pos.y * viewMatrix[13] + pos.z * viewMatrix[14] + viewMatrix[15];

	if (clipCoords.w < 0.1f) {
		return false;
	}

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

Vector3 Geometrics::TransformVector(Vector3 src, Vector3 ang, float d) {
	Vector3 newPos;
	newPos.x = src.x + (cosf((float)TORAD(ang.y)) * d);
	newPos.y = src.y + (sinf((float)TORAD(ang.y)) * d);
	newPos.z = src.z + (tanf((float)TORAD(ang.x)) * d);
	return newPos;
}