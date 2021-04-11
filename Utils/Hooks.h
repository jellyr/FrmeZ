#pragma once

typedef HRESULT(APIENTRY* EndScene)(LPDIRECT3DDEVICE9 pDevice);
extern EndScene oEndScene;

HRESULT APIENTRY Hooked_EndScene(LPDIRECT3DDEVICE9 pDevice);