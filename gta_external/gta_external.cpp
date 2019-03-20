#include "overlay/overlay.hpp"
#include "esp/esp.hpp"
#include "menu/menu.hpp"

HANDLE g::process_handle;
uintptr_t g::pid;
uintptr_t g::base_address;
bool g::is_steam_version;
bool g::key_pressed[256] = {};
float g::menu_x = 20;
float g::menu_y = 200;

c_menu_framework* menu_framework = new c_menu_framework;


namespace vars
{
	bool draw_esp = false;
	bool draw_skeleton = false;
	bool draw_name = false;
	bool draw_box = false;
	bool draw_local_player = false;

	bool draw_npcs = false;
	bool vehicle_godmode = false;
	bool player_godmode = false;
	bool semi_godmode = false;

	bool explosive_ammo = false;
	bool explosive_meelee = false;
	bool fire_ammo = false;
	bool super_jump = false;
}

namespace d3d9 {
	 int screen_width;
	 int screen_height;

	 LPDIRECT3DDEVICE9 dx9_device;
	 LPD3DXFONT tahoma_13 = 0;
	 HWND game_window;
	 HWND overlay_hwnd;
	 RECT window_rect;
	 ID3DXLine* dx9_line;
	 MARGINS margin = { -1 };
}

namespace gta_external
{
	void render()
	{
		d3d9::dx9_device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
		d3d9::dx9_device->BeginScene();
		DWORD old_fvf;
		d3d9::dx9_device->GetFVF(&old_fvf);
		d3d9::dx9_device->SetFVF(D3_DFVF_CUSTOMVERTEX);
		d3d9::dx9_device->SetTexture(0, nullptr);

		menu_framework->draw();
		menu_framework->do_menu_controls();

		c_esp().draw_esp();

		d3d9::dx9_device->SetFVF(old_fvf);
		d3d9::dx9_device->EndScene();
		d3d9::dx9_device->Present(nullptr, nullptr, nullptr, nullptr);
	}
}