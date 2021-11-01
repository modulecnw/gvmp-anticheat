#include <anticheat\anticheat.hpp>

LONG WINAPI hook_nt_protect_virtual_memory(IN HANDLE process_handle, IN OUT PVOID* base_address, IN OUT PULONG number_of_bytes_to_protect, IN ULONG new_access_protection, OUT PULONG old_access_protection) {
	/*
	 * basic hooking
	 */

	 // inform about every nt_protect_virtual_memory call
	 // Log::Info("===================");
	 // Log::Info(process_handle, base_address);
	 // Log::Info(number_of_bytes_to_protect, new_access_protection);
	 // Log::Info(old_access_protection);
	 // Log::Info("===================");

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
			Log::Error("[VP] Detected forbidden module.");

			latest_tick_detection = current_tick_detection;
		}
		current_tick_detection = current_tick;
	}

	return anticheat_main::get().o_nt_protect_virtual_memory(process_handle, base_address, number_of_bytes_to_protect, new_access_protection, old_access_protection);
}

BOOL WINAPI hook_disable_thread_library_calls(_In_ HMODULE lib_module) {
	Log::Error("[DTLC] Detected forbidden module.");

	return anticheat_main::get().o_disable_thread_library_calls(lib_module);
}

HANDLE WINAPI hook_create_file(_In_ LPCWSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile) {
	// inform about every CreateFileW call

	wstring w_string(lpFileName);
	string file_name = string(w_string.begin(), w_string.end());

	if (file_name.find(".ini") != std::string::npos) {
		if (file_name.find("ReShade") == std::string::npos) {
			// Bei 0xCheats wird beim Injecten CreateFile gecalled.
			// In dieser INI Datei liegen dann Daten über dem Spieler.
			// Nur Gott weiß warum gleichzeitig dann auch dasselbe bei ReShade gecalled wird.

			Log::Error("[CREATE_FILE] Detected forbidden module.");
		}
	}

	return anticheat_main::get().o_create_file(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

void anticheat_main::run_service()
{
	/*
	 * These are just basic tests (poc).
	 * TODO: create classes for hooking & other stuff.
	 */

	 // derzeit raus damit ich in ruhe das anticheat injecten kann aller
	 /*HMODULE module_handle_ntdll = GetModuleHandleA("ntdll.dll");
	 nt_protect_virtual_memory_t nt_protect_virtual_memory = (nt_protect_virtual_memory_t)GetProcAddress(module_handle_ntdll, "NtProtectVirtualMemory");

	 auto hooking_status = MH_CreateHook(nt_protect_virtual_memory, &hook_nt_protect_virtual_memory, reinterpret_cast<LPVOID*>(&o_nt_protect_virtual_memory));
	 if (hooking_status != MH_OK)
		 Log::Error("Failed to create hook / NtProtectVirtualMemory", MH_StatusToString(hooking_status));

	 if (MH_EnableHook(nt_protect_virtual_memory) != MH_OK)
		 Log::Error("Failed to enable hook / NtProtectVirtualMemory");
	 else
		 Log::Debug("Successfully enabled protection.");*/

	auto hooking_status = MH_CreateHook(&DisableThreadLibraryCalls, &hook_disable_thread_library_calls, reinterpret_cast<LPVOID*>(&o_disable_thread_library_calls));
	if (hooking_status != MH_OK)
		Log::Error("Failed to create hook / DisableThreadLibraryCalls", MH_StatusToString(hooking_status));

	if (MH_EnableHook(&DisableThreadLibraryCalls) != MH_OK)
		Log::Error("Failed to enable hook / DisableThreadLibraryCalls");
	else
		Log::Debug("Successfully enabled protection.");

	auto hooking_status_2 = MH_CreateHook(&CreateFileW, &hook_create_file, reinterpret_cast<LPVOID*>(&o_create_file));
	if (hooking_status_2 != MH_OK)
		Log::Error("Failed to create hook / CreateFileW", MH_StatusToString(hooking_status_2));

	if (MH_EnableHook(&CreateFileW) != MH_OK)
		Log::Error("Failed to enable hook / CreateFileW");
	else
		Log::Debug("Successfully enabled protection.");
}