#include "esp.hpp"
#include "../menu/menu.hpp"

D3DXVECTOR2 c_esp::world_to_screen(D3DXVECTOR3 world_pos) {
	static uintptr_t viewport = c_mem().read_mem<uintptr_t>(g::base_address + (g::is_steam_version ? (0x0208BAF0) : (0x02087780)));
	auto viewmatrix = c_mem().read_mem<D3DXMATRIX>(viewport + 0x24C);

	D3DXMatrixTranspose(&viewmatrix, &viewmatrix);
	auto vec_x = D3DXVECTOR4(viewmatrix._21, viewmatrix._22, viewmatrix._23, viewmatrix._24),
		 vec_y = D3DXVECTOR4(viewmatrix._31, viewmatrix._32, viewmatrix._33, viewmatrix._34),
		 vec_z = D3DXVECTOR4(viewmatrix._41, viewmatrix._42, viewmatrix._43, viewmatrix._44);

	auto screen_pos = D3DXVECTOR3((vec_x.x * world_pos.x) + (vec_x.y * world_pos.y) + (vec_x.z * world_pos.z) + vec_x.w,
		(vec_y.x * world_pos.x) + (vec_y.y * world_pos.y) + (vec_y.z * world_pos.z) + vec_y.w,
		(vec_z.x * world_pos.x) + (vec_z.y * world_pos.y) + (vec_z.z * world_pos.z) + vec_z.w);

	if (screen_pos.z <= 0.1f)
		return D3DXVECTOR2(0, 0);

	screen_pos.z = 1.0f / screen_pos.z;
	screen_pos.x *= screen_pos.z;
	screen_pos.y *= screen_pos.z;

	auto width = d3d9::screen_width;
	auto height = d3d9::screen_height;
	float x_temp = width / 2;
	float y_temp = height / 2;

	screen_pos.x += x_temp + float(0.5f * screen_pos.x * width + 0.5f);
	screen_pos.y = y_temp - float(0.5f * screen_pos.y * height + 0.5f);
	return D3DXVECTOR2(screen_pos.x, screen_pos.y);
}

bool c_esp::get_bounding_box(D3DXVECTOR3 origin, D3DXVECTOR3 mins, D3DXVECTOR3 maxs, int &out_x, int &out_y, int &out_w, int &out_h) {
	D3DXVECTOR3 min = (origin + mins);
	D3DXVECTOR3 max = (origin + maxs);
	D3DXVECTOR3 points[] = {
			D3DXVECTOR3(min.x, min.y, min.z),
			D3DXVECTOR3(min.x, max.y, min.z),
			D3DXVECTOR3(max.x, max.y, min.z),
			D3DXVECTOR3(max.x, min.y, min.z),
			D3DXVECTOR3(max.x, max.y, max.z),
			D3DXVECTOR3(min.x, max.y, max.z),
			D3DXVECTOR3(min.x, min.y, max.z),
			D3DXVECTOR3(max.x, min.y, max.z)
	};

	D3DXVECTOR2 w2s_points[8];
	auto index = 0;
	for (D3DXVECTOR3 point : points) {
		w2s_points[index] = world_to_screen(point);
		if (w2s_points[index].x == 0.f && w2s_points[index].y == 0.f)
			return false;
		index++;
	}

	float x = w2s_points[0].x;
	float y = w2s_points[0].y;
	float width = w2s_points[0].x;
	float height = w2s_points[0].y;
	for (auto point : w2s_points) {
		if (x > point.x)
			x = point.x;
		if (width < point.x)
			width = point.x;
		if (y > point.y)
			y = point.y;
		if (height < point.y)
			height = point.y;
	}

	out_x = x;
	out_y = y;
	out_w = width - x;
	out_h = height - y;
	return true;
}

