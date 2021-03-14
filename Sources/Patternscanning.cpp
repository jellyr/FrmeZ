#include "../Header/Includes.h"

DWORD FindPattern(std::string moduleName, std::string pattern, int offset, int extra) {
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo;
	GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++) {
		if (!*pat) {
			return (*(uintptr_t*)(firstMatch + offset) + extra - rangeStart);
		}
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
			if (!firstMatch) {
				firstMatch = pCur;
			}
			if (!pat[2]) {
				return (*(uintptr_t*)(firstMatch + offset) + extra - rangeStart);
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