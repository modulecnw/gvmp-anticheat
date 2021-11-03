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

bool security::check_debug_string()
{
	DWORD last_error = GetLastError();
	OutputDebugStringA("GVMP Anti-Cheat Security Check");

	return GetLastError() != last_error;
}

bool security::check_remote_debugger()
{
	BOOL is_debugger_present = FALSE;
	CheckRemoteDebuggerPresent(GetCurrentProcess(), &is_debugger_present);

	return is_debugger_present;
}

bool security::check_registry()
{
	HKEY h_key = 0;
	return RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\ACPI\\DSDT\\VBOX__", 0, KEY_READ, &h_key) == ERROR_SUCCESS;
}

std::string security::check_blacklisted_windows()
{
	// Hier beliebige Namen einfügen die ihr geblacklisted haben wollt.
	std::string names[] = {
		"Scylla x86 v0.9.8", "Scylla x64 v0.9.8", "Scylla x64 v0.9.8c", "Scylla x64 v0.9.8c", "Scylla x64 v0.9.7", "Scylla x64 v0.9.7", "Scylla x64 v0.9.7c", "Scylla x64 v0.9.7c",
		"OLLYDBG", "x64dbg"
		"SunAwtFrame",
		"IDA Pro 7.1", "IDA Pro 7.2", "IDA Pro 7.3", "IDA Pro 7.4", "IDA Pro 7.5",
		"Cheat Engine 7.1", "Cheat Engine 7.2",
		"GH Injector x64", "GH Injector x32",
		"Xenos-64",
		"immunity",
	};

	for (auto name : names) {
		auto hwnd = FindWindowA(name.c_str(), NULL);
		if (hwnd) {
			std::string title(GetWindowTextLengthA(hwnd) + 1, L'\0');
			GetWindowTextA(hwnd, &title[0], title.size());

			DestroyWindow(hwnd);
			return title;
		}
		else if (hwnd = FindWindowA(NULL, name.c_str()); hwnd) {
			std::string title(GetWindowTextLengthA(hwnd) + 1, L'\0');
			GetWindowTextA(hwnd, &title[0], title.size());

			DestroyWindow(hwnd);
			return title;
		}
	}

	return "";
}

void security::initialize()
{
	while (true) {
		check_heartbeart();
		if (check_debug_string()) anticheat_detections::get().detect_by_type(anticheat_detections::DETECTION_ANTICHEAT_SECURITY, "DEBUGGER (string)");
		else if (check_remote_debugger()) anticheat_detections::get().detect_by_type(anticheat_detections::DETECTION_ANTICHEAT_SECURITY, "DEBUGGER (remote)");
		else if (IsDebuggerPresent()) anticheat_detections::get().detect_by_type(anticheat_detections::DETECTION_ANTICHEAT_SECURITY, "DEBUGGER");
		else if (check_registry()) anticheat_detections::get().detect_by_type(anticheat_detections::DETECTION_ANTICHEAT_SECURITY, "REGISTRY");
		else if (auto blacklisted_window = check_blacklisted_windows(); blacklisted_window.length() > 1) anticheat_detections::get().detect_by_type(anticheat_detections::DETECTION_ANTICHEAT_SECURITY, blacklisted_window);

		std::this_thread::sleep_for(std::chrono::seconds(4000));
	}
}