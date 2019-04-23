#pragma once
#include "../gta_external.hpp"
namespace sdk
{
	struct c_replay_interface
	{
	private:
		struct ped_replay_interface_ptr_t {
			char _0x0000[0x100];
			uintptr_t list_ptr; //0x0100 
			__int32 max_ptrs; //0x0108 
			char _0x010C[0x4];
			__int32 last_ent; //0x0110 
			char _0x0114[0x34];
		} replay_pedlist_interface_ptr;//Size=0x0148

		struct object_replay_interface_ptr_t
		{
			char pad_0x0000[0x158]; //0x0000
			uintptr_t list_ptr; //0x0158 
			__int32 max_objects; //0x0160 
			char pad_0x0164[0x4]; //0x0164
			__int32 cur_objects; //0x0168 
			char pad_0x016C[0x5C]; //0x016C

		} replay_objectlist_interface_ptr; //Size=0x01C8

		struct replay_interface_t {
			void* game_iface;
			void* camera_iface;
			ped_replay_interface_ptr_t* vehicle_list;
			uintptr_t PedList;
			ped_replay_interface_ptr_t* pickup_list;
			uintptr_t object_list;
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
		auto get_object_list() const {
			return this->replay_objectlist_interface_ptr;
		}
	};

	class c_ped
	{
	public:
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
			float unk1; //0x14B0
			float unk2; //0x14B4
			float armor_amount; //0x14B8 
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

	public:
		uintptr_t base;
		c_ped() {
			this->base = 0;
			ZeroMemory(&this->pedestrian, sizeof(this->pedestrian));
			ZeroMemory(&this->playerinfo, sizeof(this->playerinfo));
		//	ZeroMemory(&this->vehicle, sizeof(this->vehicle));
		}

		explicit c_ped(const uintptr_t base);

		~c_ped() {
			this->base = 0;
			ZeroMemory(&this->pedestrian, sizeof(this->pedestrian));
			ZeroMemory(&this->playerinfo, sizeof(this->playerinfo));
		//	ZeroMemory(&this->vehicle, sizeof(this->vehicle));

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
		uintptr_t get_vehicle() const {
			return pedestrian.last_vehicle_ptr;
		}
		ped_t get_ped() {
			return pedestrian;
		}
		uintptr_t get_navigation() const {
			return pedestrian.navigation_ptr;
		}
	};

	struct weapon_info_t
	{
		char pad_0000[16]; //0x0000
		uint32_t weapon_name_hash; //0x0010
		char pad_0014[12]; //0x0014
		uint32_t impact_type; //0x0020
		uint32_t impact_explosion; //0x0024
		float N00000010; //0x0028
		char pad_002C[52]; //0x002C
		uint64_t c_ammo_info_maybe; //0x0060
		char pad_0068[8]; //0x0068
		float N00000019; //0x0070
		float recoil; //0x0074
		float N0000001A; //0x0078
		char pad_007C[52]; //0x007C
		float bullet_damage; //0x00B0
		char pad_00B4[28]; //0x00B4
		float N00000025; //0x00D0
		float force_on_ped; //0x00D4
		float force_on_vehicle_bullet_mass; //0x00D8
		float force_on_heli; //0x00DC
		char pad_00E0[40]; //0x00E0
		float penetration_amount; //0x0108
		char pad_010C[4]; //0x010C
		float N0000002D; //0x0110
		float muzzle_velocity; //0x0114
		byte bullets_in_batch; //0x0118
		char pad_0119[7]; //0x0119
		float N0000002F; //0x0120
		char pad_0124[4]; //0x0124
		float N00000030; //0x0128
		float reload_speed; //0x012C
		char pad_0130[336]; //0x0130
		float N0000005B; //0x0280
		char pad_0284[4]; //0x0284
		float N0000005C; //0x0288
		float weapon_range; //0x028C
		char pad_0290[88]; //0x0290
		float spread; //0x02E8
		char pad_02EC[596]; //0x02EC
	}; //Size: 0x0540

