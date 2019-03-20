#include "menu.hpp"

void c_menu_framework::draw() {
	static bool player_tab = false;
	static bool vehicle_tab = false;
	static bool esp_tab = false;
	static bool weapon_tab = false;

	this->add_entry(L"PLAYER", &player_tab, true);
	if (player_tab) {
		this->add_entry(L"  GodMode", &vars::player_godmode);
		this->add_entry(L"  Semi-GodMode", &vars::semi_godmode);
		this->add_entry(L"  Super Jump", &vars::super_jump);
	}

	this->add_entry(L"ESP", &esp_tab, true);
	if (esp_tab) {
		this->add_entry(L"  Draw ESP", &vars::draw_esp);
		this->add_entry(L"  Draw Name", &vars::draw_name);
		this->add_entry(L"  Draw Skeleton", &vars::draw_skeleton);
		this->add_entry(L"  Draw Box", &vars::draw_box);
		this->add_entry(L"  Draw NPCs", &vars::draw_npcs);
		this->add_entry(L"  Draw LocalPlayer", &vars::draw_local_player);
	}

	this->add_entry(L"WEAPON", &weapon_tab, true);
	if (weapon_tab) {
		this->add_entry(L"  Explosive Ammo", &vars::explosive_ammo);
		this->add_entry(L"  Explosive Meelee", &vars::explosive_meelee);
		this->add_entry(L"  Fire Ammo", &vars::fire_ammo);
	}

	this->add_entry(L"VEHICLE", &vehicle_tab, true);
	if (vehicle_tab) {
		this->add_entry(L"  GodMode", &vars::vehicle_godmode);
	}
}

void c_menu_framework::do_menu_controls() {
	static int item_gap = 14;
	static int alpha = 255;

	rendering::c_renderer::get()->draw_filled_rect(this->menu_x - 3, this->menu_y - 17, 154, 17, D3DCOLOR_RGBA(26, 26, 26, 255));
	rendering::c_renderer::get()->draw_rect(this->menu_x - 3, this->menu_y - 17, 154, 17, D3DCOLOR_RGBA(102, 0, 204, 255));

	rendering::c_renderer::get()->draw_string(this->menu_x + (154 / 2), this->menu_y - 15, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 255, 255, 255), DT_CENTER, false, (L"FiveM External - " + std::to_wstring(utilities::get_frame_rate())).c_str());

	rendering::c_renderer::get()->draw_filled_rect(this->menu_x - 3, this->menu_y, 154, (items.size() * item_gap), D3DCOLOR_RGBA(31, 31, 31, 255));
	rendering::c_renderer::get()->draw_rect(this->menu_x - 3, this->menu_y, 154, (items.size() * item_gap), D3DCOLOR_RGBA(102, 0, 204, 255));

	rendering::c_renderer::get()->draw_filled_rect(this->menu_x - 3, this->menu_y + (item_gap * m_current_pos), 154, item_gap, D3DCOLOR_RGBA(26, 26, 26, 255));
	rendering::c_renderer::get()->draw_rect(this->menu_x - 3, this->menu_y + (item_gap * m_current_pos), 154, item_gap, D3DCOLOR_RGBA(102, 0, 204, 255));

	if (items.empty())
		return;

	for (auto item = 0; item < items.size(); ++item) {
		auto height = this->menu_y + (item_gap * item);
		if (m_current_pos > items.size())
			m_current_pos = items.size();

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