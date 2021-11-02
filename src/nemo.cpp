#include "nemo.hpp"
#include "networking/networking.hpp"
#include "anticheat/anticheat.hpp"
#include "renderer/renderer.hpp"
#include "pointers/pointers.hpp"

void nemo_ac::run_service()
{
	Log::Debug(_xor_("nemo:V Anti-Cheat started."));

	// Networking stay disabled until server communication is done
	// networking::get().start();
	pointers::get().initialize();
	renderer::get().initialize();
	anticheat_main::get().run_service();
}


void nemo_ac::shutdown_service()
{
	Log::Error(_xor_("nemo:V Anti-Cheat shutdown."));

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}