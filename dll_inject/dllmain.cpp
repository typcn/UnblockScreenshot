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
	VirtualProtect(func_data, 6, PAGE_EXECUTE_READWRITE, &old_prot);

	func_data[0] = 0xB8;
	func_data[1] = 0x01;
	func_data[2] = 0x00;
	func_data[3] = 0x00;
	func_data[4] = 0x00;
	func_data[5] = 0xC3;

	VirtualProtect(func_data, 6, old_prot, NULL);
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

