#include "menu.hpp"

void c_menu_framework::draw() {
	this->menu_x = vars::menu::menu_x;
	this->menu_y = vars::menu::menu_y;

	static bool player_tab = false;
	static bool vehicle_tab = false;
	static bool esp_tab = false;
	static bool weapon_tab = false;
	static bool replacer_tab = false;
	static bool color_tab = false;

	this->add_entry(L"PLAYER", &player_tab, true);
	if (player_tab) {
		this->add_entry(L"  Aimbot", &vars::player::enable_aimbot, 0, L"Kinda buggy");
		this->add_entry(L"  GodMode", &vars::player::player_godmode);
		this->add_entry(L"  Semi-GodMode", &vars::player::semi_godmode, 0, L"Refill health");
		this->add_entry(L"  Super Jump", &vars::weapon::super_jump);
		this->add_entry(L"  Invisible", &vars::player::invisible_player, 0, L"Client-sided");
		this->add_entry(L"  Teleport To Waypoint", &vars::player::teleport_to_waypoint, 0, L"Might need spamming.");
		this->add_entry(L"  Run Speed", &vars::player::run_speed_amount, 0.f, 15.f, 1.f);
		this->add_entry(L"  Swim Speed", &vars::player::swim_speed_amount, 0.f, 15.f, 1.f);
		this->add_entry(L"  Draw Crosshair", &vars::weapon::draw_crosshair);
	}

	this->add_entry(L"ESP", &esp_tab, true);
	if (esp_tab) {
		this->add_entry(L"  Draw ESP", &vars::esp::draw_esp);
		this->add_entry(L"  Draw Name", &vars::esp::draw_name);
		this->add_entry(L"  Draw Distance", &vars::esp::draw_distance);
		this->add_entry(L"  Draw Weapon", &vars::esp::draw_weapon);
		this->add_entry(L"  Draw Skeleton", &vars::esp::draw_skeleton);
		this->add_entry(L"  Draw Box", &vars::esp::draw_box);
		this->add_entry(L"  Draw NPCs", &vars::esp::draw_npcs);
		this->add_entry(L"  Draw LocalPlayer", &vars::esp::draw_local_player);
		this->add_entry(L"  Draw Waypoint", &vars::esp::draw_waypoint);
		this->add_entry(L"  Draw Drugs", &vars::esp::draw_drugs);
		this->add_entry(L"  Draw Custom Hash", &vars::esp::draw_custom_hash);
		this->add_entry(L"  NPC Render Dist", &vars::esp::npc_render_distance, 0.f, 9999.f, 1.f);
		this->add_entry(L"  Player Render Dist", &vars::esp::npc_render_distance, 0.f, 9999.f, 1.f);
	}

	this->add_entry(L"WEAPON", &weapon_tab, true);
	if (weapon_tab) {
		this->add_entry(L"  REPLACER", &replacer_tab, true);
		if (replacer_tab) {
			this->add_entry(L"    Replace Pistol", &vars::weapon_replacers::replace_pistol);
			this->add_entry(L"    Replace Combat Pistol", &vars::weapon_replacers::replace_combat_pistol);
			this->add_entry(L"    Replace Bat", &vars::weapon_replacers::replace_bat);
			this->add_entry(L"    Replace Knife", &vars::weapon_replacers::replace_knife);
		}
		this->add_entry(L"  Explosive Ammo", &vars::weapon::explosive_ammo);
		this->add_entry(L"  Explosive Meelee", &vars::weapon::explosive_meelee);
		this->add_entry(L"  Fire Ammo", &vars::weapon::fire_ammo);
		this->add_entry(L"  Infinite Ammo", &vars::weapon::infinite_ammo);
		this->add_entry(L"  No Reload", &vars::weapon::no_reload);
		this->add_entry(L"  No Recoil", &vars::weapon::no_recoil);
		this->add_entry(L"  No Spread", &vars::weapon::no_spread);

		this->add_entry(L"  Reload Speed", &vars::weapon::reload_speed, 1.f, 999.f, 1.f);
		this->add_entry(L"  Damage Multiplier", &vars::weapon::damage_multiplier, 1.f, 50.f, 1.f);
		this->add_entry(L"  Bullet Damage", &vars::weapon::bullet_damage, 1.f, 500.f, 1.f);
		this->add_entry(L"  Bullet Mass", &vars::weapon::bullet_mass, 1.f, 500.f, 1.f);
		this->add_entry(L"  Muzzle Velocity", &vars::weapon::muzzle_velocity, 1.f, 500.f, 1.f);
		this->add_entry(L"  Weapon Range", &vars::weapon::weapon_range, 120.f, 9999.f, 1.f);
		this->add_entry(L"  Penetration Amount", &vars::weapon::penetration_amount, 0.1f, 999.f, 1.f);

	}

	this->add_entry(L"VEHICLE", &vehicle_tab, true);
	if (vehicle_tab) {
		this->add_entry(L"  GodMode", &vars::vehicle_mods::vehicle_godmode);
		this->add_entry(L"  Seatbelt", &vars::vehicle_mods::seatbelt);
		this->add_entry(L"  Acceleration Force", &vars::vehicle_mods::acceleration_force, 1.f, 999.f, 1.f);
		this->add_entry(L"  Brake Force", &vars::vehicle_mods::brake_force, 1.f, 999.f, 1.f);
		this->add_entry(L"  Vehicle Mass", &vars::vehicle_mods::vehicle_mass, 1.f, 9999.f, 1.f);
		this->add_entry(L"  Vehicle Buoyancy", &vars::vehicle_mods::buoyancy, 1.f, 9999.f, 1.f);
		this->add_entry(L"  Deform Multiplier", &vars::vehicle_mods::deform_multiplier, 0.f, 1000.f, 0.1f);
		this->add_entry(L"  Traction MinCurve", &vars::vehicle_mods::traction_min_curve, 0.f, 50.f, 0.1f);
		this->add_entry(L"  Traction MaxCurve", &vars::vehicle_mods::traction_max_curve, 0.f, 50.f, 0.1f);

		this->add_entry(L"  COLOR", &color_tab, true);
		if (color_tab) {
			static auto prim_r = 0.f, prim_g = 0.f, prim_b = 0.f,
				secn_r = 0.f, secn_g = 0.f, secn_b = 0.f,
				wheel_r = 0.f, wheel_g = 0.f, wheel_b = 0.f;
			this->add_entry(L"    Primary Red", &prim_r, 0.f, 255.f, 1.f);
			this->add_entry(L"    Primary Green", &prim_g, 0.f, 255.f, 1.f);
			this->add_entry(L"    Primary Blue", &prim_b, 0.f, 255.f, 1.f);

			this->add_entry(L"    Secondary Red", &secn_r, 0.f, 255.f, 1.f);
			this->add_entry(L"    Secondary Green", &secn_g, 0.f, 255.f, 1.f);
			this->add_entry(L"    Secondary Blue", &secn_b, 0.f, 255.f, 1.f);

			this->add_entry(L"    Wheel Red", &wheel_r, 0.f, 255.f, 1.f);
			this->add_entry(L"    Wheel Green", &wheel_g, 0.f, 255.f, 1.f);
			this->add_entry(L"    Wheel Blue", &wheel_b, 0.f, 255.f, 1.f);

			this->add_entry(L"    Update Car Color", &vars::vehicle_mods::update_car_color);


			vars::vehicle_mods::primary_car_color = color_t(prim_b, prim_g, prim_r, 0.f);
			vars::vehicle_mods::secondary_car_color = color_t(secn_b, secn_g, secn_r, 0.f);
			vars::vehicle_mods::car_wheel_color = color_t(wheel_b, wheel_g, wheel_r, 0.f);
		}
	}
	static bool menu_tab = false;
	this->add_entry(L"MENU", &menu_tab, true);
	if (menu_tab) {
		this->add_entry(L"  Menu x", &vars::menu::menu_x, 0.f, 1920.f, 1.f);
		this->add_entry(L"  Menu y", &vars::menu::menu_y, 0.f, 1080.f, 1.f);
		this->add_entry(L"  Menu Alpha", &vars::menu::menu_alpha, 0.f, 255.f, 1.f);
	}
}

