#include "../Header/Includes.h"

EndScene oEndScene;
ID3DXFont* Font;
uintptr_t DirectXDevice = NULL;

D3DCOLOR MenuBackgroundColor = D3DCOLOR_ARGB(255, 50, 50, 50);
D3DCOLOR MenuHighLightedColor = D3DCOLOR_ARGB(255, 90, 90, 90);
D3DCOLOR MenuBorderColor = D3DCOLOR_ARGB(255, 180, 0, 0);
D3DCOLOR TextColor = D3DCOLOR_ARGB(255, 255, 255, 255);
D3DCOLOR White = D3DCOLOR_ARGB(255, 255, 255, 255);
D3DCOLOR Black = D3DCOLOR_ARGB(255, 0, 0, 0);

bool showMenu = true;
bool bhop = false;
bool hitmarker = false;
bool autotaser = false;
bool knifebot = false;
int MenuX = 500;
int MenuY = 500;

void SolidRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice) {
	D3DRECT rect = { x, y, x + w, y + h };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0.0f, 0);
}

void BorderedRect(int x, int y, int w, int h, int thiccness, D3DCOLOR color, IDirect3DDevice9* pDevice) {
	SolidRect(x, y, w, thiccness, color, pDevice);
	SolidRect(x, y, thiccness, h, color, pDevice);
	SolidRect(x + (w - thiccness), y, thiccness, h, color, pDevice);
	SolidRect(x, y + (h - thiccness), w, thiccness, color, pDevice);
}

void CreateFontB(IDirect3DDevice9* pDevice, int size, std::string choiceFont) {
	D3DXCreateFontA(pDevice, size, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, choiceFont.c_str(), &Font);
}

void WriteText(LPCSTR Text, int x, int y, int w, int h, D3DCOLOR color) {
	RECT rect = { x, y, x + w, y + h };
	Font->DrawTextA(NULL, Text, -1, &rect, DT_CENTER, color);
}

bool CheckBox(int x, int y, bool var, std::string Name, IDirect3DDevice9* pDevice, POINT Mouse) {
	BorderedRect(x, y, 10, 10, 1, White, pDevice);
	if (Mouse.x >= x && Mouse.x <= x + 111 && Mouse.y >= y && Mouse.y <= y + 10) {
		SolidRect(x + 1, y + 1, 8, 8, MenuHighLightedColor, pDevice);
		if (GetAsyncKeyState(VK_LBUTTON) & 1) {
			var = !var;
			return var;
		}
	}

	if (var) {
		SolidRect(x + 1, y + 1, 8, 8, White, pDevice);
	}
	WriteText(Name.c_str(), x + 11, y, 100, 14, White);

	return var;
}

void DrawMenu(IDirect3DDevice9* pDevice) {
	static POINT Mouse;
	GetCursorPos(&Mouse);

	if (Mouse.x >= MenuX - 2 && Mouse.x <= MenuX + 204 && Mouse.y >= MenuY - 20 && Mouse.y <= MenuY) {
		if (GetAsyncKeyState(VK_LBUTTON)) {
			MenuX = Mouse.x - 100;
			MenuY = Mouse.y + 10;
		}
	}

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		showMenu = !showMenu;
	}

	if (showMenu) {
		SolidRect(MenuX, MenuY, 200, 200, MenuBackgroundColor, pDevice);
		SolidRect(MenuX - 2, MenuY - 20, 204, 20, MenuBorderColor, pDevice);
		BorderedRect(MenuX - 2, MenuY - 2, 204, 204, 2, MenuBorderColor, pDevice);
		WriteText("FrmeZ", MenuX, MenuY - 17, 200, 14, Black);

		bhop = CheckBox(MenuX + 5, MenuY + 5, bhop, "Bhop", pDevice, Mouse);
		hitmarker = CheckBox(MenuX + 5, MenuY + 20, hitmarker, "Hitmarker", pDevice, Mouse);
		autotaser = CheckBox(MenuX + 5, MenuY + 35, autotaser, "Auto Taser", pDevice, Mouse);
		knifebot = CheckBox(MenuX + 5, MenuY + 50, knifebot, "Knifebot", pDevice, Mouse);
	}
}

HRESULT __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice) {
	static bool init = false;

	if (!init) {
		init = true;
		CreateFontB(pDevice, 14, "Times New Roman");
	}

	DrawMenu(pDevice);
	return oEndScene(pDevice);
}