	struct handling_data_t
	{
		char pad_0000[8]; //0x0000
		float N000001B3; //0x0008
		float vehicle_mass; //0x000C //1350.000
		float N000001B4; //0x0010
		float N000002D4; //0x0014
		float N000001B5; //0x0018
		float N000002D7; //0x001C
		char pad_0020[32]; //0x0020
		float Buoyancy; //0x0040 // 85.000
		float N000002BC; //0x0044
		float N000001BB; //0x0048
		float acceleration; //0x004C // 1.000
		char pad_0050[16]; //0x0050
		float N000001BE; //0x0060
		float N000002C2; //0x0064
		float N000001BF; //0x0068
		float brake_force; //0x006C //1.000
		float N000001C0; //0x0070
		float N000002C8; //0x0074
		float N000001C1; //0x0078
		float handbrake_force; //0x007C //0.650
		char pad_0080[8]; //0x0080
		float traction_curve_max; //0x0088 //2.560
		char pad_008C[4]; //0x008C
		float traction_curve_min; //0x0090 //2.470
		char pad_0094[92]; //0x0094
		float collision_damage_mp; //0x00F0
		float weapon_damage_mp; //0x00F4
		float deform_multiplier; //0x00F8 //0.600
		char pad_00FC[36]; //0x00FC
		float boost_max_speed; //0x0120
		char pad_0124[532]; //0x0124
		float thrust; //0x0338
		char pad_033C[1292]; //0x033C
	}; //Size: 0x0848

	struct vehicle_t
	{
		char pad_0000[48]; //0x0000
		uint64_t navigation_ptr; //0x0030
		char pad_0038[16]; //0x0038
		uint64_t vehicle_mods_ptr; //0x0048
		char pad_0050[312]; //0x0050
		uint8_t N0000003C; //0x0188
		byte god_mode; //0x0189
		char pad_018A[6]; //0x018A
		uint8_t N0000003D; //0x0190
		char pad_0191[239]; //0x0191
		float health1; //0x0280
		char pad_0284[156]; //0x0284
		float boost; //0x0320
		char pad_0324[1276]; //0x0324
		float health2; //0x0820
		float health3; //0x0824
		char pad_0828[192]; //0x0828
		float health4; //0x08E8
		char pad_08EC[44]; //0x08EC
		uintptr_t vehicle_handling_ptr; //0x0918
		char pad_0920[864]; //0x0920
	}; //Size: 0x0C80

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

	extern D3DXVECTOR3 get_bone_position(uintptr_t ped_ptr, int bone_id);

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

