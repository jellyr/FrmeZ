#include "../Header/Includes.h"

float MENU_X = 720.0f;
float MENU_Y = MENU_X * (2.0f / 3.0f);
float MARGIN = MENU_X * (1.0f / 144.0f);
float TITLEMARGIN = MENU_Y * (1.0f / 12.0f);
float CHECKBOXBORDERRECT = 14;
float CHECKBOXRECT = 10;
float SLIDERBORDERLONG = 54;
float SLIDERBORDERSHORT = 14;
float SLIDERLONG = 50;
float SLIDERSHORT = 10;
float BUTTONBORDERLONG = 42;
float BUTTONBORDERSHORT = 14;
float BUTTONLONG = 38;
float BUTTONSHORT = 10;

float posMenuX = 500.0f;
float posMenuY = 500.0f;
int MenuTab = 0;

LPD3DXFONT TitleFont;
LPD3DXFONT MenuFont;
LPD3DXFONT DrawFont;

D3DCOLOR MenuBackgroundColor = D3DCOLOR_ARGB(255, 50, 50, 50);
D3DCOLOR MenuHighLightedColor = D3DCOLOR_ARGB(255, 90, 90, 90);
D3DCOLOR TextColor = D3DCOLOR_ARGB(255, 255, 255, 255);
D3DCOLOR White = D3DCOLOR_ARGB(255, 255, 255, 255);
D3DCOLOR Black = D3DCOLOR_ARGB(255, 0, 0, 0);
D3DCOLOR Red = D3DCOLOR_ARGB(255, 255, 0, 0);

bool showMenu = true;
bool box2D = false;
bool snaplines = false;
bool recoilCrosshair = false;
bool hitmarker = false;

void SolidRect(float x, float y, float w, float h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice) {
	D3DRECT rect = { (LONG)x, (LONG)y, (LONG)x + (LONG)w, (LONG)y + (LONG)h };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0.0f, 0);
}

void BorderedRect(float x, float y, float w, float h, float thiccness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice) {
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

void WriteText(LPD3DXFONT Font, LPCSTR Text, float x, float y, float w, float h, DWORD Format, D3DCOLOR color) {
	RECT rect = { (LONG)x, (LONG)y, (LONG)x + (LONG)w, (LONG)y + (LONG)h };
	Font->DrawTextA(NULL, Text, -1, &rect, Format | DT_NOCLIP, color);
}

bool CheckBox(LPD3DXFONT Font, float x, float y, bool var, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse) {
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

bool Button(LPD3DXFONT Font, float x, float y, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse) {
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

float Slider(LPD3DXFONT Font, float x, float y, float var, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse) {
	BorderedRect(x, y, SLIDERBORDERLONG, SLIDERBORDERSHORT, 1, White, pDevice);
	WriteText(Font, Name.c_str(), x + 59, y, 100, 15, DT_LEFT, White);
	if (Mouse.x >= x && Mouse.x <= x + SLIDERBORDERLONG && Mouse.y >= y && Mouse.y <= y + SLIDERBORDERSHORT) {
		SolidRect(x + MARGIN, y + MARGIN, SLIDERLONG, SLIDERSHORT, MenuHighLightedColor, pDevice);
		if (GetAsyncKeyState(VK_LBUTTON)) {
			var = max(0.0f, Mouse.x - x - (2 * MARGIN));
			SolidRect(x + MARGIN, y + MARGIN, var, SLIDERSHORT, Red, pDevice);
			WriteText(Font, Name.c_str(), x + 50, y, 100, 15, DT_LEFT, White);
			return var;
		}
	}
	if (var != 0.0f) {
		SolidRect(x + MARGIN, y + MARGIN, var, SLIDERSHORT, Red, pDevice);
	}
	return var;
}

void DrawLine(float x1, float y1, float x2, float y2, float thickness, LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color) {
	LPD3DXLINE lineL;
	D3DXCreateLine(pDevice, &lineL);
	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);
	lineL->SetWidth((float)thickness);
	lineL->Draw(Line, 2, color);
	lineL->Release();
}

void DrawEspBox2D(float x1, float y1, float x2, float y2, float thickness, LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color) {
	float height = ABS(y1 - y2);

	Vector2 topLeft, topRight;
	topLeft.x = x1 - height / 4.0f;
	topRight.x = x1 + height / 4.0f;
	topLeft.y = topRight.y = y1;

	Vector2 bottomLeft, bottomRight;
	bottomLeft.x = x2 - height / 4.0f;
	bottomRight.x = x2 + height / 4.0f;
	bottomLeft.y = bottomRight.y = y2;

	DrawLine(topLeft.x, topLeft.y, topRight.x, topRight.y, thickness, pDevice, color);
	DrawLine(bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y, thickness, pDevice, color);
	DrawLine(topLeft.x, topLeft.y, bottomLeft.x, bottomLeft.y, thickness, pDevice, color);
	DrawLine(topRight.x, topRight.y, bottomRight.x, bottomRight.y, thickness, pDevice, color);
}

void DrawHitmarker(LPDIRECT3DDEVICE9 pDevice) {
	Vector2 crosshair = { (float)(windowWidth / 2), (float)(windowHeight / 2) };
	Vector2 left, right, top, bottom;
	left = right = top = bottom = crosshair;
	left.x -= 5;
	left.y -= 5;
	right.x += 5;
	right.y += 5;
	top.y -= 5;
	top.x += 5;
	bottom.y += 5;
	bottom.x -= 5;

	DrawLine(left.x, left.y, right.x, right.y, 2, pDevice, D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawLine(top.x, top.y, bottom.x, bottom.y, 2, pDevice, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void DrawMenu(LPDIRECT3DDEVICE9 pDevice) {
	static POINT Mouse;
	static bool grab = false;
	GetCursorPos(&Mouse);

	if (Mouse.x >= posMenuX && Mouse.x <= posMenuX + MENU_X && Mouse.y >= posMenuY && Mouse.y <= posMenuY + TITLEMARGIN) {
		if (GetAsyncKeyState(VK_LBUTTON) == KEY_DOWN) {
			grab = true;
		}
	}
	if (grab) {
		if (GetAsyncKeyState(VK_LBUTTON) == KEY_UP) {
			grab = false;
		}
		posMenuX = (float)Mouse.x;
		posMenuY = (float)Mouse.y;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		showMenu = !showMenu;
	}

	if (showMenu) {
		SolidRect(posMenuX, posMenuY, MENU_X, MENU_Y, MenuBackgroundColor, pDevice);
		SolidRect(posMenuX, posMenuY, MENU_X, TITLEMARGIN, Red, pDevice);
		BorderedRect(posMenuX, posMenuY, MENU_X, MENU_Y, 5.0f, Red, pDevice);
		WriteText(TitleFont, "FrmeZ - ESP", posMenuX, posMenuY, MENU_X, TITLEMARGIN, DT_CENTER, Black);

		box2D = CheckBox(MenuFont, posMenuX + (2 * MARGIN), posMenuY + TITLEMARGIN + MARGIN, box2D, "2D Box", pDevice, Mouse);
		//snaplines = CheckBox(MenuFont, posMenuX + (2 * MARGIN), posMenuY + 45, snaplines, "Snaplines", pDevice, Mouse);

		//recoilCrosshair = CheckBox(MenuFont, posMenuX + (2 * MARGIN), posMenuY + 85, recoilCrosshair, "Recoil Crosshair", pDevice, Mouse);
		//hitmarker = CheckBox(MenuFont, posMenuX + (2 * MARGIN), posMenuY + 105, hitmarker, "Hitmarker", pDevice, Mouse);
	}
}