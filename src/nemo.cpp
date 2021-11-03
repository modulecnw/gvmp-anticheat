#include "nemo.hpp"
#include "networking/networking.hpp"
#include "anticheat/anticheat.hpp"
#include "renderer/renderer.hpp"
#include "pointers/pointers.hpp"
#include "utilities/security.hpp"

void nemo_ac::run_service(HMODULE module)
{
	Log::Debug(_xor_("nemo:V Anti-Cheat started."));
	security::get().hide_thread();

	// initialize security in own thread
	std::thread([]() {
		security::get().hide_thread();
		security::get().initialize();
	}).detach();

	pointers::get().initialize();
	//renderer::get().initialize();
	anticheat_main::get().run_service();
}


void nemo_ac::shutdown_service()
{
	Log::Error(_xor_("nemo:V Anti-Cheat shutdown."));

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}