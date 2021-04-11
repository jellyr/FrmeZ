#include "../Header/Includes.h"

LPD3DXFONT TitleFont;
LPD3DXFONT MenuFont;
LPD3DXFONT DrawFont;

D3DCOLOR MenuBackgroundColor = D3DCOLOR_ARGB(255, 50, 50, 50);
D3DCOLOR MenuHighLightedColor = D3DCOLOR_ARGB(255, 90, 90, 90);
D3DCOLOR MenuBorderColor = D3DCOLOR_ARGB(255, 180, 0, 0);
D3DCOLOR TextColor = D3DCOLOR_ARGB(255, 255, 255, 255);
D3DCOLOR White = D3DCOLOR_ARGB(255, 255, 255, 255);
D3DCOLOR Black = D3DCOLOR_ARGB(255, 0, 0, 0);
D3DCOLOR Red = D3DCOLOR_ARGB(255, 255, 0, 0);

bool showMenu = true;
bool esp = false;
bool box2D = false;
bool snaplines = false;
bool recoilCrosshair = false;
bool hitmarker = false;

int MenuX = 500;
int MenuY = 500;
int MenuTab = 0;

void SolidRect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice) {
	D3DRECT rect = { x, y, x + w, y + h };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0.0f, 0);
}

void BorderedRect(int x, int y, int w, int h, int thiccness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice) {
	SolidRect(x, y, w, thiccness, color, pDevice);
	SolidRect(x, y, thiccness, h, color, pDevice);
	SolidRect(x + (w - thiccness), y, thiccness, h, color, pDevice);
	SolidRect(x, y + (h - thiccness), w, thiccness, color, pDevice);
}

void CreateFontB(LPDIRECT3DDEVICE9 pDevice, std::string choiceFont) {
	D3DXCreateFontA(pDevice, TITLEFONTSIZE, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, choiceFont.c_str(), &TitleFont);
	D3DXCreateFontA(pDevice, MENUFONTSIZE, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, choiceFont.c_str(), &MenuFont);
	D3DXCreateFontA(pDevice, DRAWFONTSIZE, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, choiceFont.c_str(), &DrawFont);
}

void WriteText(LPD3DXFONT Font, LPCSTR Text, int x, int y, int w, int h, DWORD Format, D3DCOLOR color) {
	RECT rect = { x, y, x + w, y + h };
	Font->DrawTextA(NULL, Text, -1, &rect, Format | DT_NOCLIP, color);
}

bool CheckBox(LPD3DXFONT Font, int x, int y, bool var, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse) {
	BorderedRect(x, y, CHECKBOXBORDERRECT, CHECKBOXBORDERRECT, 1, White, pDevice);
	WriteText(Font, Name.c_str(), x + 19, y, 100, 15, DT_LEFT, White);
	if (Mouse.x >= x && Mouse.x <= x + CHECKBOXBORDERRECT && Mouse.y >= y && Mouse.y <= y + CHECKBOXBORDERRECT) {
		SolidRect(x + MARGIN, y + MARGIN, CHECKBOXRECT, CHECKBOXRECT, MenuHighLightedColor, pDevice);
		if (GetAsyncKeyState(VK_LBUTTON) & 1) {
			var = !var;
			return var;
		}
	}
	if (var) {
		SolidRect(x + MARGIN, y + MARGIN, CHECKBOXRECT, CHECKBOXRECT, Red, pDevice);
	}
	return var;
}

bool Button(LPD3DXFONT Font, int x, int y, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse) {
	BorderedRect(x, y, BUTTONBORDERLONG, BUTTONBORDERSHORT, 1, White, pDevice);
	WriteText(Font, Name.c_str(), x - (BUTTONLONG / 2), y, 100, 15, DT_CENTER, White);
	if (Mouse.x >= x && Mouse.x <= x + BUTTONLONG && Mouse.y >= y && Mouse.y <= y + BUTTONSHORT) {
		SolidRect(x + MARGIN, y + MARGIN, BUTTONLONG, BUTTONSHORT, MenuHighLightedColor, pDevice);
		if (GetAsyncKeyState(VK_LBUTTON) & 1) {
			return true;
		}
	}
	return false;
}

