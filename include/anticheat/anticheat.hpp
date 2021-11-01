#pragma once
#include "imports.hpp"

#define ANTICHEAT
using namespace std;

class anticheat_main : public c_singleton<anticheat_main>
{
private:
	typedef LONG(WINAPI* nt_protect_virtual_memory_t)(IN HANDLE process_handle, IN OUT PVOID* base_address, IN OUT PULONG number_of_bytes_to_protect, IN ULONG new_access_protection, OUT PULONG old_access_protection);
public:
	// needs to be public to get accessed
	nt_protect_virtual_memory_t o_nt_protect_virtual_memory = nullptr;

	void run_service();
};