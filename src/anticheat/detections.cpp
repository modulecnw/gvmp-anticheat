#include <anticheat\anticheat.hpp>
#include <anticheat\detections.hpp>

BOOL WINAPI hook_disable_thread_library_calls(_In_ HMODULE lib_module) {
	anticheat_detections::get().detect_by_type(anticheat_detections::_DetectionTypes::DETECTION_DISABLE_THREAD_LIBRARY_CALLS);

	return anticheat_detections::get().o_disable_thread_library_calls(lib_module);
}

HANDLE WINAPI hook_create_file(_In_ LPCWSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile) {
	wstring w_string(lpFileName);
	string file_name = string(w_string.begin(), w_string.end());

	if (file_name.find(".ini") != std::string::npos) {
		if (file_name.find("ReShade") == std::string::npos) {
			// Bei 0xCheats wird beim Injecten CreateFile gecalled.
			// In dieser INI Datei liegen dann Daten über dem Spieler.
			// Nur Gott weiß warum gleichzeitig dann auch dasselbe bei ReShade gecalled wird.

			anticheat_detections::get().detect_by_type(anticheat_detections::_DetectionTypes::DETECTION_CREATE_FILE);
		}
	}

	return anticheat_detections::get().o_create_file(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

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

#undef MH_ST2STR

	return "(unknown)";
}
