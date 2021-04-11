#pragma once

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")

#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <Psapi.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include "../Utils/Patternscanning.h"
#include "../Utils/NetvarManager.h"
#include "../Utils/Utils.h"
#include "../Utils/Offsets.h"
#include "../Utils/D3D9Device.h"
#include "../Utils/TrampHook.h"
#include "../Utils/Hooks.h"
#include "../Utils/Geometrics.h"
#include "../Features/ESP.h"
#include "../GUI/Draw.h"

#define ABS(x) ((x < 0) ? (-x) : (x))
#define TORAD(x) ((x) * 0.01745329252)

#define KEY_DOWN -32768
#define KEY_UP 0

#define TITLEFONTSIZE 30
#define MENUFONTSIZE 15
#define DRAWFONTSIZE 15

#define W_USP 262205
#define W_GLOCK 4
#define W_DEAGLE 1
#define W_FIVESEVEN 3
#define W_P2000 32
#define W_P250 36
#define W_TEC9 30
#define W_CZAUTO 63
#define W_ELITE 2
#define W_REVOLVER 64
#define W_MP9 34
#define W_MAC10 17
#define W_MP7 33
#define W_MP5SD 23
#define W_UMP45 24
#define W_P90 19
#define W_PPBIZON 26
#define W_SG553 39
#define W_AUG 8
#define W_M4A4 16
#define W_GALIL 13
#define W_FAMAS 10
#define W_M4A1S 262204
#define W_AK47 7
#define W_SCOUT 40
#define W_AWP 9
#define W_SCAR20 38
#define W_G38G1 11
#define W_NOVA 35
#define W_XM1014 25
#define W_SAWEDOFF 29
#define W_MAG7 27
#define W_M249 14
#define W_NEGEV 28
#define W_TASER 31

#define MENUBORDERLONG 704
#define MENUBORDERSHORT 354
#define MENULONG 700
#define MENUSHORT 350
#define MARGIN 2
#define CHECKBOXBORDERRECT 14
#define CHECKBOXRECT 10
#define SLIDERBORDERLONG 54
#define SLIDERBORDERSHORT 14
#define SLIDERLONG 50
#define SLIDERSHORT 10
#define BUTTONBORDERLONG 42
#define BUTTONBORDERSHORT 14
#define BUTTONLONG 38
#define BUTTONSHORT 10