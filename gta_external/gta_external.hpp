#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <TlHelp32.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <type_traits>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")
#define D3_DFVF_CUSTOMVERTEX        ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

namespace g {
	extern HANDLE process_handle;
	extern uintptr_t pid;
	extern uintptr_t base_address;
	extern bool is_steam_version;
	extern bool key_pressed[256];
	extern float menu_x;
	extern float menu_y;
}

#include "utilities/utilities.hpp"
#include "memory/memory.hpp"
#include "sdk/sdk.hpp"

namespace gta_external {
	extern void render();
}

namespace d3d9 {
	extern int screen_width;
	extern int screen_height;

	extern HWND game_window;
	extern HWND overlay_hwnd;
	extern RECT window_rect;
	extern ID3DXLine* dx9_line;
	extern LPDIRECT3DDEVICE9 dx9_device;
	extern LPD3DXFONT tahoma_13;
	extern MARGINS margin;
}
#include "rendering/rendering.hpp"

namespace vars
{
	extern bool draw_esp;
	extern bool draw_skeleton;
	extern bool draw_name;
	extern bool draw_box;
	extern bool draw_local_player;

	extern bool draw_npcs;
	extern bool vehicle_godmode;
	extern bool player_godmode;
	extern bool semi_godmode;
	
	extern bool explosive_ammo;
	extern bool explosive_meelee;
	extern bool fire_ammo;
	extern bool super_jump;
}