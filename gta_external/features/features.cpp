#include "features.hpp"
#include "../features/weapon_replacer/weapon_replacer.hpp"

static uint64_t o_cur_vehicle = 0;
static float min_curve = 0, max_curve = 0;
void features::vehicle_features(sdk::c_ped local_ped) {
	auto cur_vehicle = c_mem::get()->read_mem<uint64_t>(local_ped.base + 0x0D28);

	if (cur_vehicle) {
		if (vars::vehicle_mods::update_car_color) {
			auto vehicle_mods_ptr = c_mem::get()->read_mem<uint64_t>(cur_vehicle + 0x48);
			if (vehicle_mods_ptr) {
				auto model_info = c_mem::get()->read_mem<uint64_t>(vehicle_mods_ptr + 0x0020);
				if (model_info) {
					c_mem::get()->write_mem<color_t>(model_info + 0xA4, vars::vehicle_mods::primary_car_color); //primary_color
					c_mem::get()->write_mem<color_t>(model_info + 0xA8, vars::vehicle_mods::secondary_car_color); //secondary_color
					c_mem::get()->write_mem<color_t>(model_info + 0xB0, vars::vehicle_mods::car_wheel_color); //wheel_color
					vars::vehicle_mods::update_car_color = false;
				}
			}
		}

		if (vars::vehicle_mods::vehicle_godmode) {
			c_mem::get()->write_mem<byte>(cur_vehicle + 0x189, 1); //godmode_byte
			c_mem::get()->write_mem<float>(cur_vehicle + 0x280, 1000); // health1
			c_mem::get()->write_mem<float>(cur_vehicle + 0x8E8, 1000); // health2
			c_mem::get()->write_mem<float>(cur_vehicle + 0x824, 1000); // health3
			c_mem::get()->write_mem<float>(cur_vehicle + 0x0820, 1000); // health4
		}

		static bool o_sbelt = false;
		if (vars::vehicle_mods::seatbelt) {
			c_mem::get()->write_mem<BYTE>(local_ped.base + 0x13EC, 0xC9);
			if (!o_sbelt)
				o_sbelt = true;
		}
		else if (o_sbelt) {
			c_mem::get()->write_mem<BYTE>(local_ped.base + 0x13EC, 0xC8);
			o_sbelt = false;
		}

		auto vehicle_handling = c_mem::get()->read_mem<uint64_t>(cur_vehicle + 0x918);
		if (vehicle_handling) {
			if (o_cur_vehicle != cur_vehicle) {
				vars::vehicle_mods::traction_min_curve = min_curve = c_mem::get()->read_mem<float>(vehicle_handling + 0x0090);
				vars::vehicle_mods::traction_max_curve = max_curve = c_mem::get()->read_mem<float>(vehicle_handling + 0x0088);
				o_cur_vehicle = cur_vehicle;
			}
			if (vars::vehicle_mods::traction_max_curve != max_curve)
				c_mem::get()->write_mem<float>(vehicle_handling + 0x0088, vars::vehicle_mods::traction_max_curve);
			if (vars::vehicle_mods::traction_min_curve != min_curve)
				c_mem::get()->write_mem<float>(vehicle_handling + 0x0090, vars::vehicle_mods::traction_min_curve);

			if (vars::vehicle_mods::acceleration_force != 1.f)
				c_mem::get()->write_mem<float>(vehicle_handling + 0x4C, vars::vehicle_mods::acceleration_force);
			if (vars::vehicle_mods::vehicle_mass != 1350.f)
				c_mem::get()->write_mem<float>(vehicle_handling + 0xC, vars::vehicle_mods::vehicle_mass);
			if (vars::vehicle_mods::buoyancy != 85.f)
				c_mem::get()->write_mem<float>(vehicle_handling + 0x40, vars::vehicle_mods::buoyancy);
			if (vars::vehicle_mods::deform_multiplier != 0.6f)
				c_mem::get()->write_mem<float>(vehicle_handling + 0x40, vars::vehicle_mods::deform_multiplier);
			if (vars::vehicle_mods::brake_force != 1.f) {
				c_mem::get()->write_mem<float>(vehicle_handling + 0x6C, vars::vehicle_mods::brake_force);
				c_mem::get()->write_mem<float>(vehicle_handling + 0x7C, vars::vehicle_mods::brake_force);
			}
		}
	}
}

