#include "weapon_replacer.hpp"

c_weapon_replacer::c_weapon_replacer() {
	static bool init = false;
	static TCHAR current_path[MAX_PATH], value_output[32] = { '\0' };
	static std::string filepath = "";
	if (!init) {
		GetCurrentDirectoryA(MAX_PATH, current_path);
		filepath = std::string(current_path) + "\\weapon_hash.cfg";
		init = true;
	}
	if (vars::weapon_replacers::replace_pistol) {
		GetPrivateProfileStringA("WEAPON_REPLACE", "pistol_replace_hash", 0, value_output, 32, filepath.c_str());
		this->replace_pistol(std::stoull(value_output));
		vars::weapon_replacers::replace_pistol = false;
	}
	if (vars::weapon_replacers::replace_combat_pistol) {
		GetPrivateProfileStringA("WEAPON_REPLACE", "combat_pistol_replace_hash", 0, value_output, 32, filepath.c_str());
		this->replace_combat_pistol(std::stoull(value_output));
		vars::weapon_replacers::replace_combat_pistol = false;
	}
	if (vars::weapon_replacers::replace_bat) {
		GetPrivateProfileStringA("WEAPON_REPLACE", "bat_replace_hash", 0, value_output, 32, filepath.c_str());
		this->replace_bat(std::stoull(value_output));
		vars::weapon_replacers::replace_bat = false;
	}
	if (vars::weapon_replacers::replace_knife) {
		GetPrivateProfileStringA("WEAPON_REPLACE", "knife_replace_hash", 0, value_output, 32, filepath.c_str());
		this->replace_knife(std::stoull(value_output));
		vars::weapon_replacers::replace_knife = false;
	}
}

void c_weapon_replacer::replace_pistol(uint64_t hash) {
	auto pistol = c_mem::get()->read_mem<uintptr_t>(g::base_address.modBaseAddr + 0x027DB7F0);
	if (pistol) {
		pistol = c_mem::get()->read_mem<uintptr_t>(pistol + 0x128);
		if (pistol)
			c_mem::get()->write_mem<uint64_t>(pistol + 0x10, hash);
	}
}

void c_weapon_replacer::replace_combat_pistol(uint64_t hash) {
	auto combat_pistol = c_mem::get()->read_mem<uintptr_t>(g::base_address.modBaseAddr + 0x027DB7C0);
	if (combat_pistol) {
		combat_pistol = c_mem::get()->read_mem<uintptr_t>(combat_pistol + 0x50);
		c_mem::get()->write_mem<uint64_t>(combat_pistol + 0x10, hash);
	}
}

void c_weapon_replacer::replace_bat(uint64_t hash) {
	auto bat = c_mem::get()->read_mem<uint64_t>(g::base_address.modBaseAddr + 0x01CCD190);
	if (bat) {
		bat = c_mem::get()->read_mem<uint64_t>(bat);
		bat = c_mem::get()->read_mem<uint64_t>(bat + 0x100);
		bat = c_mem::get()->read_mem<uint64_t>(bat + 0x340);
		bat = c_mem::get()->read_mem<uint64_t>(bat + 0x30);
		if (bat)
			c_mem::get()->write_mem<uint64_t>(bat + 0x10, hash);
	}
}

void c_weapon_replacer::replace_knife(uint64_t hash) {
	auto knife = c_mem::get()->read_mem<uint64_t>(g::base_address.modBaseAddr + 0x0247F190);
	if (knife) {
		knife = c_mem::get()->read_mem<uint64_t>(knife + 0x30);
		knife = c_mem::get()->read_mem<uint64_t>(knife + 0x460);
		knife = c_mem::get()->read_mem<uint64_t>(knife + 0x10);
		knife = c_mem::get()->read_mem<uint64_t>(knife + 0x198);
		if(knife)
			c_mem::get()->write_mem<uint64_t>(knife + 0x10, hash);
	}
}