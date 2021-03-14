#pragma once

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")

#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <Psapi.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include "detours.h"
#include "Patternscanning.h"
#include "NetvarManager.h"
#include "Utils.h"
#include "Hacks.h"
#include "Menu.h"
#include "Signatures.h"
#include "Netvars.h"

#define W_TASER 31