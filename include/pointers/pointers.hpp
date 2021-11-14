#pragma once
#include "imports.hpp"
#include "module.hpp"
#include "scanner.hpp"

#include <gta/game_classes.hpp>

#include <Psapi.h>
#pragma comment (lib,"psapi.lib")

using namespace std;
class pointers : public c_singleton<pointers>
{
public:
	/* typedefs*/
	using event_gun_shot_t = __int64(*)(__int64 a1, __int64* a2);
	using get_bone_position_t = void*(__fastcall*)(__int64 ped, __int64 pos_out, int32_t bone);
	using world_to_screen_t = bool(__fastcall*)(Vector3* world_position, float* out_x, float* out_y);
	using pointer_to_handle_t = int32_t(*)(void* ptr);

	memory::module_t gta5_module = memory::module_t(nullptr);
	memory::module_t ragemp_module = memory::module_t(nullptr);

	game_state_t* ptr_gta_game_state = nullptr;
	CWorldFactory* ptr_gta_world_factory = nullptr;
	CViewPort* ptr_gta_viewport = nullptr;
	uintptr_t ptr_gta_camera = 0;
	get_bone_position_t ptr_gta_get_bone_position = nullptr;
	world_to_screen_t ptr_gta_world_to_screen = nullptr;
	pointer_to_handle_t ptr_gta_pointer_to_handle = nullptr;
	event_gun_shot_t ptr_gta_event_shot = nullptr;
	std::string* ptr_ragemp_get_name = nullptr;

	void initialize();
};
