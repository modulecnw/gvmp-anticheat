#pragma once
#include "imports.hpp"
#include <SubAuth.h>

using namespace std;

class security : public c_singleton<security>
{
private:
	typedef NTSTATUS(__stdcall* nt_query_information_process_t)(_In_ HANDLE, _In_  unsigned int, _Out_ PVOID, _In_ ULONG, _Out_ PULONG);
	typedef NTSTATUS(__stdcall* nt_set_information_thread_t)(_In_ HANDLE, _In_ THREAD_INFORMATION_CLASS, _In_ PVOID, _In_ ULONG);

	nt_query_information_process_t nt_query_information_process = NULL;

public:
	bool initialize();
	void hide_current_thread();
	void unlink_peb_headers(HMODULE module);
};