#include <utilities\security.hpp>

void security::hide_thread() {
	HMODULE h_ntdll = GetModuleHandleA("ntdll.dll");
	if (h_ntdll == INVALID_HANDLE_VALUE || h_ntdll == NULL) return;

	auto nt_set_information_thread = GetProcAddress(h_ntdll, "NtSetInformationThread");
	if (nt_set_information_thread != NULL) reinterpret_cast<nt_set_information_thread_t>(nt_set_information_thread)(GetCurrentThread(), thread_hide_from_debugger, 0, 0);
}

void security::check_heartbeart() {
	// check to networking server if client is connected
}

void security::check_debug_string()
{
	DWORD last_error = GetLastError();
	OutputDebugStringA("GVMP Anti-Cheat Check");

	auto is_debugging = GetLastError() != last_error;
}

void security::initialize()
{
	while (true) {
		this->check_heartbeart();
		this->check_debug_string();

		std::this_thread::sleep_for(std::chrono::seconds(150));
	}
}

void security::hide_thread()
{
}