	static std::wstring get_weapon_name(DWORD hash)
	{
		//removed xoring, cba to do properly.
		static auto dagger = std::wstring(L"dagger");
		static auto bat = std::wstring(L"bat");
		static auto bottle = std::wstring(L"bottle");
		static auto crowbar = std::wstring(L"crowbar");
		static auto unarmed = std::wstring(L"unarmed");
		static auto flashlight = std::wstring(L"flashlight");
		static auto golfclub = std::wstring(L"golfclub");
		static auto hammer = std::wstring(L"hammer");
		static auto hatchet = std::wstring(L"hatchet");
		static auto knuckle = std::wstring(L"knuckle");
		static auto knife = std::wstring(L"knife");
		static auto machete = std::wstring(L"machete");
		static auto switchblade = std::wstring(L"switchblade");
		static auto nightstick = std::wstring(L"nightstick");
		static auto wrench = std::wstring(L"wrench");
		static auto battleaxe = std::wstring(L"battleaxe");
		static auto poolcue = std::wstring(L"poolcue");
		static auto pistol = std::wstring(L"pistol");
		static auto pistolmk2 = std::wstring(L"pistol_mk2");
		static auto combatpistol = std::wstring(L"combatpistol");
		static auto appistol = std::wstring(L"appistol");
		static auto stungun = std::wstring(L"stungun");
		static auto pistol50 = std::wstring(L"pistol50");
		static auto snspistol = std::wstring(L"snspistol");
		static auto snspistolmk2 = std::wstring(L"snspistol_mk2");
		static auto heavypistol = std::wstring(L"heavypistol");
		static auto vintagepistol = std::wstring(L"vintagepistol");
		static auto flaregun = std::wstring(L"flaregun");
		static auto marksmanpistol = std::wstring(L"marksmanpistol");
		static auto revolver = std::wstring(L"revolver");
		static auto revolvermk2 = std::wstring(L"revolver_mk2");
		static auto doubleaction = std::wstring(L"doubleaction");
		static auto microsmg = std::wstring(L"microsmg");
		static auto smg = std::wstring(L"smg");
		static auto smgmk2 = std::wstring(L"smg_mk2");
		static auto assaultsmg = std::wstring(L"assaultsmg");
		static auto combatpdw = std::wstring(L"combatpdw");
		static auto machinepistol = std::wstring(L"machinepistol");
		static auto minismg = std::wstring(L"minismg");
		static auto pumpshotgun = std::wstring(L"pumpshotgun");
		static auto pumpshotgun_mk2 = std::wstring(L"pumpshotgun_mk2");
		static auto sawnoffshotgun = std::wstring(L"sawnoffshotgun");
		static auto assaultshotgun = std::wstring(L"assaultshotgun");
		static auto bullpupshotgun = std::wstring(L"bullpupshotgun");
		static auto musket = std::wstring(L"musket");
		static auto heavyshotgun = std::wstring(L"heavyshotgun");
		static auto dbshotgun = std::wstring(L"dbshotgun");
		static auto autoshotgun = std::wstring(L"autoshotgun");
		static auto assaultrifle = std::wstring(L"assaultrifle");
		static auto assaultrifle_mk2 = std::wstring(L"assaultrifle_mk2");
		static auto carbinerifle = std::wstring(L"carbinerifle");
		static auto carbinerifle_mk2 = std::wstring(L"carbinerifle_mk2");
		static auto advancedrifle = std::wstring(L"advancedrifle");
		static auto specialcarbine = std::wstring(L"specialcarbine");
		static auto specialcarbine_mk2 = std::wstring(L"specialcarbine_mk2");
		static auto bullpuprifle = std::wstring(L"bullpuprifle");
		static auto bullpuprifle_mk2 = std::wstring(L"bullpuprifle_mk2");
		static auto compactrifle = std::wstring(L"compactrifle");
		static auto machine_gun = std::wstring(L"machine_gun");
		static auto combatmg = std::wstring(L"combatmg");
		static auto combatmg_mk2 = std::wstring(L"combatmg_mk2");
		static auto gusenberg = std::wstring(L"gusenberg");
		static auto sniperrifle = std::wstring(L"sniperrifle");
		static auto heavysniper = std::wstring(L"heavysniper");
		static auto heavysniper_mk2 = std::wstring(L"heavysniper_mk2");
		static auto marksmanrifle = std::wstring(L"marksmanrifle");
		static auto marksmanrifle_mk2 = std::wstring(L"marksmanrifle_mk2");
		static auto rpg = std::wstring(L"rpg");
		static auto grenadelauncher = std::wstring(L"grenadelauncher");
		static auto grenadelauncher_smoke = std::wstring(L"grenadelauncher_smoke");
		static auto minigun = std::wstring(L"minigun");
		static auto firework = std::wstring(L"firework");
		static auto railgun = std::wstring(L"railgun");
		static auto hominglauncher = std::wstring(L"hominglauncher");
		static auto compactlauncher = std::wstring(L"compactlauncher");
		static auto grenade = std::wstring(L"grenade");
		static auto bzgas = std::wstring(L"bzgas");
		static auto smokegrenade = std::wstring(L"smokegrenade");
		static auto flare = std::wstring(L"flare");
		static auto molotov = std::wstring(L"molotov");
		static auto stickybomb = std::wstring(L"stickybomb");
		static auto proxmine = std::wstring(L"proxmine");
		static auto snowball = std::wstring(L"snowball");
		static auto pipebomb = std::wstring(L"pipebomb");
		static auto ball = std::wstring(L"ball");
		static auto petrolcan = std::wstring(L"petrolcan");
		static auto fireextinguisher = std::wstring(L"fireextinguisher");
		static auto parachute = std::wstring(L"parachute");

		switch (hash)
		{
		case 0x92A27487:
			return dagger.c_str(); break;
		case 0x958A4A8F:
			return bat.c_str(); break;
		case 0xF9E6AA4B:
			return bottle.c_str(); break;
		case 0x84BD7BFD:
			return crowbar.c_str(); break;
		case 0xA2719263:
			return unarmed.c_str(); break;
		case 0x8BB05FD7:
			return flashlight.c_str(); break;
		case 0x440E4788:
			return golfclub.c_str(); break;
		case 0x4E875F73:
			return hammer.c_str(); break;
		case 0xF9DCBF2D:
			return hatchet.c_str(); break;
		case 0xD8DF3C3C:
			return knuckle.c_str(); break;
		case 0x99B507EA:
			return knife.c_str(); break;
		case 0xDD5DF8D9:
			return machete.c_str(); break;
		case 0xDFE37640:
			return switchblade.c_str(); break;
		case 0x678B81B1:
			return nightstick.c_str(); break;
		case 0x19044EE0:
			return wrench.c_str(); break;
		case 0xCD274149:
			return battleaxe.c_str(); break;
		case 0x94117305:
			return poolcue.c_str(); break;
		case 0x1B06D571:
			return pistol.c_str(); break;
		case 0xBFE256D4:
			return pistolmk2.c_str(); break;
		case 0x5EF9FEC4:
			return combatpistol.c_str(); break;
		case 0x22D8FE39:
			return appistol.c_str(); break;
		case 0x3656C8C1:
			return stungun.c_str(); break;
		case 0x99AEEB3B:
			return pistol50.c_str(); break;
		case 0xBFD21232:
			return snspistol.c_str(); break;
		case 0x88374054:
			return snspistolmk2.c_str(); break;
		case 0xD205520E:
			return heavypistol.c_str(); break;
		case 0x83839C4:
			return vintagepistol.c_str(); break;
		case 0x47757124:
			return flaregun.c_str(); break;
		case 0xDC4DB296:
			return marksmanpistol.c_str(); break;
		case 0xC1B3C3D1:
			return revolver.c_str(); break;
		case 0xCB96392F:
			return revolvermk2.c_str(); break;
		case 0x97EA20B8:
			return doubleaction.c_str(); break;
		case 0x13532244:
			return microsmg.c_str(); break;
		case 0x2BE6766B:
			return smg.c_str(); break;
		case 0x78A97CD0:
			return smgmk2.c_str(); break;
		case 0xEFE7E2DF:
			return assaultsmg.c_str(); break;
		case 0xA3D4D34:
			return combatpdw.c_str(); break;
		case 0xDB1AA450:
			return machinepistol.c_str(); break;
		case 0xBD248B55:
			return minismg.c_str(); break;
		case 0x1D073A89:
			return pumpshotgun.c_str(); break;
		case 0x555AF99A:
			return pumpshotgun_mk2.c_str(); break;
		case 0x7846A318:
			return sawnoffshotgun.c_str(); break;
		case 0xE284C527:
			return assaultshotgun.c_str(); break;
		case 0x9D61E50F:
			return bullpupshotgun.c_str(); break;
		case 0xA89CB99E:
			return musket.c_str(); break;
		case 0x3AABBBAA:
			return heavyshotgun.c_str(); break;
		case 0xEF951FBB:
			return dbshotgun.c_str(); break;
		case 0x12E82D3D:
			return autoshotgun.c_str(); break;
		case 0xBFEFFF6D:
			return assaultrifle.c_str(); break;
		case 0x394F415C:
			return assaultrifle_mk2.c_str(); break;
		case 0x83BF0278:
			return carbinerifle.c_str(); break;
		case 0xFAD1F1C9:
			return carbinerifle_mk2.c_str(); break;
		case 0xAF113F99:
			return advancedrifle.c_str(); break;
		case 0xC0A3098D:
			return specialcarbine.c_str(); break;
		case 0x969C3D67:
			return specialcarbine_mk2.c_str(); break;
		case 0x7F229F94:
			return bullpuprifle.c_str(); break;
		case 0x84D6FAFD:
			return bullpuprifle_mk2.c_str(); break;
		case 0x624FE830:
			return compactrifle.c_str(); break;
		case 0x9D07F764:
			return machine_gun.c_str(); break;
		case 0x7FD62962:
			return combatmg.c_str(); break;
		case 0xDBBD7280:
			return combatmg_mk2.c_str(); break;
		case 0x61012683:
			return gusenberg.c_str(); break;
		case 0x5FC3C11:
			return sniperrifle.c_str(); break;
		case 0xC472FE2:
			return heavysniper.c_str(); break;
		case 0xA914799:
			return heavysniper_mk2.c_str(); break;
		case 0xC734385A:
			return marksmanrifle.c_str(); break;
		case 0x6A6C02E0:
			return marksmanrifle_mk2.c_str(); break;
		case 0xB1CA77B1:
			return rpg.c_str(); break;
		case 0xA284510B:
			return grenadelauncher.c_str(); break;
		case 0x4DD2DC56:
			return grenadelauncher_smoke.c_str(); break;
		case 0x42BF8A85:
			return minigun.c_str(); break;
		case 0x7F7497E5:
			return firework.c_str(); break;
		case 0x6D544C99:
			return railgun.c_str(); break;
		case 0x63AB0442:
			return hominglauncher.c_str(); break;
		case 0x781FE4A:
			return compactlauncher.c_str(); break;
		case 0x93E220BD:
			return grenade.c_str(); break;
		case 0xA0973D5E:
			return bzgas.c_str(); break;
		case 0xFDBC8A50:
			return smokegrenade.c_str(); break;
		case 0x497FACC3:
			return flare.c_str(); break;
		case 0x24B17070:
			return molotov.c_str(); break;
		case 0x2C3731D9:
			return stickybomb.c_str(); break;
		case 0xAB564B93:
			return proxmine.c_str(); break;
		case 0x787F0BB:
			return snowball.c_str(); break;
		case 0xBA45E8B8:
			return pipebomb.c_str(); break;
		case 0x23C9F95C:
			return ball.c_str(); break;
		case 0x34A67B97:
			return petrolcan.c_str(); break;
		case 0x60EC506:
			return fireextinguisher.c_str(); break;
		case 0xFBAB5776:
			return parachute.c_str(); break;
		default:
			return unarmed.c_str(); break;
		}
	}
}