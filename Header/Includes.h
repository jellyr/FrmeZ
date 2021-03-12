#pragma once

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")

#include <Windows.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include "detours.h"
#include "Patternscanning.h"
#include "Utils.h"
#include "Hacks.h"
#include "Menu.h"

#define W_TASER 31

#define LOCALPLAYER 0xD8B2DC
#define ENTITYLIST 0x4DA2F24
#define FLAGS 0x104
#define FORCEJUMP 0x524CE84
#define TOTALHITSONSERVER 0xA3A8
#define VELOCITY 0x114
#define ORIGIN 0x138
#define ACTIVEWEAPON 0x2EF8
#define ITEMDEFINITIONINDEX 0x2FAA
#define FORCEATTACK 0x31D446C
#define FLASHDURATION 0xA420
#define CROSSHAIRID 0xB3E4
#define TEAMNUM 0xF4
#define HEALTH 0x100