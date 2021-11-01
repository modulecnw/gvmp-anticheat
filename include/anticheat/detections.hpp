#pragma once
#include "imports.hpp"

#define ANTICHEAT
using namespace std;

class anticheat_detections : public c_singleton<anticheat_detections>
{
private:
	typedef LONG(WINAPI* nt_protect_virtual_memory_t)(IN HANDLE process_handle, IN OUT PVOID* base_address, IN OUT PULONG number_of_bytes_to_protect, IN ULONG new_access_protection, OUT PULONG old_access_protection);
	typedef BOOL(WINAPI* disable_thread_library_calls_t)(_In_ HMODULE lib_module);
	typedef HANDLE(WINAPI* create_file_t)(_In_ LPCWSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile);
	typedef FILE* (__cdecl* fs_open_t)(_In_z_ char const* _FileName, _In_z_ char const* _Mode, _In_ int _ShFlag);
public:
	typedef enum _DetectionTypes {
		DETECTION_UNKNOWN = 1,
		DETECTION_DISABLE_THREAD_LIBRARY_CALLS,
		DETECTION_CREATE_FILE,
		DETECTION_FS_OPEN
	};

	nt_protect_virtual_memory_t o_nt_protect_virtual_memory = nullptr;
	disable_thread_library_calls_t o_disable_thread_library_calls = nullptr;
	create_file_t o_create_file = nullptr;
	fs_open_t o_fs_open = nullptr;

	void run_service();
	const char* detection_to_string(_DetectionTypes detection_type);
	void detect_by_type(_DetectionTypes detection_type, const char* detection_info = "");
};