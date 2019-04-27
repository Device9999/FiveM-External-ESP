#include "esp.hpp"
#include "../menu/menu.hpp"
#include "../aimbot/aimbot.hpp"

D3DXVECTOR2 c_esp::world_to_screen(D3DXVECTOR3 world_pos) {
	static uintptr_t viewport = c_mem::get()->read_mem<uintptr_t>(g::base_address.modBaseAddr + (g::is_steam_version ? (0x0208BAF0) : (0x02087780)));
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
		auto bone_1 = sdk::get_bone_position(ped_base, bone_positions[i][0]),
			 bone_2 = sdk::get_bone_position(ped_base, bone_positions[i][1]);
		if (bone_1 != D3DXVECTOR3(0, 0, 0) && bone_2 != D3DXVECTOR3(0, 0, 0) && ((screen_1 = world_to_screen(bone_1)) != D3DXVECTOR2(0, 0)) && ((screen_2 = world_to_screen(bone_2)) != D3DXVECTOR2(0, 0))) {
			rendering::c_renderer::get()->draw_line(screen_1.x, screen_1.y, screen_2.x, screen_2.y, D3DCOLOR_RGBA(255, 0, 0, 255));
		}
	}
}

void c_esp::draw_esp() {
	static auto replay_interface = sdk::c_replay_interface(c_mem::get()->read_mem<uintptr_t>(g::base_address.modBaseAddr + (g::is_steam_version ? (0x01F00028) : (0x01EFD4C8))));
	static sdk::c_ped local_ped;
	static bool player_var[33];
	static bool teleport_to_player[33];

	if (vars::esp::draw_drugs)
		this->draw_object_esp(replay_interface);

	if (!local_ped.base) {
		local_ped = sdk::c_ped(c_mem::get()->read_mem<uintptr_t>(g::world_ptr + 0x8));
		memset(player_var, 0, sizeof(*player_var));
		memset(teleport_to_player, 0, sizeof(*teleport_to_player));
		return;
	}

	auto local_origin = c_mem::get()->read_mem<D3DXVECTOR3>(local_ped.get_navigation() + 0x50);
	if (local_ped.get_playerinfo_ptr()) {
		auto playerinfo = local_ped.get_playerinfo();
		auto local = local_ped.get_ped();
		auto cur_vehicle = c_mem::get()->read_mem<uint64_t>(local_ped.base + 0x0D28);

		if (vars::player::teleport_to_waypoint || vars::esp::draw_waypoint) {
			auto blip_list = (uint64_t)(g::base_address.modBaseAddr + 0x206B4E0);
			auto teleport_height = -200.f;
			for (int i = 0; i < 2000; i++) {
				auto blip = c_mem::get()->read_mem<uintptr_t>(blip_list + (i * 8));
				if (!blip)
					continue;

				auto blip_color = c_mem::get()->read_mem<int>(blip + 0x48);
				auto blip_icon = c_mem::get()->read_mem<int>(blip + 0x40);
				if ((blip_color != /*BlipColor::ColorWaypoint*/84) || (blip_icon != /*BlipSprite::SpriteWaypoint*/8))
					continue;

				auto waypoint_pos = c_mem::get()->read_mem<D3DXVECTOR3>(blip + 0x10);
				if (waypoint_pos != D3DXVECTOR2(0.f, 0.f)) {
					auto waypoint_up = world_to_screen(D3DXVECTOR3(waypoint_pos.x, waypoint_pos.y, waypoint_pos.z + 220.f));
					auto screen_waypoint_pos = world_to_screen(D3DXVECTOR3(waypoint_pos.x, waypoint_pos.y, waypoint_pos.z));
					if (waypoint_up != D3DXVECTOR2(0, 0) && screen_waypoint_pos != D3DXVECTOR2(0, 0)) {
						rendering::c_renderer::get()->draw_line(screen_waypoint_pos.x, screen_waypoint_pos.y, waypoint_up.x, waypoint_up.y, D3DCOLOR_RGBA(255, 0, 0, 255));
						rendering::c_renderer::get()->draw_string(waypoint_up.x, waypoint_up.y - 14.f, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 0, 0, 255), DT_CENTER, false, (L"WAYPOINT - " + std::to_wstring(int(D3DXVec3Length(&(local_origin - waypoint_pos)))) + L"m").c_str());
					}

					if (vars::player::teleport_to_waypoint) {
						for (int i = 0; i < 5; i++) {
							if (waypoint_pos != D3DXVECTOR2(0.f, 0.f)) {
								auto vehicle_navigation = c_mem::get()->read_mem<uintptr_t>(local_ped.get_vehicle() + 0x0030);
								c_mem::get()->write_mem<D3DXVECTOR3>(vehicle_navigation + 0x50, D3DXVECTOR3(waypoint_pos.x, waypoint_pos.y, teleport_height));
								c_mem::get()->write_mem<D3DXVECTOR3>(local_ped.get_navigation() + 0x50, D3DXVECTOR3(waypoint_pos.x, waypoint_pos.y, teleport_height));
							}
						}
						vars::player::teleport_to_waypoint = false;
					}
				}
			}
		}
	}
	static bool draw_plist = false;
	menu_framework->add_entry(L"PLAYERLIST", &draw_plist, c_menu_framework::tab_type::type_tab);

	auto pedlist_interface = replay_interface.get_ped_list(); //0x0100
	auto ped_list = pedlist_interface.list_ptr;
	if (!ped_list)
		return;

	for (auto i = 0U; i < pedlist_interface.max_ptrs; i++) {
		auto ped = sdk::c_ped(c_mem::get()->read_mem<uintptr_t>(ped_list + (i * 0x10)));
		if (!ped.base)
			continue;

		auto ped_origin = ped.get_position();
		if (!vars::esp::draw_local_player && ped.base == local_ped.base)
			continue;

		if (vars::player::enable_aimbot)
			c_aimbot().do_aimbot(ped);

		auto ped_type = ped.get_ped_type();
		ped_type = ped_type << 11 >> 25;

		auto playerinfo = ped.get_playerinfo();
		auto distance = D3DXVec3Length(&(local_origin - ped_origin));

		if (!vars::esp::draw_npcs && ped_type != sdk::NETWORK_PLAYER)
			continue;

		if (ped_type != sdk::NETWORK_PLAYER) {
			if (distance > vars::esp::npc_render_distance)
				continue;
		} else {
			if (distance > vars::esp::player_render_distance)
				continue;
		}

		if (ped.get_playerinfo_ptr()) {
			if (draw_plist) {
				auto player_name = std::string(playerinfo.name);
				if (ped.base != local_ped.base)
					menu_framework->add_entry((L"  " + std::to_wstring(i) + L", " + std::wstring(player_name.begin(), player_name.end())).c_str(), &player_var[i], c_menu_framework::tab_type::type_dont_draw);
				if (player_var[i]) {
					menu_framework->add_entry(L"Teleport to", &teleport_to_player[i], c_menu_framework::tab_type::type_on_off);
				}
			}
			if (teleport_to_player[i]) { // this shit buggy af, needs to be looped couple times in order to teleport anywhere. might also teleport u in random locations lol.
				for (int i = 0; i < 5; i++) {
					auto vehicle_navigation = c_mem::get()->read_mem<uintptr_t>(local_ped.get_vehicle() + 0x0030);
					c_mem::get()->write_mem<D3DXVECTOR3>(vehicle_navigation + 0x50, ped_origin);
					c_mem::get()->write_mem<D3DXVECTOR3>(local_ped.get_navigation() + 0x50, ped_origin);
				}
				teleport_to_player[i] = false;
			}
		}

		if (!vars::esp::draw_esp)
			continue;

		auto mins = D3DXVECTOR3(-0.61f, -0.25f, -1.30f), maxs = D3DXVECTOR3(0.61f, 0.25f, 0.94f);
		if (ped_type == sdk::ped_types::ANIMAL) {
			mins = D3DXVECTOR3(-0.305f, -0.125f, -0.469f);
			maxs = D3DXVECTOR3(0.305f, 0.125f, 0.469f);
		}

		std::wstring name = (sdk::get_ped_type_name(ped.base, ped_type));
		auto health = ped.get_ped().health;
		if (health <= 0)
			continue;

		name.append(L" - " + std::to_wstring((int)health) + L"hp");

		if (vars::esp::draw_distance)
			name.append(L" - " + std::to_wstring(int(distance)) + L"m");

		if (ped.get_ped().god_mode)
			name.append(L" - GOD MODE");

		if (vars::esp::draw_skeleton)
			draw_skeleton(ped.base);

		int x, y, w, h;
		if (get_bounding_box(ped_origin, mins, maxs, x, y, w, h)) {
			if (vars::esp::draw_box) {
				auto box_col = (ped_type == sdk::NETWORK_PLAYER) ? D3DCOLOR_RGBA(255, 0, 0, 255) : D3DCOLOR_RGBA(0, 255, 0, 255);
				rendering::c_renderer::get()->draw_rect(x, y, w, h, D3DCOLOR_RGBA(0, 0, 0, 255));
				rendering::c_renderer::get()->draw_rect(x + 1, y + 1, w - 2, h - 2, box_col);
				rendering::c_renderer::get()->draw_rect(x + 2, y + 2, w - 4, h - 4, D3DCOLOR_RGBA(0, 0, 0, 255));
			}
			if (vars::esp::draw_name)
				rendering::c_renderer::get()->draw_string(x + (w / 2), y - 13, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, 255), DT_CENTER, false, std::wstring(name.begin(), name.end()).c_str());

			if (vars::esp::draw_weapon) {
				auto weapon_mgr = ped.get_ped().weapon_manager_ptr;
				if (weapon_mgr) {
					auto weapon_current = c_mem::get()->read_mem<uintptr_t>(weapon_mgr + 0x20);
					if (weapon_current) {
						auto weapon_hash = c_mem::get()->read_mem<uint32_t>(weapon_current + 0x10);
						rendering::c_renderer::get()->draw_string(x + (w / 2), y + h + 2, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, 255), DT_CENTER, false, sdk::get_weapon_name(weapon_hash).c_str());
					}
				}
			}
		}
	}
}


