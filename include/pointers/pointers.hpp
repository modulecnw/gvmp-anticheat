#pragma once
#include "imports.hpp"
#include "module.hpp"
#include "scanner.hpp"

#include <gta/game_classes.hpp>

using namespace std;
class pointers : public c_singleton<pointers>
{
public:
	/* typedefs*/
	using event_gun_shot_t = __int64(*)(__int64 a1, __int64* a2);
	using pointer_to_handle_t = int32_t(*)(void* ptr);

	memory::module_t gta5_module = memory::module_t(nullptr);
	memory::module_t ragemp_module = memory::module_t(nullptr);

	game_state_t* ptr_gta_game_state = nullptr;
	CWorldFactory* ptr_gta_world_factory = nullptr;
	CViewPort* ptr_gta_viewport = nullptr;
	uintptr_t ptr_gta_camera = 0;
	pointer_to_handle_t ptr_gta_pointer_to_handle = nullptr;
	event_gun_shot_t ptr_gta_event_shot = nullptr;

	void initialize();
};
