// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <stdint.h>
#include <Windows.h>

BOOL CALLBACK EnumWindowsCB(HWND hwnd, LPARAM lParam)
{
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	if (pid == lParam)
	{
		SetWindowDisplayAffinity(hwnd, WDA_NONE);
	}
	return TRUE;
}

void fucktheshitup() {
	DWORD pid = GetCurrentProcessId();
	EnumWindows(EnumWindowsCB, pid);
	uint8_t *func_data = (uint8_t *)GetProcAddress(GetModuleHandle(L"user32.dll"), "SetWindowDisplayAffinity");

	DWORD old_prot;
	VirtualProtect(func_data, 128, PAGE_EXECUTE_READWRITE, &old_prot);

	while (true) {
		func_data[0] = 0x90;
		func_data++;
		if (func_data[0] == 0xC2 || func_data[0] == 0xC3) {
			break;
		}
	}

	VirtualProtect(func_data, 128, old_prot, NULL);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		fucktheshitup();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