void c_esp::draw_object_esp(sdk::c_replay_interface replay_iface) {
	auto objectlist_interface = replay_iface.get_object_list(); //0x0100
	auto ped_list = objectlist_interface.list_ptr;
	if (!ped_list)
		return;

	static bool load_custom_hash = false;
	static uint64_t custom_hash = 0;
	static std::string custom_hash_name = "??";
	if (vars::esp::draw_custom_hash && !load_custom_hash) {
		static TCHAR current_path[MAX_PATH], value_output[32] = { '\0' };
		GetCurrentDirectoryA(MAX_PATH, current_path);
		static auto filepath = std::string(current_path) + "\\weapon_hash.cfg";

		GetPrivateProfileStringA("DRUG_ESP", "custom_hash_to_draw", 0, value_output, 32, filepath.c_str());
		custom_hash = std::stoull(value_output);
		GetPrivateProfileStringA("DRUG_ESP", "custom_hash_name", 0, value_output, 32, filepath.c_str());
		custom_hash_name = value_output;
		load_custom_hash = true;
	}

	for (auto i = 0U; i < objectlist_interface.max_objects; i++) {
		auto object = c_mem::get()->read_mem<uintptr_t>(ped_list + (i * 0x10));
		if (!object)
			continue;
		
		auto position = c_mem::get()->read_mem<D3DXVECTOR3>(object + 0x0090);
		if (position != D3DXVECTOR3(0, 0, 0)) {
			auto w2s = world_to_screen(position);
			auto c_base_info = c_mem::get()->read_mem<uint64_t>(object + 0x20);
			auto weapon_hash = c_mem::get()->read_mem<int32_t>(c_base_info + 0x18);

			std::wstring namee = L"";
			struct hash_name {
				std::wstring name;
				int32_t hash;
			};

			static std::vector<hash_name> hashes = {
				hash_name{L"hei_prop_heist_weed_block_01", -54433116},
				hash_name{L"hei_prop_heist_weed_block_01b", -680115871},
				hash_name{L"hei_prop_heist_weed_pallet", -553616286},
				hash_name{L"hei_prop_heist_weed_pallet_02", 1228076166},
				hash_name{L"p_weed_bottle_s", 2021859795},

				hash_name{L"prop_weed_01", 452618762},
				hash_name{L"prop_weed_02", -305885281},
				hash_name{L"prop_weed_block_01", -1688127},
				hash_name{L"prop_weed_bottle", 671777952},
				hash_name{L"prop_weed_pallet", 243282660},
				hash_name{L"prop_weed_tub_01", -232602273},
				hash_name{L"prop_weed_tub_01b", 1913437669},

				hash_name{L"prop_money_bag_01", 289396019},
				hash_name{L"prop_michael_backpack", 1585260068},
				hash_name{L"p_michael_backpack_s", 1203231469},

				hash_name{L"hei_prop_hei_drug_case", 1049338225},
				hash_name{L"hei_prop_hei_drug_pack_01a", 525896218},
				hash_name{L"hei_prop_hei_drug_pack_01b", -395076527},
				hash_name{L"hei_prop_hei_drug_pack_02", -1907742965},
				hash_name{L"ng_proc_drug01a002", -2127785247},
				hash_name{L"prop_drug_package", 528555233},
				hash_name{L"prop_drug_package_02", -1964997422},
				hash_name{L"prop_mp_drug_pack_blue", -1620734287},
				hash_name{L"prop_mp_drug_pack_red", 138777325},
				hash_name{L"prop_mp_drug_package", 765087784},

				hash_name{L"p_meth_bag_01_s", 1808635348},
				hash_name{L"prop_meth_bag_01", 285917444},
				hash_name{L"prop_meth_setup_01", -2059889071}
			};

			for (auto hash : hashes) {
				if (weapon_hash == hash.hash)
					namee = hash.name;
			}

			if(vars::esp::draw_custom_hash && custom_hash != 0 && weapon_hash == custom_hash)
				namee = std::wstring(custom_hash_name.begin(), custom_hash_name.end());


			if (!namee.empty())
				rendering::c_renderer::get()->draw_string(w2s.x, w2s.y, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 0, 0, 255), DT_CENTER, false, namee.c_str());
		}
	}
}