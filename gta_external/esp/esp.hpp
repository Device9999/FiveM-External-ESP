#pragma once
#include "../gta_external.hpp"

class c_esp
{
public:

	D3DXVECTOR2 world_to_screen(D3DXVECTOR3 world_pos);

	bool get_bounding_box(D3DXVECTOR3 origin, D3DXVECTOR3 mins, D3DXVECTOR3 maxs, int & out_x, int & out_y, int & out_w, int & out_h);

	void draw_skeleton(uintptr_t ped_base);

	void draw_esp();

	void draw_object_esp(sdk::c_replay_interface replay_iface);

};