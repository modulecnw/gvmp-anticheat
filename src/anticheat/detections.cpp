#include <anticheat\anticheat.hpp>
#include <anticheat\detections.hpp>

/**
 * Detection-Rate: 100%
 * False-Flag Rate: 0-0.5%
 *
 * Before any cheat creates their thread, they call 'DisableThreadLibraryCalls'.
 * Currently only tested during runtime. Needs to be tested at game start to see how it behaves.
 */
BOOL WINAPI hook_disable_thread_library_calls(_In_ HMODULE lib_module) {
	char module_file_name[MAX_PATH] = { 0 };
	GetModuleFileNameA(lib_module, module_file_name, MAX_PATH);

	std::string string_module_file_name = std::string(module_file_name);

	if (string_module_file_name.find("COMCTL32.dll") == std::string::npos && string_module_file_name.find("XAudio2_7.dll") == std::string::npos)
		anticheat_detections::get().detect_by_type(anticheat_detections::_DetectionTypes::DETECTION_DISABLE_THREAD_LIBRARY_CALLS, string_module_file_name);

	return anticheat_detections::get().o_disable_thread_library_calls(lib_module);
}


/**
 * Detection-Rate: 50-60%
 * False-Flag Rate: 0-5%
 *
 * Some cheats create a file to pass data from loader to client.
 * NVIDIA & ReShade may also this.
 */
