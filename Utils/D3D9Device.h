#pragma once

extern int windowWidth, windowHeight;

static HWND window;

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);

HWND GetProcessWindow();

bool GetD3D9Device(void** pTable, size_t Size);