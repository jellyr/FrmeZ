#include "../Header/Includes.h"

EndScene oEndScene;

HRESULT APIENTRY Hooked_EndScene(LPDIRECT3DDEVICE9 pDevice) {
	static bool init = false;

	if (!init) {
		init = true;
		CreateFontB(pDevice, "Times New Roman");
	}

	DrawMenu(pDevice);

	if (IsClientInGame()) {
		ESP::Esp(pDevice);
		ESP::RecoilCrosshair(pDevice);
		ESP::Hitmarker(pDevice);
	}

	return oEndScene(pDevice);
}