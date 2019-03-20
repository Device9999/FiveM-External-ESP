#pragma once
#include "../gta_external.hpp"

struct c_replay_interface
{
private:
	struct replay_interface_ptr_t {
		char _0x0000[0x100];
		uintptr_t list_ptr; //0x0100 
		__int32 max_ptrs; //0x0108 
		char _0x010C[0x4];
		__int32 last_ent; //0x0110 
		char _0x0114[0x34];
	} replay_pedlist_interface_ptr;//Size=0x0148

	struct replay_interface_t {
		void* game_iface;
		void* camera_iface;
		replay_interface_ptr_t* vehicle_list;
		uintptr_t PedList;
		replay_interface_ptr_t* pickup_list;
		replay_interface_ptr_t* object_list;
	} replay_interface;
public:
	uintptr_t base;
	c_replay_interface() {
		this->base = 0;
		ZeroMemory(&this->replay_interface, sizeof(this->replay_interface));
		ZeroMemory(&this->replay_pedlist_interface_ptr, sizeof(this->replay_pedlist_interface_ptr));
	}

	explicit c_replay_interface(const uintptr_t base);

	~c_replay_interface() {
		this->base = 0;
		ZeroMemory(&this->replay_interface, sizeof(this->replay_interface));
		ZeroMemory(&this->replay_pedlist_interface_ptr, sizeof(this->replay_pedlist_interface_ptr));

	}
public:
	auto get_ped_list() const {
		return this->replay_pedlist_interface_ptr;
	}
};

class c_ped
{
private:
	struct ped_t
	{
		char pad_0x0000[0x28]; //0x0000
		BYTE entity_type; //0x0028 
		char pad_0x0029[0x3]; //0x0029
		BYTE invisible; //0x002C 
		char pad_0x002D[0x1]; //0x002D
		BYTE freeze_momentum; //0x002E 
		char pad_0x002F[0x1]; //0x002F
		uintptr_t navigation_ptr; //0x0030 
		char pax_0x0038[0x10]; //0x0038
		struct c_ped_style* ped_style_ptr; //0x0048
		char pad_0x0038[0x40]; //0x0050
		D3DXVECTOR3 origin; //0x0090 
		char pad_0x009C[0xED]; //0x009C
		BYTE god_mode; //0x0189 
		char pad_0x018A[0xF6]; //0x018A
		float health; //0x0280 
		char pad_0x0284[0x1C]; //0x0284
		float max_health; //0x02A0 
		char pad_0x02A4[0x4]; //0x02A4
		struct c_attacker* attacker_ptr; //0x02A8 
		char pad_0x02B0[0x70]; //0x02B0
		D3DXVECTOR3 velocity; //0x0320 
		char pad_0x032C[0x9FC]; //0x032C
		uintptr_t last_vehicle_ptr; //0x0D28 
		char pad_0x0D30[0x378]; //0x0D30
		uint32_t ped_type; //0x10A8 
		char pad_0x10A9[12]; //0x10A9
		uintptr_t player_info_ptr; //0x10B8 
		char pad_0x10C0[0x8]; //0x10C0
		uintptr_t weapon_manager_ptr; //0x10C8 
		char pad_0x10D0[0x31C]; //0x10D0
		BYTE seatbelt; //0x13EC 
		char pad_0x13ED[0xB]; //0x13ED
		BYTE unk094; //0x13F8 
		char pad_0x13F9[0x1]; //0x13F9
		BYTE can_switch_weapons;
		char pad_0x13FB[0x5];
		BYTE forced_aim; //0x1400 
		BYTE N00000936; //0x1401 
		BYTE N00000939; //0x1402 
		BYTE N00000937; //0x1403 
		char pad_0x1404[0x67]; //0x1404
		BYTE is_in_vehicle; //0x146B 
		char pad_0x146C[0x44]; //0x146C
		float armor_amount; //0x14B0 
		char pad_0x14B4[0x20]; //0x14B4
		float fatigued_health_threshold; //0x14D4 
		float injured_health_threshold; //0x14D8 
		float dying_health_threshold; //0x14DC 
		float hurt_health_threshold; //0x14E0 
		char pad_0x14E4[0xC]; //0x14E4
		class c_vehicle* last_vehicle2_ptr; //0x14F0 
		char pad_0x14F8[0xDC]; //0x14F8
		__int32 cash; //0x15D4 
	} pedestrian;

