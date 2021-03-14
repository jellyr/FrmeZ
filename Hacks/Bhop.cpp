#include "../Header/Includes.h"

void Bhop(uintptr_t gameModule, uintptr_t localPlayer) {
    uintptr_t flags = *(BYTE*)(localPlayer + m_fFlags);
    if ((GetAsyncKeyState(VK_SPACE)) && (flags & (1 << 0)) && (IsEntityMoving(localPlayer))) {
        *(uintptr_t*)(gameModule + dwForceJump) = 6;
    }
}