#pragma once

namespace ESP {
	void Update();
	void Esp(LPDIRECT3DDEVICE9 pDevice);
	void RecoilCrosshair(LPDIRECT3DDEVICE9 pDevice);
	void Hitmarker(LPDIRECT3DDEVICE9 pDevice);
	namespace Variables {
		inline uintptr_t localPlayer;
		inline Vector3 angle;
		inline float viewMatrix[16];
		inline int totalHitShots;
	}
}