#include <pointers\pointers.hpp>
#include <Psapi.h>

using namespace memory;

void pointers::initialize()
{
	this->gta5_module = memory::module_t(nullptr);
	this->ragemp_module = memory::module_t("multiplayer.dll");

	if (!this->ragemp_module.base()) {
		MessageBoxA(0, "Es ist ein Fehler aufgetreten. Bitte starte das Spiel neu!", "GVMP Anti-Cheat", 0);
		exit(0);

		return;
	}

	//TODO: _xor_ all strings

	this->ptr_gta_game_state = as_relative<game_state_t*>(find_pattern(this->gta5_module, "Game-State", "48 85 C9 74 4B 83 3D"), 7);
	this->ptr_gta_world_factory = as_relative<CWorldFactory*>(find_pattern(this->gta5_module, "WorldFactory", "48 8B C3 48 83 C4 20 5B C3 0F B7 05 ? ? ? ?", -0xB));
	this->ptr_gta_viewport = *as_relative<CViewPort**>(find_pattern(this->gta5_module, "Viewport", "48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD"));
	this->ptr_gta_camera = as_relative<uintptr_t>(find_pattern(this->gta5_module, "Camera", "48 8B 05 ? ? ? ? 48 8B 98 ? ? ? ? EB"));
	this->ptr_gta_get_bone_position = find_pattern<get_bone_position_t>(this->gta5_module, "GetBone", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 60 48 8B 01 41 8B E8 48 8B F2 48 8B F9 33 DB");
	this->ptr_gta_world_to_screen = find_pattern<world_to_screen_t>(this->gta5_module, "WorldToScreen", "48 89 5C 24 ? 55 56 57 48 83 EC 70 65 4C 8B 0C 25 ? 00 00 00 8B");
	this->ptr_gta_pointer_to_handle = find_pattern<pointer_to_handle_t>(this->gta5_module, "PointerToHandle", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB");

	this->ptr_ragemp_get_name = find_pattern<std::string*>(this->ragemp_module, "PlayerName", "70 78 46 ? 70 78 46 ? 40 1C 45 ? FF ? ?", 0xF);

	// dauert lange, da er alle module durchscannt  :p
	//if (find_pattern_outside_module<uintptr_t>("0xCheats", "E8 ? ? ? ? 41 52 49 89 E2") != 0)
	//	Log::Info("FOUND");
	// find_pattern_outside_module<uintptr_t>("Hags", "65 6E 65 6D 79 5F 76 69");
}