void features::player_features(sdk::c_ped local_ped) {
	auto playerinfo = local_ped.get_playerinfo();
	auto local = local_ped.get_ped();

	if (vars::player::player_godmode) {
		c_mem::get()->write_mem<BYTE>(local_ped.base + 0x189, 1);
	}

	static bool was_invisible = false;
	if (vars::player::invisible_player && !was_invisible) {
		c_mem::get()->write_mem<BYTE>(local_ped.base + 0x2C, 0x1);
		was_invisible = true;
	}
	else if (!vars::player::invisible_player && was_invisible) {
		c_mem::get()->write_mem<BYTE>(local_ped.base + 0x2C, 0x37);
		was_invisible = false;
	}

	if (vars::weapon::explosive_ammo || vars::weapon::explosive_ammo || vars::weapon::fire_ammo || vars::weapon::super_jump) {
		auto readshit = c_mem().read_mem<uintptr_t>(playerinfo.frame_flags);
		c_mem().write_mem<uintptr_t>(local_ped.get_playerinfo_ptr() + 0x01F8, readshit |
			(vars::weapon::explosive_ammo ? sdk::frame_flags::explosive_ammo : 0) |
			(vars::weapon::explosive_meelee ? sdk::frame_flags::explosive_meelee : 0) |
			(vars::weapon::super_jump ? sdk::frame_flags::super_jump : 0) |
			(vars::weapon::fire_ammo ? sdk::frame_flags::fire_ammo : 0));
	}

	if (vars::player::semi_godmode) {
		auto max_health = local.max_health;
		auto health = local.health;
		if ((health > 0.f) && (health < max_health))
			c_mem::get()->write_mem<float>(local_ped.base + 0x280, max_health); //current health

		if (local.armor_amount < 200.f)
			c_mem::get()->write_mem<float>(local_ped.base + 0x14B8, 200.f); //current health
	}

	static bool enabled_infinite = false;
	if (vars::weapon::infinite_ammo && !enabled_infinite) {
		BYTE nop[] = { 0x90, 0x90, 0x90 };
		WriteProcessMemory(g::process_handle, (LPVOID)(g::base_address.modBaseAddr + 0xEC58F1), &nop, sizeof(nop), NULL); //infinite_ammo
		enabled_infinite = true;
	}
	else if (!vars::weapon::infinite_ammo && enabled_infinite) {
		BYTE original[] = { 0x41, 0x2B, 0xD1 };
		WriteProcessMemory(g::process_handle, (LPVOID)(g::base_address.modBaseAddr + 0xEC58F1), &original, sizeof(original), NULL); //infinite_ammo 41 2B D1 E8
		enabled_infinite = false;
	}

	static bool enabled_noreload = false;
	if (vars::weapon::no_reload && !enabled_noreload) {
		byte nop1[] = { 0x90, 0x90, 0x90 };
		WriteProcessMemory(g::process_handle, (LPVOID)(g::base_address.modBaseAddr + 0xEC58AC), &nop1, sizeof(nop1), NULL); //noreload
		enabled_noreload = true;
	}
	else if (!vars::weapon::no_reload && enabled_noreload) {
		BYTE original1[] = { 0x41, 0x2B, 0xC9 };
		WriteProcessMemory(g::process_handle, (LPVOID)(g::base_address.modBaseAddr + 0xEC58AC), &original1, sizeof(original1), NULL); //noreload 41 2B C9 3B C8 0F
		enabled_noreload = false;
	}

	auto weapon_mgr = local.weapon_manager_ptr;
	if (weapon_mgr) {
		auto weapon_current_ptr = c_mem::get()->read_mem<uintptr_t>(weapon_mgr + 0x20);
		//auto weapon_current = c_mem::get()->read_mem<sdk::weapon_info_t>(weapon_current_ptr);// crashes when writing struct
		if (weapon_current_ptr) {

			if (vars::weapon::reload_speed > 1.f)
				c_mem::get()->write_mem<float>(weapon_current_ptr + 0x012C, vars::weapon::reload_speed);
			if (vars::weapon::bullet_mass > 1.f) {
				c_mem::get()->write_mem<float>(weapon_current_ptr + 0x00D8, vars::weapon::bullet_mass);
				c_mem::get()->write_mem<float>(weapon_current_ptr + 0x00DC, vars::weapon::bullet_mass);
				c_mem::get()->write_mem<float>(weapon_current_ptr + 0x00D4, vars::weapon::bullet_mass);
			}
			if (vars::weapon::bullet_damage > 1.f)
				c_mem::get()->write_mem<float>(weapon_current_ptr + 0x00B0, vars::weapon::bullet_damage);
			if (vars::weapon::muzzle_velocity > 1.f)
				c_mem::get()->write_mem<float>(weapon_current_ptr + 0x0114, vars::weapon::muzzle_velocity);
			if (vars::weapon::weapon_range > 1.f)
				c_mem::get()->write_mem<float>(weapon_current_ptr + 0x028C, vars::weapon::weapon_range);

			if (vars::weapon::penetration_amount > 0.1f)
				c_mem::get()->write_mem<float>(weapon_current_ptr + 0x0108, vars::weapon::penetration_amount);
			if (vars::weapon::no_spread)
				c_mem::get()->write_mem<float>(weapon_current_ptr + 0x02E8, 0.f);
			if (vars::weapon::no_recoil)
				c_mem::get()->write_mem<float>(weapon_current_ptr + 0x0074, 0.f);


			/*if (vars::weapon::reload_speed > 1.f)
				weapon_current.reload_speed = vars::weapon::reload_speed;
			if (vars::weapon::bullet_mass > 1.f) {
				weapon_current.force_on_vehicle_bullet_mass = vars::weapon::bullet_mass;
				weapon_current.force_on_heli = vars::weapon::bullet_mass;
				weapon_current.force_on_ped = vars::weapon::bullet_mass;
			}
			if (vars::weapon::bullet_damage > 1.f)
				weapon_current.bullet_damage = vars::weapon::bullet_damage;
			if (vars::weapon::muzzle_velocity > 1.f)
				weapon_current.muzzle_velocity = vars::weapon::muzzle_velocity;
			if (vars::weapon::weapon_range > 1.f)
				weapon_current.weapon_range = vars::weapon::weapon_range;

			if (vars::weapon::penetration_amount > 0.1f)
				weapon_current.penetration_amount = vars::weapon::penetration_amount;
			if (vars::weapon::no_spread)
				weapon_current.spread = 0.f;
			if (vars::weapon::no_recoil)
				weapon_current.recoil = 0.f;

			c_mem::get()->write_mem<sdk::weapon_info_t>(weapon_current_ptr, weapon_current);*/
		}
	}

	if (vars::weapon::damage_multiplier > 1.f)
		c_mem::get()->write_mem<float>(local_ped.get_playerinfo_ptr() + 0xC98, vars::weapon::damage_multiplier);

	if (vars::player::run_speed_amount > 1.f)
		c_mem::get()->write_mem<float>(local_ped.get_playerinfo_ptr() + 0x14C, vars::player::run_speed_amount);
	if (vars::player::swim_speed_amount > 1.f)
		c_mem::get()->write_mem<float>(local_ped.get_playerinfo_ptr() + 0x0148, vars::player::swim_speed_amount);

}

void features::feature_thread() {
	while (true) {
		auto local_ped = sdk::c_ped(c_mem::get()->read_mem<uintptr_t>(g::world_ptr + 0x8));
		if (local_ped.base) {
			if (local_ped.get_playerinfo_ptr()) {
				player_features(local_ped);
				vehicle_features(local_ped);
				c_weapon_replacer();
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}