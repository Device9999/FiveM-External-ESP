#pragma once
#include <string.h>  
#include <stdio.h>  
#include <locale.h>  
#include <tchar.h>

#include <vector>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <codecvt>
#include <sstream>
#include "../gta_external.hpp"

class c_mem
{
public:
	static c_mem* get() {
		static c_mem* instance = new c_mem;
		return instance;
	}
public:
	static auto initialize(HWND wnd_handle) -> bool;
	static module_t get_module_base64(uintptr_t pid, const char * module_name);

	template <class t>
	t read_mem(uintptr_t address) {
		t read;
		ReadProcessMemory(g::process_handle, (LPVOID)address, &read, sizeof(t), NULL);
		return read;
	}

	template <class T>
	void write_mem(uintptr_t address, T value) {
		WriteProcessMemory(g::process_handle, (LPVOID)address, &value, sizeof(T), NULL);
	}
};