#include "../Header/Includes.h"

void ESP::Update() {
	ESP::Variables::localPlayer = *(uintptr_t*)(gameModule + dwLocalPlayer);
	ESP::Variables::angle = *(Vector3*)(ESP::Variables::localPlayer + m_aimPunchAngle);
	memcpy(&ESP::Variables::viewMatrix, (PBYTE*)(gameModule + dwViewMatrix), sizeof(ESP::Variables::viewMatrix));
	//ESP::Variables::viewMatrix[16] = *(float*)(gameModule + dwViewMatrix);
	ESP::Variables::totalHitShots = *(int*)(ESP::Variables::localPlayer + m_totalHitsOnServer);
}

void ESP::Esp(LPDIRECT3DDEVICE9 pDevice) {
	for (int i = 1; i < 32; i++) {
		uintptr_t entity = *(uintptr_t*)(gameModule + dwEntityList + (i * 0x10));
		if (!IsEntityValid(entity)) {
			continue;
		}
		Vector3 entityHead3D = Geometrics::GetBonePosition(entity, 8);
		entityHead3D.z += 10.0f;
		Vector2 entityPosition2D, entityHead2D;
		Vector3 entityLocation = *(Vector3*)(entity + m_vecOrigin);
		if (Geometrics::WorldToScreen(entityLocation, entityPosition2D, ESP::Variables::viewMatrix)) {
			if (snaplines) {
				DrawLine(entityPosition2D.x, entityPosition2D.y, (float)(windowWidth / 2), (float)windowHeight, 2.0f, pDevice, D3DCOLOR_ARGB(255, 0, 0, 255));
			}
			if (Geometrics::WorldToScreen(entityHead3D, entityHead2D, ESP::Variables::viewMatrix)) {
				if (box2D) {
					DrawEspBox2D(entityPosition2D.x, entityPosition2D.y, entityHead2D.x, entityHead2D.y, 2.0f, pDevice, D3DCOLOR_ARGB(255, 0, 255, 0));
				}
			}
		}
	}
}

void ESP::RecoilCrosshair(LPDIRECT3DDEVICE9 pDevice) {
	if (!recoilCrosshair) {
		return;
	}

	static Vector2 crosshair = { 0.0f, 0.0f };

	crosshair.x = (float)(windowWidth / 2 - (windowWidth / 90 * ESP::Variables::angle.y));
	crosshair.y = (float)(windowHeight / 2 + (windowHeight / 90 * ESP::Variables::angle.x));

	Vector2 left, right, top, bottom;
	left = right = top = bottom = crosshair;
	left.x -= 4.0f;
	right.x += 4.0f;
	top.y -= 4.0f;
	bottom.y += 4.0f;

	DrawLine(left.x, left.y, right.x, right.y, 2.0f, pDevice, D3DCOLOR_ARGB(255, 255, 0, 0));
	DrawLine(top.x, top.y, bottom.x, bottom.y, 2.0f, pDevice, D3DCOLOR_ARGB(255, 255, 0, 0));
}

void ESP::Hitmarker(LPDIRECT3DDEVICE9 pDevice) {
	if (!hitmarker) {
		return;
	}

	static int hitShots = 0;

	if (ESP::Variables::totalHitShots > hitShots) {
		PlaySoundA("hitmarker", handleModule, SND_RESOURCE | SND_ASYNC);
		DrawHitmarker(pDevice);
		hitShots = ESP::Variables::totalHitShots;
	}
	if (ESP::Variables::totalHitShots == 0) {
		hitShots = 0;
	}
}