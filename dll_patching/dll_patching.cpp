#include "stdafx.h"
#include "Shlobj.h"
#include <assert.h>
#include <stdint.h>
#include <Windows.h>
#include <winnt.h>
#include <inttypes.h>

int main(int argc, char const *argv[]) {
	char user32path[128];
	GetModuleFileNameA(GetModuleHandle(L"user32.dll"), user32path, 128);
	FILE *f = fopen(user32path, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	uint8_t *data = (uint8_t *)malloc(fsize);
	fread(data, fsize, 1, f);
	fclose(f);

	uint32_t pe_file_start = *(uint32_t *)(data + 64 - 4);
	printf("PE File Start: 0x%x\n", pe_file_start);

	uint32_t header_size = *(uint32_t *)(data + pe_file_start + 24 + /* OptionalHeader */ +60 /* to SizeOfHeaders */);
	printf("Header Size: 0x%x\n", header_size);

	HMODULE user32 = GetModuleHandle(L"user32.dll");
	intptr_t funcaddr = (intptr_t)GetProcAddress(user32, "SetWindowDisplayAffinity");
	printf("Function address: 0x%" PRIxPTR "\n", funcaddr);

	intptr_t offset = funcaddr - (intptr_t)user32;
	printf("Memory offset: 0x%" PRIxPTR "\n", offset);

	IMAGE_NT_HEADERS *nt_headers = (IMAGE_NT_HEADERS *)(data + pe_file_start);
	PIMAGE_SECTION_HEADER section_header = IMAGE_FIRST_SECTION(nt_headers);

	intptr_t file_offset = offset - section_header->VirtualAddress + section_header->PointerToRawData;
	printf("File offset is: 0x%" PRIxPTR "\n", file_offset);

	uint8_t *func_data = data + file_offset;

	// mov eax, 1     retn
	func_data[0] = 0xB8;
	func_data[1] = 0x01;
	func_data[2] = 0x00;
	func_data[3] = 0x00;
	func_data[4] = 0x00;
	func_data[5] = 0xC3;

	FILE *outfile = fopen("user32_patched.dll", "wb");
	fwrite(data, fsize, 1, outfile);
	fflush(outfile);
	fclose(outfile);
	printf("Patching complete, user32_patched.dll saved to current working directory.\n");
	getchar();
	return 0;
}