#pragma once
#include "../gta_external.hpp"

namespace overlay {
	extern void directx_init(HWND hWnd);
	extern LRESULT CALLBACK wnd_proc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
	extern void set_overlay_position();
	extern void initialize();
}