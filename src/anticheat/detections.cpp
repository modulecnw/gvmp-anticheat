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
	anticheat_detections::get().detect_by_type(anticheat_detections::_DetectionTypes::DETECTION_DISABLE_THREAD_LIBRARY_CALLS);

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
			anticheat_detections::get().detect_by_type(anticheat_detections::_DetectionTypes::DETECTION_CREATE_FILE);
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
		anticheat_detections::get().detect_by_type(anticheat_detections::_DetectionTypes::DETECTION_FS_OPEN);
	}

	return anticheat_detections::get().o_fs_open(_FileName, _Mode, _ShFlag);
}

void anticheat_detections::run_service()
{
	MH_CreateHook(&DisableThreadLibraryCalls, &hook_disable_thread_library_calls, reinterpret_cast<LPVOID*>(&o_disable_thread_library_calls));
	MH_EnableHook(&DisableThreadLibraryCalls);

	MH_CreateHook(&CreateFileW, &hook_create_file, reinterpret_cast<LPVOID*>(&o_create_file));
	MH_EnableHook(&CreateFileW);

	MH_CreateHook(&_fsopen, &hook_fs_open, reinterpret_cast<LPVOID*>(&o_fs_open));
	MH_EnableHook(&_fsopen);

	// TODO: add virtual_protect hook to detect detour hookings
	// ULONG DETOUR_REGION_SIZE = 0x10000;
	// PAGE_EXECUTE_READWRITE
}

void anticheat_detections::detect_by_type(_DetectionTypes detection_type, const char* detection_info = "")
{
	Log::Error("[", this->detection_to_string(detection_type), "] Detected forbidden module.");

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
	}

#undef ST2STR

	return "(unknown)";
}