void c_menu_framework::do_menu_controls() {
	static int item_gap = 14;
	static int alpha = 255;
	alpha = vars::menu::menu_alpha;

	rendering::c_renderer::get()->draw_filled_rect(this->menu_x - 3, this->menu_y - 17, 154, 17, D3DCOLOR_RGBA(26, 26, 26, alpha));
	rendering::c_renderer::get()->draw_rect(this->menu_x - 3, this->menu_y - 17, 154, 17, D3DCOLOR_RGBA(102, 0, 204, alpha));

	rendering::c_renderer::get()->draw_string(this->menu_x + (154 / 2), this->menu_y - 15, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, alpha), DT_CENTER, false, (L"FiveM External - " + std::to_wstring(utilities::get_frame_rate())).c_str());

	rendering::c_renderer::get()->draw_filled_rect(this->menu_x - 3, this->menu_y, 154, (items.size() * item_gap), D3DCOLOR_RGBA(31, 31, 31, alpha));
	rendering::c_renderer::get()->draw_rect(this->menu_x - 3, this->menu_y, 154, (items.size() * item_gap), D3DCOLOR_RGBA(102, 0, 204, alpha));

	rendering::c_renderer::get()->draw_filled_rect(this->menu_x - 3, this->menu_y + (item_gap * m_current_pos), 154, item_gap, D3DCOLOR_RGBA(26, 26, 26, alpha));
	rendering::c_renderer::get()->draw_rect(this->menu_x - 3, this->menu_y + (item_gap * m_current_pos), 154, item_gap, D3DCOLOR_RGBA(102, 0, 204, alpha));

	if (items.empty())
		return;
	if (m_current_pos > items.size())
		m_current_pos = items.size();

	if (!items[m_current_pos].tool_tip.empty()) {
		rendering::c_renderer::get()->draw_filled_rect(this->menu_x - 3, this->menu_y + (items.size() * item_gap) + 3, 154, 28, D3DCOLOR_RGBA(31, 31, 31, alpha));
		rendering::c_renderer::get()->draw_rect(this->menu_x - 3, this->menu_y + (items.size() * item_gap) + 3, 154, 28, D3DCOLOR_RGBA(102, 0, 204, alpha));

		rendering::c_renderer::get()->draw_string(this->menu_x, this->menu_y + (items.size() * item_gap) + 5, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, alpha), DT_LEFT, true, L"NOTE:");
		rendering::c_renderer::get()->draw_string(this->menu_x, this->menu_y + (items.size() * item_gap) + 16, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, alpha), DT_LEFT, true, items[m_current_pos].tool_tip.c_str());

	}

	for (auto item = 0; item < items.size(); ++item) {
		auto height = this->menu_y + (item_gap * item);

		switch (items[item].m_type)
		{
		case item_type::type_bool: {
			rendering::c_renderer::get()->draw_string(this->menu_x, height, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, alpha), DT_LEFT, true, items[item].m_title.c_str());
			if (items[item].tab_type == tab_type::type_on_off)
				rendering::c_renderer::get()->draw_string(this->menu_x + 150, height, d3d9::tahoma_13, *items[item].m_bool ? D3DCOLOR_RGBA(0, 255, 0, alpha) : D3DCOLOR_RGBA(255, 0, 0, alpha), DT_RIGHT, true, *items[item].m_bool ? L"ON" : L"OFF");
			else if(items[item].tab_type == tab_type::type_tab)
				rendering::c_renderer::get()->draw_string(this->menu_x + 150, height, d3d9::tahoma_13, *items[item].m_bool ? D3DCOLOR_RGBA(0, 255, 0, alpha) : D3DCOLOR_RGBA(255, 0, 0, alpha), DT_RIGHT, true, *items[item].m_bool ? L"[-]" : L"[+]");
			break;
		}
		case item_type::type_int: {
			rendering::c_renderer::get()->draw_string(this->menu_x, height, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, alpha), DT_LEFT, true, items[item].m_title.c_str());
			rendering::c_renderer::get()->draw_string(this->menu_x + 150, height, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, alpha), DT_RIGHT, true, L"%i", *items[item].m_int);
			break;
		}
		case item_type::type_float: {
			rendering::c_renderer::get()->draw_string(this->menu_x, height, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, alpha), DT_LEFT, true, items[item].m_title.c_str());
			rendering::c_renderer::get()->draw_string(this->menu_x + 150, height, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, alpha), DT_RIGHT, true, L"%.2f", *items[item].m_float);
			break;
		}
		default:
			break;
		}

		if (GetAsyncKeyState(VK_UP) & 1) {
			m_current_pos = (m_current_pos > 0) ? (m_current_pos - 1) : items.size() - 1;
		} 
		else if (GetAsyncKeyState(VK_DOWN) & 1) {
			m_current_pos = (m_current_pos < items.size() - 1) ? (m_current_pos + 1) : 0;
		}
		else if (GetAsyncKeyState(VK_LEFT) & 1) {
			switch (items[m_current_pos].m_type) {
			case item_type::type_bool: {
				*items[m_current_pos].m_bool = !*items[m_current_pos].m_bool;
				break;
			}
			case item_type::type_int: {
				*items[m_current_pos].m_int -= items[m_current_pos].m_int_step;
				if (*items[m_current_pos].m_int < items[m_current_pos].m_int_min)
					*items[m_current_pos].m_int = items[m_current_pos].m_int_max;
				break;
			}
			case item_type::type_float: {
				*items[m_current_pos].m_float -= items[m_current_pos].m_float_step;
				if (*items[m_current_pos].m_float < items[m_current_pos].m_float_min)
					*items[m_current_pos].m_float = items[m_current_pos].m_float_max;
				break;
			}
			default:
				break;
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 1) {
			switch (items[m_current_pos].m_type) {
			case item_type::type_bool: {
				*items[m_current_pos].m_bool = !*items[m_current_pos].m_bool;
				break;
			}
			case item_type::type_int: {
				*items[m_current_pos].m_int += items[m_current_pos].m_int_step;
				if (*items[m_current_pos].m_int > items[m_current_pos].m_int_max)
					*items[m_current_pos].m_int = items[m_current_pos].m_int_min;
				break;
			}
			case item_type::type_float: {
				*items[m_current_pos].m_float += items[m_current_pos].m_float_step;
				if (*items[m_current_pos].m_float > items[m_current_pos].m_float_max)
					*items[m_current_pos].m_float = items[m_current_pos].m_float_min;
				break;
			}
			default:
				break;
			}
		}
	}
	if (!items.empty())
		items.clear();
}