#pragma once

typedef HRESULT(__stdcall* EndScene)(IDirect3DDevice9* pDevice);
extern EndScene oEndScene;
extern uintptr_t DirectXDevice;

extern bool bhop;
extern bool hitmarker;
extern bool autotaser;
extern bool knifebot;

void SolidRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice);
void BorderedRect(int x, int y, int w, int h, int thiccness, D3DCOLOR color, IDirect3DDevice9* pDevice);
void CreateFontB(IDirect3DDevice9* pDevice, int size, std::string choiceFont);
void WriteText(LPCSTR Text, int x, int y, int w, int h, D3DCOLOR color);
bool CheckBox(int x, int y, bool var, std::string Name, IDirect3DDevice9* pDevice, POINT Mouse);
void DrawMenu(IDirect3DDevice9* pDevice);

HRESULT __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice);