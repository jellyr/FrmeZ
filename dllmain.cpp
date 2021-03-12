#include "Header/Includes.h"
#include "Header/Offsets.h"

DWORD WINAPI MoveMint(HMODULE hModule) {
    uintptr_t gameModule = (DWORD)GetModuleHandle("client.dll");
    static DWORD DirectXDevice = NULL;

    while (!DirectXDevice) {
        DirectXDevice = **(DWORD**)(FindPattern("shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C") + 0x1);
    }

    void** pVTable = *reinterpret_cast<void***>(DirectXDevice);
    oEndScene = (EndScene)DetourFunction((PBYTE)pVTable[42], (PBYTE)Hooked_EndScene);
    
    GetOffsets(gameModule);

    while (!(GetAsyncKeyState(VK_END))) {
        uintptr_t localPlayer = GetLocalPlayer(gameModule);

        if (bhop) Bhop(gameModule, localPlayer);
        if (hitmarker) Hitmarker(hModule, localPlayer);
        if (autotaser) AutoTaser(gameModule, localPlayer);

        Sleep(1);
    }

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