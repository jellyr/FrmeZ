#include "Header/Includes.h"

DWORD WINAPI MoveMint(HMODULE hModule) {
    static void* d3d9Device[119];
    static BYTE EndSceneBytes[7]{ 0 };
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device))) {
        memcpy(EndSceneBytes, (char*)d3d9Device[42], 7);
        oEndScene = (EndScene)TrampHook((char*)d3d9Device[42], (char*)Hooked_EndScene, 7);
    }

    while (!(GetAsyncKeyState(VK_END))) {
        if (IsClientInGame()) {
            ESP::Update();
        }
        Sleep(1);
    }

    Patch((BYTE*)d3d9Device[42], EndSceneBytes, 7);
    Sleep(1000);
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            //AllocConsole();
            //freopen("CONOUT$", "w", stdout);
            DisableThreadLibraryCalls(hModule);
            CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MoveMint, hModule, 0, nullptr));
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}