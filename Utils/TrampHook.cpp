#include "../Header/Includes.h"

void Patch(BYTE* dst, BYTE* src, unsigned int size) {
	DWORD curProtection;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &curProtection);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, curProtection, &curProtection);
}

bool Hook(char* src, char* dst, int len) {
	if (len < 5) return false;
	DWORD curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);
	memset(src, 0x90, len);
	uintptr_t relativeAddress = (uintptr_t)(dst - src - 5);
	*src = (char)0xE9;
	*(uintptr_t*)(src + 1) = (uintptr_t)relativeAddress;
	DWORD temp;
	VirtualProtect(src, len, curProtection, &temp);
	return true;
}

char* TrampHook(char* src, char* dst, unsigned int len) {
	if (len < 5) return 0;
	char* gateway = (char*)VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(gateway, src, len);
	uintptr_t gateJmpAddy = (uintptr_t)(src - gateway - 5);
	*(gateway + len) = (char)0xE9;
	*(uintptr_t*)(gateway + len + 1) = gateJmpAddy;
	if (Hook(src, dst, len)) {
		return gateway;
	}
	else return nullptr;
}