D3DXVECTOR3 c_esp::get_bone_position(uintptr_t ped_ptr, int bone_id) {
	auto matrix = c_mem::get()->read_mem<D3DXMATRIX>(ped_ptr + 0x60);
	auto bone = c_mem::get()->read_mem<D3DXVECTOR3>(ped_ptr + (0x430 + bone_id * 0x10));
	D3DXVECTOR4 transform;
	D3DXVec3Transform(&transform, &bone, &matrix);
	return D3DXVECTOR3(transform.x, transform.y, transform.z);
}

void c_esp::draw_skeleton(uintptr_t ped_base) {
	int bone_positions[][2] = {
		{ 0, 7 },
	    { 7, 6 },
        { 7, 5 },
		{ 7, 8 },
		{ 8, 3 },
		{ 8, 4 }
	};
	for (int i = 0; i < 6; ++i) {
		D3DXVECTOR2 screen_1, screen_2;
		auto bone_1 = get_bone_position(ped_base, bone_positions[i][0]),
			 bone_2 = get_bone_position(ped_base, bone_positions[i][1]);
		if (bone_1 != D3DXVECTOR3(0, 0, 0) && bone_2 != D3DXVECTOR3(0, 0, 0) && ((screen_1 = world_to_screen(bone_1)) != D3DXVECTOR2(0, 0)) && ((screen_2 = world_to_screen(bone_2)) != D3DXVECTOR2(0, 0))) {
			rendering::c_renderer::get()->draw_line(screen_1.x, screen_1.y, screen_2.x, screen_2.y, D3DCOLOR_RGBA(255, 0, 0, 255));
		}
	}
}