float Slider(LPD3DXFONT Font, int x, int y, float var, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse) {
	BorderedRect(x, y, SLIDERBORDERLONG, SLIDERBORDERSHORT, 1, White, pDevice);
	WriteText(Font, Name.c_str(), x + 59, y, 100, 15, DT_LEFT, White);
	if (Mouse.x >= x && Mouse.x <= x + SLIDERBORDERLONG && Mouse.y >= y && Mouse.y <= y + SLIDERBORDERSHORT) {
		SolidRect(x + MARGIN, y + MARGIN, SLIDERLONG, SLIDERSHORT, MenuHighLightedColor, pDevice);
		if (GetAsyncKeyState(VK_LBUTTON)) {
			var = max(0.0f, Mouse.x - x - (2 * MARGIN));
			SolidRect(x + MARGIN, y + MARGIN, (int)var, SLIDERSHORT, Red, pDevice);
			WriteText(Font, Name.c_str(), x + 50, y, 100, 15, DT_LEFT, White);
			return var;
		}
	}
	if (var != 0.0f) {
		SolidRect(x + MARGIN, y + MARGIN, (int)var, SLIDERSHORT, Red, pDevice);
	}
	return var;
}

void DrawLine(float x1, float y1, float x2, float y2, int thickness, LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color) {
	LPD3DXLINE lineL;
	D3DXCreateLine(pDevice, &lineL);
	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);
	lineL->SetWidth((float)thickness);
	lineL->Draw(Line, 2, color);
	lineL->Release();
}

void DrawEspBox2D(float x1, float y1, float x2, float y2, int thickness, LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color) {
	/*int height = (int)ABS(y1 - y2);

	Vector2 topLeft, topRight;
	topLeft.x = x1 - height / 4;
	topRight.x = x1 + height / 4;
	topLeft.y = topRight.y = y1;

	Vector2 bottomLeft, bottomRight;
	bottomLeft.x = x2 - height / 4;
	bottomRight.x = x2 + height / 4;
	bottomLeft.y = bottomRight.y = y2;

	DrawLine(topLeft.x, topLeft.y, topRight.x, topRight.y, thickness, pDevice, color);
	DrawLine(bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y, thickness, pDevice, color);
	DrawLine(topLeft.x, topLeft.y, bottomLeft.x, bottomLeft.y, thickness, pDevice, color);
	DrawLine(topRight.x, topRight.y, bottomRight.x, bottomRight.y, thickness, pDevice, color);*/
	DrawLine(x1, y1, x1 + x2, y1, thickness, pDevice, color);
	DrawLine(x1, y1 + y2, x1 + x2, y1 + y2, thickness, pDevice, color);
	DrawLine(x1, y1, x1, y1 + y2, thickness, pDevice, color);
	DrawLine(x1 + x2, y1, x1 + x2, y1 + y2, thickness, pDevice, color);
}

void DrawHitmarker() {

}

void DrawMenu(LPDIRECT3DDEVICE9 pDevice) {
	static POINT Mouse;
	static bool grab = false;
	GetCursorPos(&Mouse);

	if (Mouse.x >= MenuX - 2 && Mouse.x <= MenuX + MENUBORDERLONG && Mouse.y >= MenuY - 40 && Mouse.y <= MenuY) {
		if (GetAsyncKeyState(VK_LBUTTON) == KEY_DOWN) {
			grab = true;
		}
	}
	if ((grab) && (GetAsyncKeyState(VK_LBUTTON) == KEY_UP)) {
		grab = false;
	}
	if (grab) {
		MenuX = Mouse.x - 100;
		MenuY = Mouse.y + 10;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		showMenu = !showMenu;
	}

	if (showMenu) {
		SolidRect(MenuX, MenuY, MENULONG, MENUSHORT, MenuBackgroundColor, pDevice);
		SolidRect(MenuX - 2, MenuY - 40, MENUBORDERLONG, 40, MenuBorderColor, pDevice);
		BorderedRect(MenuX - 2, MenuY - 2, MENUBORDERLONG, MENUBORDERSHORT, 2, MenuBorderColor, pDevice);
		WriteText(TitleFont, "FrmeZ - ESP", MenuX, MenuY - 35, MENULONG, 25, DT_CENTER, Black);

		esp = CheckBox(MenuFont, MenuX + 5, MenuY + 5, esp, "ESP", pDevice, Mouse);
		box2D = CheckBox(MenuFont, MenuX + 15, MenuY + 25, box2D, "2D Box", pDevice, Mouse);
		snaplines = CheckBox(MenuFont, MenuX + 15, MenuY + 45, snaplines, "Snaplines", pDevice, Mouse);

		recoilCrosshair = CheckBox(MenuFont, MenuX + 5, MenuY + 85, recoilCrosshair, "Recoil Crosshair", pDevice, Mouse);
		hitmarker = CheckBox(MenuFont, MenuX + 5, MenuY + 105, hitmarker, "Hitmarker", pDevice, Mouse);
	}
}