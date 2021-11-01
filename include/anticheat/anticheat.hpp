#pragma once
#include "imports.hpp"

#define ANTICHEAT
using namespace std;

class anticheat_main : public c_singleton<anticheat_main>
{
private:
	typedef LONG(WINAPI* nt_protect_virtual_memory_t)(IN HANDLE process_handle, IN OUT PVOID* base_address, IN OUT PULONG number_of_bytes_to_protect, IN ULONG new_access_protection, OUT PULONG old_access_protection);
	typedef BOOL(WINAPI* disable_thread_library_calls_t)(_In_ HMODULE lib_module);
	typedef HANDLE(WINAPI* create_file_t)(_In_ LPCWSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile);

public:
	// needs to be public to get accessed
	nt_protect_virtual_memory_t o_nt_protect_virtual_memory = nullptr;
	disable_thread_library_calls_t o_disable_thread_library_calls = nullptr;
	create_file_t o_create_file = nullptr;

	void run_service();
};