	struct playerinfo_t
	{
		char pad_0x0000[0x34]; //0x0000
		int32_t internal_ip; //0x0034 
		int16_t internal_port; //0x0038 
		char pad_0x003A[0x2]; //0x003A
		int32_t relay_ip; //0x003C 
		int16_t relay_port; //0x0040 
		char pad_0x0042[0x2]; //0x0042
		int32_t external_ip; //0x0044 
		int16_t external_port; //0x0048 
		char pad_0x004A[0x32]; //0x004A
		char name[20]; //0x007C 
		char pad_0x0090[0x4]; //0x0090
		int32_t team; //0x0094 
		char pad_0x0098[0xB0]; //0x0098
		float swin_speed; //0x0148 
		float run_speed; //0x014C 
		char pad_0x0150[0x68]; //0x0150
		uint32_t ulstate; //0x01B8 
		char pad_0x01BC[0xC]; //0x01BC
		uintptr_t ped_ptr; //0x01C8 
		char pad_0x01D0[40]; //0x01D0
		BYTE frame_flags; //0x01F8 
		char pad_0x01FA[1383]; //0x01FA
		uintptr_t wanted_data_ptr; //0x0760 
		char pad_0x07FC[0x464]; //0x07FC
		float stamina; //0x0C60 
		float stamina_max; //0x0C64 
		char pad_0x0C68[0x10]; //0x0C68
		float damage_modifier; //0x0C78 
		char pad_0x0C7C[0x4]; //0x0C7C
		float meelee_damage_mod; //0x0C80 
		char pad_0x0C84[0x4]; //0x0C84
		float vehicle_damage_mod; //0x0C88 
		char pad_0x0C8C[0x1B4]; //0x0C8C
		BYTE is_aiming; //0x0E40 
		char pad_0x0E41[0x7]; //0x0E41
	} playerinfo;

	struct vehicle_t {
		struct c_ped_vtable* vtable; //0x0000 
		char pad_0x0008[0x18]; //0x0008
		struct c_vehicle_modinfo* modelinfo_ptr; //0x0020 
		char pad_0x0028[0x8]; //0x0028
		struct c_navigation* navigation_ptr; //0x0030 
		char pad_0x0038[0x10]; //0x0038
		struct c_vehicle_mods* vehicle_mods_ptr; //0x0048 
		char pad_0x0050[0x40]; //0x0050
		D3DXVECTOR3 origin; //0x0090 
		char pad_0x009C[0x3C]; //0x009C
		BYTE state; //0x00D8 
		char pad_0x00D9[0xB0]; //0x00D9
		BYTE god_mode; //0x0189 
		char pad_0x018A[0xF6]; //0x018A
		float health; //0x0280 
		char pad_0x0284[0x1C]; //0x0284
		float max_health; //0x02A0 
		char pad_0x02A4[0x4]; //0x02A4
		struct c_attacker* attacker_ptr; //0x02A8 
		char pad_0x02B0[0x72]; //0x02B0
		BYTE voltic_rocket_state; //0x0322 
		char pad_0x0323[0x1]; //0x0323
		float voltic_rocket_energy; //0x0324 
		char pad_0x0328[0x448]; //0x0328
		D3DXVECTOR3 velocity; //0x0770 
		char pad_0x077C[0x100]; //0x077C
		float health2; //0x087C 
		char pad_0x0880[0x28]; //0x0880
		struct c_vehicle_handling* vehicle_handling_ptr; //0x08A8 
		char pad_0x08B0[0x3]; //0x08B0
		BYTE bulletproof_tires; //0x08B3 
		char pad_0x08B4[0x4]; //0x08B4
		BYTE stolen; //0x08B8 
		char pad_0x08B9[0x11]; //0x08B9
		BYTE N00000954; //0x08CA 
		char pad_0x08CB[0x41]; //0x08CB
		float N0000081E; //0x090C 
		char pad_0x0910[0x58]; //0x0910
		float dirt_level; //0x0968 
		char pad_0x096C[0xA8]; //0x096C
		uint32_t car_alarm_length; //0x0A14 
		char pad_0x0A18[0x148]; //0x0A18
		BYTE openable_doors; //0x0B60 
		char pad_0x0B61[0x4B]; //0x0B61
		float gravity; //0x0BAC 
		BYTE max_passengers; //0x0BB0 
		char pad_0x0BB1[0x1]; //0x0BB1
		BYTE num_of_passengers; //0x0BB2 
		char pad_0x0BB3[0x5]; //0x0BB3
		ped_t passenger_ptr[16]; //0x0BB8
	} vehicle;

public:
	uintptr_t base;
	c_ped() {
		this->base = 0;
		ZeroMemory(&this->pedestrian, sizeof(this->pedestrian));
		ZeroMemory(&this->playerinfo, sizeof(this->playerinfo));
		ZeroMemory(&this->vehicle, sizeof(this->vehicle));
	}

	explicit c_ped(const uintptr_t base);

