#include "Header/Includes.h"

DWORD WINAPI MoveMint(HMODULE hModule) {
    while (!DirectXDevice) {
        DirectXDevice = *(uintptr_t*)(shaderModule + dwppDirect3DDevice9);
    }

    void** pVTable = *reinterpret_cast<void***>(DirectXDevice);
    oEndScene = (EndScene)DetourFunction((PBYTE)pVTable[42], (PBYTE)Hooked_EndScene);

    while (!(GetAsyncKeyState(VK_END))) {
        uintptr_t localPlayer = *(uintptr_t*)(gameModule + dwLocalPlayer);

        if (bhop) Bhop(gameModule, localPlayer);
        if (hitmarker) Hitmarker(hModule, localPlayer);
        if (autotaser) AutoTaser(gameModule, localPlayer);
        if (knifebot) Knifebot(gameModule, localPlayer);

        Sleep(1);
    }

    FreeConsole();
    MessageBox(NULL, "Successfully un-injected", "FrmeZ", NULL);
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            AllocConsole();
            freopen("CONOUT$", "w", stdout);
            DisableThreadLibraryCalls(hModule);
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MoveMint, hModule, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}