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

struct module_t
{
	DWORD64 modBaseAddr, hModule, modBaseSize;
};
struct color_t
{
	BYTE r, g, b, a;

	color_t(float r_, float g_, float b_, float a_) {
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}

};

namespace g {
	extern uintptr_t world_ptr;
	extern HANDLE process_handle;
	extern uintptr_t pid;
	extern module_t base_address;
	extern uint64_t hModule;
	extern uint64_t modBaseSize;
	extern bool is_steam_version;
	extern MODULEENTRY32 module_entry;
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
	namespace vehicle_mods 
	{
		extern bool seatbelt;
		extern float traction_min_curve;
		extern float traction_max_curve;
		extern float acceleration_force;
		extern float brake_force;
		extern float vehicle_mass;
		extern float buoyancy;
		extern float deform_multiplier;
		extern bool update_vehicle_mods;
		extern bool vehicle_godmode;
		extern bool update_car_color;
		extern color_t primary_car_color;
		extern color_t secondary_car_color;
		extern color_t car_wheel_color;
	}
	namespace weapon_replacers
	{
		extern bool replace_pistol;
		extern bool replace_combat_pistol;
		extern bool replace_bat;
		extern bool replace_knife;
	}
	namespace esp
	{
		extern bool draw_custom_hash;
		extern bool draw_esp;
		extern bool draw_skeleton;
		extern bool draw_distance;
		extern bool draw_name;
		extern bool draw_weapon;
		extern bool draw_box;
		extern bool draw_local_player;
		extern bool draw_npcs;
		extern bool draw_drugs;
		extern bool draw_waypoint;
		extern float npc_render_distance;
		extern float player_render_distance;
	}
	namespace player
	{
		extern float run_speed_amount;
		extern float swim_speed_amount;
		extern bool enable_aimbot;
		extern bool invisible_player;
		extern bool player_godmode;
		extern bool semi_godmode;
		extern bool teleport_to_waypoint;
	}
	namespace weapon
	{
		extern float damage_multiplier;
		extern float reload_speed;
		extern float bullet_mass;
		extern float bullet_damage;
		extern float muzzle_velocity;
		extern float weapon_range;
		extern float penetration_amount;
		extern bool infinite_ammo;
		extern bool no_reload;
		extern bool no_recoil;
		extern bool no_spread;
		extern bool explosive_ammo;
		extern bool explosive_meelee;
		extern bool fire_ammo;
		extern bool super_jump;
		extern bool draw_crosshair;
	}
	namespace menu
	{
		extern float menu_x;
		extern float menu_y;
		extern float menu_alpha;
	}
}