#include "../Header/Includes.h"

DWORD FindPattern(std::string moduleName, std::string pattern, bool relative, int offset, int extra) {
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo;
	GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++) {
		if (!*pat) {
			if (relative) {
				return (*(uintptr_t*)(firstMatch + offset) + extra - rangeStart);
			}
			return (*(uintptr_t*)(firstMatch + offset) + extra);
		}
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
			if (!firstMatch) {
				firstMatch = pCur;
			}
			if (!pat[2]) {
				if (relative) {
					return (*(uintptr_t*)(firstMatch + offset) + extra - rangeStart);
				}
				return (*(uintptr_t*)(firstMatch + offset) + extra);
			}
			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') {
				pat += 3;
			} else {
				pat += 2;
			}
		} else {
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}
	return NULL;
}