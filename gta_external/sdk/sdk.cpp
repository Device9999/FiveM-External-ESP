#include "sdk.hpp"

D3DXVECTOR3 sdk::get_bone_position(uintptr_t ped_ptr, int bone_id) {
	auto matrix = c_mem::get()->read_mem<D3DXMATRIX>(ped_ptr + 0x60);
	auto bone = c_mem::get()->read_mem<D3DXVECTOR3>(ped_ptr + (0x430 + bone_id * 0x10));
	D3DXVECTOR4 transform;
	D3DXVec3Transform(&transform, &bone, &matrix);
	return D3DXVECTOR3(transform.x, transform.y, transform.z);
}

sdk::c_replay_interface::c_replay_interface(const uintptr_t base)
{
	ZeroMemory(&this->replay_interface, sizeof(this->replay_interface));
	ZeroMemory(&this->replay_pedlist_interface_ptr, sizeof(this->replay_pedlist_interface_ptr));
	ZeroMemory(&this->replay_objectlist_interface_ptr, sizeof(this->replay_objectlist_interface_ptr));

	this->base = base;
	this->replay_interface = c_mem::get()->read_mem<replay_interface_t>(this->base);

	if (this->replay_interface.PedList)
		this->replay_pedlist_interface_ptr = c_mem::get()->read_mem<ped_replay_interface_ptr_t>(this->replay_interface.PedList);

	if (this->replay_interface.object_list)
		this->replay_objectlist_interface_ptr = c_mem::get()->read_mem<object_replay_interface_ptr_t>(this->replay_interface.object_list);
}

sdk::c_ped::c_ped(const uintptr_t base)
{
	ZeroMemory(&this->pedestrian, sizeof(this->pedestrian));
	ZeroMemory(&this->playerinfo, sizeof(this->playerinfo));

	this->base = base;
	/*read base struct*/
	this->pedestrian = c_mem::get()->read_mem<ped_t>(this->base);
	if (this->pedestrian.player_info_ptr)
		this->playerinfo = c_mem::get()->read_mem<playerinfo_t>(this->pedestrian.player_info_ptr);
}