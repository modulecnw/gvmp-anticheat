#pragma once
#include "imports.hpp"

using namespace std;

class security : public c_singleton<security>
{
private:
	enum thread_info_class { thread_hide_from_debugger = 0x11 };
	
	typedef NTSTATUS(__stdcall* nt_query_information_process_t)(_In_ HANDLE, _In_  unsigned int, _Out_ PVOID, _In_ ULONG, _Out_ PULONG);
	typedef NTSTATUS(__stdcall* nt_set_information_thread_t)(_In_ HANDLE, _In_ thread_info_class, _In_ PVOID, _In_ ULONG);

	void check_debug_string();
public:
	void initialize();
	void hide_thread();
	void check_heartbeart();
};