#pragma once

namespace Geometrics {
	Vector3 GetBonePosition(uintptr_t entity, int bone);
	bool WorldToScreen(Vector3 pos, Vector2& screen, float viewMatrix[16]);
	Vector3 TransformVector(Vector3 src, Vector3 ang, float d);
}