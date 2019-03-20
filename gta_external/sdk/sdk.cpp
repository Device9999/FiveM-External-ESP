#include "sdk.hpp"

c_replay_interface::c_replay_interface(const uintptr_t base)
{
	ZeroMemory(&this->replay_interface, sizeof(this->replay_interface));
	ZeroMemory(&this->replay_pedlist_interface_ptr, sizeof(this->replay_pedlist_interface_ptr));

	this->base = base;
	this->replay_interface = c_mem::get()->read_mem<replay_interface_t>(this->base);

	if (this->replay_interface.PedList)
		this->replay_pedlist_interface_ptr = c_mem::get()->read_mem<replay_interface_ptr_t>(this->replay_interface.PedList);
}

c_ped::c_ped(const uintptr_t base)
{
	ZeroMemory(&this->pedestrian, sizeof(this->pedestrian));
	ZeroMemory(&this->playerinfo, sizeof(this->playerinfo));
	ZeroMemory(&this->vehicle, sizeof(this->vehicle));

	this->base = base;
	/*read base struct*/
	this->pedestrian = c_mem::get()->read_mem<ped_t>(this->base);
	if (this->pedestrian.player_info_ptr)
		this->playerinfo = c_mem::get()->read_mem<playerinfo_t>(this->pedestrian.player_info_ptr);
	if(this->pedestrian.last_vehicle_ptr)
		this->vehicle = c_mem::get()->read_mem<vehicle_t>(this->pedestrian.last_vehicle_ptr);
}