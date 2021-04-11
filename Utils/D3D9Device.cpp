#include "../Header/Includes.h"

IDirect3D9* pD3D = NULL;
LPDIRECT3DDEVICE9 pDummyDevice = NULL;

int windowWidth, windowHeight;

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam) {
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);
	if (GetCurrentProcessId() != wndProcId) {
		return TRUE; // skip to next window
	}
	window = handle;
	return FALSE; // window found abort search
}

HWND GetProcessWindow() {
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);

	RECT size;
	GetWindowRect(window, &size);
	windowWidth = size.right - size.left;
	windowHeight = size.bottom - size.top;

	return window;
}

bool GetD3D9Device(void** pTable, size_t Size) {
	if (!pTable) {
		return false;
	}
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D) {
		return false;
	}
	pDummyDevice = NULL;

	// options to create dummy device
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetProcessWindow();

	HRESULT dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

	if (dummyDeviceCreated != S_OK) {
		// may fail in windowed fullscreen mode, trying again with windowed mode
		d3dpp.Windowed = !d3dpp.Windowed;

		dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

		if (dummyDeviceCreated != S_OK) {
			pD3D->Release();
			return false;
		}
	}

	memcpy(pTable, *reinterpret_cast<void***>(pDummyDevice), Size);

	pDummyDevice->Release();
	pD3D->Release();
	return true;
}