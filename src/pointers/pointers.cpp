#include <pointers\pointers.hpp>

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

	this->ptr_gta_game_state = as_relative<game_state_t*>(find_pattern(this->gta5_module, "Game-State", "48 85 C9 74 4B 83 3D"), 7);
	this->ptr_gta_world_factory = as_relative<CWorldFactory*>(find_pattern(this->gta5_module, "WorldFactory", "48 8B C3 48 83 C4 20 5B C3 0F B7 05 ? ? ? ?", -11));
	this->ptr_gta_viewport = *as_relative<CViewPort**>(find_pattern(this->gta5_module, "Viewport", "48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD"));
	this->ptr_gta_camera = as_relative<uintptr_t>(find_pattern(this->gta5_module, "Camera", "48 8B 05 ? ? ? ? 48 8B 98 ? ? ? ? EB"));
	this->ptr_gta_pointer_to_handle = find_pattern<pointer_to_handle_t>(this->gta5_module, "PointerToHandle", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB");
}
