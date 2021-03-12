#include "../Header/Includes.h"

void Bhop(uintptr_t gameModule, uintptr_t localPlayer) {
    uintptr_t flags = *(BYTE*)(localPlayer + FLAGS);
    if ((GetAsyncKeyState(VK_SPACE)) && (flags & (1 << 0)) && (IsEntityMoving(localPlayer))) {
        *(uintptr_t*)(gameModule + FORCEJUMP) = 6;
    }
}