void c_esp::draw_esp() {
	static auto replay_interface = c_replay_interface(c_mem::get()->read_mem<uintptr_t>(g::base_address + (g::is_steam_version ? (0x01F00028) : (0x01EFD4C8))));
	static auto world_ptr = c_mem::get()->read_mem<uintptr_t>(g::base_address + (g::is_steam_version ? (0x024839C8) : (0x0247F840)));
	static auto local_ped = c_ped(c_mem::get()->read_mem<uintptr_t>(world_ptr + 0x8));
	static bool player_var[33];
	static bool teleport_to_player[33];

	if (local_ped.get_playerinfo_ptr()) {
		auto playerinfo = local_ped.get_playerinfo();
		auto local = local_ped.get_ped();
		if (vars::player_godmode) {
			c_mem::get()->write_mem<byte>(local_ped.base + 0x189, 1); //godmode_byte
		}
		if (vars::semi_godmode) {
			auto max_health = local.max_health;
			auto health = local.health;
			if ((health > 0.f) && (health < max_health))
				c_mem::get()->write_mem<float>(local_ped.base + 0x280, max_health); //godmode_byte
		}

		if (vars::vehicle_godmode) {
			c_mem::get()->write_mem<byte>(local.last_vehicle_ptr + 0x189, 1); //godmode_byte
			c_mem::get()->write_mem<float>(local.last_vehicle_ptr + 0x280, 1000); // health1
			c_mem::get()->write_mem<float>(local.last_vehicle_ptr + 0x8E8, 1000); // health2
			c_mem::get()->write_mem<float>(local.last_vehicle_ptr + 0x824, 1000); // health3
		}
		if (vars::explosive_ammo || vars::explosive_ammo || vars::fire_ammo || vars::super_jump) {
			auto readshit = c_mem().read_mem<uintptr_t>(playerinfo.frame_flags);
			c_mem().write_mem<uintptr_t>(local_ped.get_playerinfo_ptr() + 0x01F8, readshit |
				(vars::explosive_ammo ? frame_flags::explosive_ammo : 0) |
				(vars::explosive_meelee ? frame_flags::explosive_meelee : 0) |
				(vars::super_jump ? frame_flags::super_jump : 0) |
				(vars::fire_ammo ? frame_flags::fire_ammo : 0));
		}
	}
	static bool draw_plist = false;
	menu_framework->add_entry(L"PLAYERLIST", &draw_plist, c_menu_framework::tab_type::type_tab);

	auto pedlist_interface = replay_interface.get_ped_list(); //0x0100
	auto ped_list = pedlist_interface.list_ptr;
	if (!ped_list)
		return;

	for (auto i = 0U; i < pedlist_interface.max_ptrs; i++) {
		auto ped = c_ped(c_mem::get()->read_mem<uintptr_t>(ped_list + (i * 0x10)));
		if (!ped.base)
			continue;

		auto ped_origin = ped.get_position();
		auto local_origin = c_mem::get()->read_mem<D3DXVECTOR3>(local_ped.get_navigation() + 0x50);

		if (!vars::draw_local_player && ped.base == local_ped.base)
			continue;

		auto ped_type = ped.get_ped_type();
		ped_type = ped_type << 11 >> 25;

		auto playerinfo = ped.get_playerinfo();
		if (!vars::draw_npcs && ped_type != NETWORK_PLAYER)
			continue;

		if (ped.get_playerinfo_ptr()) {
			if (draw_plist) {
				auto player_name = std::string(playerinfo.name);
				if (ped.base != local_ped.base)
					menu_framework->add_entry((L"  " + std::to_wstring(i) + L", " + std::wstring(player_name.begin(), player_name.end())).c_str(), &player_var[i], c_menu_framework::tab_type::type_dont_draw);
				if (player_var[i]) {
					menu_framework->add_entry(L"Teleport to", &teleport_to_player[i], c_menu_framework::tab_type::type_on_off);
				}
			}
		}

		if (teleport_to_player[i]) { // this shit buggy af, needs to be looped couple times in order to teleport anywhere. might also teleport u in random locations lol.
			auto delta_pos = (local_origin - ped_origin);
			auto length = sqrtf(delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y + delta_pos.z * delta_pos.z);
			c_mem::get()->write_mem<D3DXVECTOR3>(local_ped.get_navigation() + 0x50, ped_origin);
			if (length < 200) {
				teleport_to_player[i] = false;
			}
		}

		if (!vars::draw_esp)
			continue;

		auto mins = D3DXVECTOR3(-0.61f, -0.25f, -1.30f), maxs = D3DXVECTOR3(0.61f, 0.25f, 0.94f);
		if (ped_type == ped_types::ANIMAL) {
			mins = D3DXVECTOR3(-0.305f, -0.125f, -0.469f);
			maxs = D3DXVECTOR3(0.305f, 0.125f, 0.469f);
		}

		std::wstring name = (get_ped_type_name(ped.base, ped_type));
		auto health = ped.get_ped().health;
		if (health <= 0)
			continue;

		name.append(L" - " + std::to_wstring((int)health) + L"hp");

		if (ped.get_ped().god_mode)
			name.append(L" - GOD MODE");

		if (vars::draw_skeleton)
			draw_skeleton(ped.base);

		int x, y, w, h;
		if (get_bounding_box(ped_origin, mins, maxs, x, y, w, h)) {
			if (vars::draw_box) {
				auto box_col = (ped_type == NETWORK_PLAYER) ? D3DCOLOR_RGBA(255, 0, 0, 255) : D3DCOLOR_RGBA(0, 255, 0, 255);
				rendering::c_renderer::get()->draw_rect(x, y, w, h, D3DCOLOR_RGBA(0, 0, 0, 255));
				rendering::c_renderer::get()->draw_rect(x + 1, y + 1, w - 2, h - 2, box_col);
				rendering::c_renderer::get()->draw_rect(x + 2, y + 2, w - 4, h - 4, D3DCOLOR_RGBA(0, 0, 0, 255));
			}
			if (vars::draw_name)
				rendering::c_renderer::get()->draw_string(x + (w / 2), y - 16, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, 255), DT_CENTER, false, std::wstring(name.begin(), name.end()).c_str());
		}
	}
}