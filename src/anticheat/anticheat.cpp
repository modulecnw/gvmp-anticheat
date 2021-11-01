#include <anticheat\anticheat.hpp>

LONG WINAPI hook_nt_protect_virtual_memory(IN HANDLE process_handle, IN OUT PVOID* base_address, IN OUT PULONG number_of_bytes_to_protect, IN ULONG new_access_protection, OUT PULONG old_access_protection) {
	/*
	 * basic hooking
	 */

	 // inform about every nt_protect_virtual_memory call
	Log::Info("===================");
	Log::Info(process_handle, base_address);
	Log::Info(number_of_bytes_to_protect, new_access_protection);
	Log::Info(old_access_protection);
	Log::Info("===================");

	if (new_access_protection >= 0x40) {
		DWORD64 current_tick = GetTickCount64();

		static DWORD64 current_tick_detection = 0x0;
		static DWORD64 latest_tick_detection = 0x0;

		/*
		 * virtualprotect gets called by gta5 himself too
		 * but not that often.
		 * if it spams = cheat!
		 */
		if ((current_tick_detection - latest_tick_detection) > 2000) {
			Log::Error("Detected forbidden module.");

			latest_tick_detection = current_tick_detection;
		}
		current_tick_detection = current_tick;
	}

	return anticheat_main::get().o_nt_protect_virtual_memory(process_handle, base_address, number_of_bytes_to_protect, new_access_protection, old_access_protection);
}

void anticheat_main::run_service()
{
	/*
	 * These are just basic tests (poc).
	 * TODO: create classes for hooking & other stuff.
	 */
	HMODULE module_handle_ntdll = GetModuleHandleA("ntdll.dll");

	nt_protect_virtual_memory_t nt_protect_virtual_memory = (nt_protect_virtual_memory_t)GetProcAddress(module_handle_ntdll, "NtProtectVirtualMemory");

	auto hooking_status = MH_CreateHook(nt_protect_virtual_memory, &hook_nt_protect_virtual_memory, reinterpret_cast<LPVOID*>(&o_nt_protect_virtual_memory));
	if (hooking_status != MH_OK)
		Log::Error("Failed to create hook / NtProtectVirtualMemory", MH_StatusToString(hooking_status));

	if (MH_EnableHook(nt_protect_virtual_memory) != MH_OK)
		Log::Error("Failed to enable hook / NtProtectVirtualMemory");
	else
		Log::Debug("Successfully enabled protection.");
}