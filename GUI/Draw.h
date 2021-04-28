#pragma once

extern bool box2D;
extern bool snaplines;
extern bool recoilCrosshair;
extern bool hitmarker;

void SolidRect(float x, float y, float w, float h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
void BorderedRect(float x, float y, float w, float h, float thiccness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
void CreateFontB(LPDIRECT3DDEVICE9 pDevice, std::string choiceFont);
void WriteText(LPD3DXFONT Font, LPCSTR Text, float x, float y, float w, float h, DWORD Format, D3DCOLOR color);
bool CheckBox(LPD3DXFONT Font, float x, float y, bool var, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse);
float Slider(LPD3DXFONT Font, float x, float y, float var, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse);
bool Button(LPD3DXFONT Font, float x, float y, std::string Name, LPDIRECT3DDEVICE9 pDevice, POINT Mouse);

void DrawLine(float x1, float y1, float x2, float y2, float thickness, LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color);
void DrawEspBox2D(float x1, float y1, float x2, float y2, float thickness, LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color);
void DrawHitmarker(LPDIRECT3DDEVICE9 pDevice);

void DrawMenu(LPDIRECT3DDEVICE9 pDevice);