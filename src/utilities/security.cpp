#include <utilities\security.hpp>

bool security::initialize()
{
	HMODULE h_ntdll = LoadLibraryA("ntdll.dll");
	if (h_ntdll == INVALID_HANDLE_VALUE || h_ntdll == NULL) return false;

	nt_query_information_process = (nt_query_information_process_t)GetProcAddress(h_ntdll, "NtQueryInformationProcess");

	return true;
}

void security::hide_current_thread()
{
	if (nt_query_information_process == NULL) return;

	nt_query_information_process(GetCurrentThread(), 0x11, 0, 0, 0); // 0x11 = HIDE_THREAD_FROM_DEBUGGER
}
