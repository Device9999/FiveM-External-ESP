#include "memory.hpp"

auto c_mem::initialize(HWND wnd_handle) -> bool {
	DWORD process_id;
	if (wnd_handle) {
		GetWindowThreadProcessId(wnd_handle, &process_id);
		g::pid = process_id;
		return true;
	}
	return false;
}

uintptr_t c_mem::get_module_base64(uintptr_t pid, const char *module_name)
{
	DWORD64 base_address = 0;
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
	if (snapshot == INVALID_HANDLE_VALUE) {
		char str[0xff];
		sprintf_s(str, "Failed to get %s, invalid handle value", module_name);
		MessageBoxA(0, str, "ERROR", MB_OK | ERROR);
		return base_address;
	}

	MODULEENTRY32 module_entry;
	module_entry.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(snapshot, &module_entry)) {
		do {
			if (_tcsicmp(module_entry.szModule, module_name) == 0) {
				base_address = (DWORD64)module_entry.modBaseAddr;
				break;
			}
		} while (Module32Next(snapshot, &module_entry));
	}
	CloseHandle(snapshot);
	return base_address;
}
