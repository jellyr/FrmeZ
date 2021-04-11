#pragma once

extern bool esp;
extern bool box2D;
extern bool snaplines;
extern bool recoilCrosshair;
extern bool hitmarker;

void SolidRect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
void BorderedRect(int x, int y, int w, int h, int thiccness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
void CreateFontB(LPDIRECT3DDEVICE9 pDevice, std::string choiceFont);
void WriteText(LPD3DXFONT Font, LPCSTR Text, int x, int y, int w, int h, DWORD Format, D3DCOLOR color);
bool CheckBox(LPD3DXFONT Font, int x, int y, bool var, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse);
float Slider(LPD3DXFONT Font, int x, int y, float var, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse);
bool Button(LPD3DXFONT Font, int x, int y, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse);

void DrawLine(float x1, float y1, float x2, float y2, int thickness, LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color);
void DrawEspBox2D(float x1, float y1, float x2, float y2, int thickness, LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color);
void DrawHitmarker();

void DrawMenu(LPDIRECT3DDEVICE9 pDevice);