	~c_ped() {
		this->base = 0;
		ZeroMemory(&this->pedestrian, sizeof(this->pedestrian));
		ZeroMemory(&this->playerinfo, sizeof(this->playerinfo));
		ZeroMemory(&this->vehicle, sizeof(this->vehicle));

	}
public:
	D3DXVECTOR3 get_position() const {
		return pedestrian.origin;
	}
	uint32_t get_ped_type() const {
		return pedestrian.ped_type;
	}
	uintptr_t get_playerinfo_ptr() const {
		return pedestrian.player_info_ptr;
	}
	float get_health() const {
		return pedestrian.health;
	}
	playerinfo_t get_playerinfo() const {
		return playerinfo;
	}
	vehicle_t get_vehicle() const {
		return vehicle;
	}
	ped_t get_ped() {
		return pedestrian;
	}
	uintptr_t get_navigation() const {
		return pedestrian.navigation_ptr;
	}
};

enum ped_types
{
	PLAYER_0, // michael
	PLAYER_1, // franklin
	NETWORK_PLAYER, // mp character
	PLAYER_2, // trevor
	CIVMALE,
	CIVFEMALE,
	COP,
	GANG_ALBANIAN,
	GANG_BIKER_1,
	GANG_BIKER_2,
	GANG_ITALIAN,
	GANG_RUSSIAN,
	GANG_RUSSIAN_2,
	GANG_IRISH,
	GANG_JAMAICAN,
	GANG_AFRICAN_AMERICAN,
	GANG_KOREAN,
	GANG_CHINESE_JAPANESE,
	GANG_PUERTO_RICAN,
	DEALER,
	MEDIC,
	FIREMAN,
	CRIMINAL,
	BUM,
	PROSTITUTE,
	SPECIAL,
	MISSION,
	SWAT,
	ANIMAL,
	ARMY
};

enum frame_flags {
	explosive_ammo = (1 << 11),
	fire_ammo = (1 << 12),
	explosive_meelee = (1 << 13),
	super_jump = (1 << 14)
};

static auto get_ped_type_name(uintptr_t ped, uint32_t ped_type) {
	std::string type_str = "unknown";
	switch (ped_type) {
	case PLAYER_0: {
		type_str = "michael";
		break;
	}
	case PLAYER_1: {
		type_str = "franklin";
		break;
	}
	case PLAYER_2: {
		type_str = "trevor";
		break;
	}
	case NETWORK_PLAYER: {
		auto cped = c_ped(ped);
		if (cped.get_playerinfo_ptr())
			type_str = std::string(cped.get_playerinfo().name);
		break;
	}
	case CIVMALE: {
		type_str = "civil_male";
		break;
	}
	case CIVFEMALE: {
		type_str = "civil_female";
		break;
	}
	case COP: {
		type_str = "cop";
		break;
	}
	case GANG_ALBANIAN: {
		type_str = "gang_member";
		break;
	}
	case GANG_BIKER_1: {
		type_str = "gang_member";
		break;
	}
	case GANG_BIKER_2: {
		type_str = "gang_member";
		break;
	}
	case GANG_ITALIAN: {
		type_str = "gang_member";
		break;
	}
	case GANG_RUSSIAN: {
		type_str = "gang_member";
		break;
	}
	case GANG_RUSSIAN_2: {
		type_str = "gang_member";
		break;
	}
	case GANG_IRISH: {
		type_str = "gang_member";
		break;
	}
	case GANG_JAMAICAN: {
		type_str = "gang_member";
		break;
	}
	case GANG_AFRICAN_AMERICAN: {
		type_str = "gang_member";
		break;
	}
	case GANG_KOREAN: {
		type_str = "gang_member";
		break;
	}
	case GANG_CHINESE_JAPANESE: {
		type_str = "gang_member";
		break;
	}
	case GANG_PUERTO_RICAN: {
		type_str = "gang_member";
		break;
	}
	case DEALER: {
		type_str = "dealer";
		break;
	}
	case MEDIC: {
		type_str = "medic";
		break;
	}
	case FIREMAN: {
		type_str = "fireman";
		break;
	}
	case CRIMINAL: {
		type_str = "criminal";
		break;
	}
	case BUM: {
		type_str = "bum";
		break;
	}
	case PROSTITUTE: {
		type_str = "prostitute";
		break;
	}
	case SPECIAL: {
		type_str = "special";
		break;
	}
	case MISSION: {
		type_str = "mission";
		break;
	}
	case SWAT: {
		type_str = "swat";
		break;
	}
	case ANIMAL: {
		type_str = "animal";
		break;
	}
	case ARMY: {
		type_str = "army";
		break;
	}
	default:
		break;
	}
	return std::wstring(type_str.begin(), type_str.end());
}