HANDLE WINAPI hook_create_file(_In_ LPCWSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile) {
	wstring w_string(lpFileName);
	string file_name = string(w_string.begin(), w_string.end());

	if (file_name.find(".ini") != std::string::npos) {
		if (file_name.find("ReShade") == std::string::npos) {
			anticheat_detections::get().detect_by_type(anticheat_detections::_DetectionTypes::DETECTION_CREATE_FILE, file_name);
		}
	}

	return anticheat_detections::get().o_create_file(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

/**
 * Detection-Rate: 95%
 * False-Flag Rate: 0%
 *
 * Detects loading & writing any types of config or authentification files.
 * Usually theres no module who uses std::ifstream.
 */
FILE* __cdecl hook_fs_open(_In_z_ char const* _FileName, _In_z_ char const* _Mode, _In_ int _ShFlag) {
	string file_name = _FileName;

	if (file_name.find(".ini") != std::string::npos || file_name.find(".token") != std::string::npos || file_name.find(".cfg") != std::string::npos) {
		anticheat_detections::get().detect_by_type(anticheat_detections::_DetectionTypes::DETECTION_FS_OPEN, file_name);
	}

	return anticheat_detections::get().o_fs_open(_FileName, _Mode, _ShFlag);
}

HWND WINAPI hook_create_window(_In_ DWORD ex_style, _In_opt_ LPCSTR class_name, _In_opt_ LPCSTR window_name, _In_ DWORD style, _In_ int x, _In_ int y, _In_ int width, _In_ int height, _In_opt_ HWND parent, _In_opt_ HMENU menu, _In_opt_ HINSTANCE instance, _In_opt_ LPVOID param) {
	auto result = anticheat_detections::get().o_create_window(ex_style, class_name, window_name, style, x, y, width, height, parent, menu, instance, param);
	if (class_name == NULL) return result;

	std::string string_window_name(class_name);

	if (string_window_name != "DXGIWatchdogThreadWindow" && string_window_name != "D3DProxyWindow")
		anticheat_detections::get().detect_by_type(anticheat_detections::_DetectionTypes::DETECTION_CREATE_WINDOW, string_window_name);

	return result;
}

BOOL WINAPI hook_flush_instruction_cache(_In_ HANDLE process, _In_reads_bytes_opt_(size) LPCVOID base_address, _In_ SIZE_T size) {
	uintptr_t blacklisted_hooks[] = {
		(uintptr_t)GetModuleHandleA(NULL) + 0x6770
	};

	for (auto target_hook : blacklisted_hooks) {
		if ((uintptr_t)base_address == target_hook) {
			anticheat_detections::get().detect_by_type(anticheat_detections::_DetectionTypes::DETECTION_MINHOOK_FLUSH_CACHE);

			break;
		}
	}

#if DEBUG
	Log::Error("===================");
	Log::Error(process, base_address);
	Log::Error(size);
	Log::Error("===================");
#endif

	return anticheat_detections::get().o_flush_instruction_cache(process, base_address, size);
}

/**
 * Detection-Rate: 100%
 * False-Flag Rate: 0%
 *
 * Detects standard LoadLibrary injections.
 * Example: GH-Injector, Xenos-64, etc.
 */
NTSTATUS NTAPI main_dll_manifest_prober_callback(IN HMODULE dll_base, IN PCWSTR full_dll_path, OUT PHANDLE activation_context) {
	DWORD64 current_tick = GetTickCount64();

	static DWORD64 current_tick_prober_callback = 0x0;
	static DWORD64 latest_tick_prober_callback = 0x0;

	if ((current_tick_prober_callback - latest_tick_prober_callback) > 4 * 1000) {
		anticheat_detections::get().detect_by_type(anticheat_detections::_DetectionTypes::DETECTION_DLL_MANIFEST_PROBER_CALLBACK);

		latest_tick_prober_callback = current_tick_prober_callback;
	}
	current_tick_prober_callback = current_tick;

	if (!*activation_context) return STATUS_INVALID_PARAMETER;

	HANDLE actx = NULL;
	ACTCTXW act = { 0 };

	act.cbSize = sizeof(act);
	act.dwFlags = ACTCTX_FLAG_RESOURCE_NAME_VALID | ACTCTX_FLAG_HMODULE_VALID;
	act.lpSource = full_dll_path;
	act.hModule = dll_base;

	*activation_context = 0;

	actx = CreateActCtxW(&act);

	if (actx == INVALID_HANDLE_VALUE) return 0xC0000234;
	*activation_context = actx;

	return 0x0;
}

void anticheat_detections::run_service()
{

	MH_CreateHook(&DisableThreadLibraryCalls, &hook_disable_thread_library_calls, reinterpret_cast<LPVOID*>(&o_disable_thread_library_calls));
	MH_EnableHook(&DisableThreadLibraryCalls);

	MH_CreateHook(&CreateFileW, &hook_create_file, reinterpret_cast<LPVOID*>(&o_create_file));
	MH_EnableHook(&CreateFileW);

	MH_CreateHook(&_fsopen, &hook_fs_open, reinterpret_cast<LPVOID*>(&o_fs_open));
	MH_EnableHook(&_fsopen);

	MH_CreateHook(&FlushInstructionCache, &hook_flush_instruction_cache, reinterpret_cast<LPVOID*>(&o_flush_instruction_cache));
	MH_EnableHook(&FlushInstructionCache);

	MH_CreateHook(&CreateWindowExA, &hook_create_window, reinterpret_cast<LPVOID*>(&o_create_window));
	MH_EnableHook(&CreateWindowExA);

	// LoadLibrary Detection
	// Funktioniert zwar perfekt, aber verträgt sich nicht gut mit dem Renderer :(
	//		auto ldr_set_dll_manifest_prober = GetProcAddress(GetModuleHandleA("ntdll.dll"), "LdrSetDllManifestProber");
	//		if (ldr_set_dll_manifest_prober != NULL) reinterpret_cast<ldr_set_dll_manifest_prober_t>(ldr_set_dll_manifest_prober)(&main_dll_manifest_prober_callback, NULL, &ReleaseActCtx);

	// TODO: add virtual_protect hook to detect detour hookings
	// ULONG DETOUR_REGION_SIZE = 0x10000;
	// PAGE_EXECUTE_READWRITE
}

void anticheat_detections::detect_by_type(_DetectionTypes detection_type) {
	Log::Error("[", this->detection_to_string(detection_type), "] Detected forbidden module.");

	// TODO: send detection to server etc.
	// >:(
}

void anticheat_detections::detect_by_type(_DetectionTypes detection_type, std::string optional_information) {
	Log::Error("[", this->detection_to_string(detection_type), "] Detected forbidden module.");

	if (optional_information.length() > 0)
		Log::Error("[", this->detection_to_string(detection_type), "] Information:", optional_information);

	// TODO: send detection to server etc.
	// >:(
}

const char* anticheat_detections::detection_to_string(_DetectionTypes detection_type)
{
#define ST2STR(x)    \
    case x:             \
        return #x;

	switch (detection_type) {
		ST2STR(DETECTION_UNKNOWN)
			ST2STR(DETECTION_DISABLE_THREAD_LIBRARY_CALLS)
			ST2STR(DETECTION_CREATE_FILE)
			ST2STR(DETECTION_FS_OPEN)
			ST2STR(DETECTION_DLL_MANIFEST_PROBER_CALLBACK)
			ST2STR(DETECTION_MINHOOK_FLUSH_CACHE)
			ST2STR(DETECTION_CREATE_WINDOW)
			ST2STR(DETECTION_ANTICHEAT_SECURITY)
	}

#undef ST2STR

	return "(unknown)";
}
