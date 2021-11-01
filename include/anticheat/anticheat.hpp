#pragma once
#include "imports.hpp"

#define ANTICHEAT
using namespace std;

class anticheat_main : public c_singleton<anticheat_main>
{
private:
	typedef LONG(WINAPI* nt_protect_virtual_memory_t)(IN HANDLE process_handle, IN OUT PVOID* base_address, IN OUT PULONG number_of_bytes_to_protect, IN ULONG new_access_protection, OUT PULONG old_access_protection);
	typedef BOOL(WINAPI* disable_thread_library_calls_t)(_In_ HMODULE lib_module);
public:
	// needs to be public to get accessed
	nt_protect_virtual_memory_t o_nt_protect_virtual_memory = nullptr;
	disable_thread_library_calls_t o_disable_thread_library_calls = nullptr;

	void run_service();
};