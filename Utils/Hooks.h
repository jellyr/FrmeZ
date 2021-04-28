#pragma once

extern HMODULE handleModule;

typedef HRESULT(APIENTRY* EndScene)(LPDIRECT3DDEVICE9 pDevice);
extern EndScene oEndScene;

HRESULT APIENTRY Hooked_EndScene(LPDIRECT3DDEVICE9 pDevice);