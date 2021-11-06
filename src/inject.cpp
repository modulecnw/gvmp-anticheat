#include "imports.hpp"
#include "nemo.hpp"

inline HMODULE g_hModule = nullptr;
DWORD WINAPI start_thread(LPVOID lParameter)
{
	Log::Push(new Log::ConsoleStream());
	MH_Initialize();

	nemo_ac::get().run_service(g_hModule);

	while (true)
	{
		// External Cheat Test
		/*if (GetAsyncKeyState(VK_ADD) & 0x1) {
			auto hwnd = GetTopWindow((HWND)GetForegroundWindow());

			std::wstring title(GetWindowTextLength(hwnd) + 1, L'\0');
			GetWindowTextW(hwnd, &title[0], title.size());

			Log::Info(title.c_str());
		}*/

		if (GetAsyncKeyState(VK_PRIOR) & 0x8000)
			break;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		std::this_thread::yield();
	}

	nemo_ac::get().shutdown_service();

	fclose(stdin);
	fclose(stdout);

	FreeConsole();

	FreeLibraryAndExitThread(g_hModule, 0);

	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {

		g_hModule = hModule;
		AllocConsole();

		SetConsoleTitleA("NEMO | Developer-Output Console");

		freopen_s((FILE**)stdin, "conin$", "r", stdin);
		freopen_s((FILE**)stdout, "conout$", "w", stdout);

		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)start_thread, nullptr, 0, nullptr);
	}

	return TRUE;
}