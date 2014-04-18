/////////////////////////////////////////////
//
//	    Mafia 2 Online @ Hooking.cpp
//        Project: core (Client)
//
//////////////////////////////////////////////

#include <includes.h>

namespace Hooking
{
void Hook(DWORD dwAddress, DWORD dwHookAddress, unsigned char ucOpcode)
{
	// Unprotect segment
	DWORD dwOld = 0;//Temp variable
	VirtualProtect((void *)dwAddress, 5, PAGE_EXECUTE_READWRITE, &dwOld);

    *(BYTE *)dwAddress = ucOpcode;
    *(DWORD*)(dwAddress + 0x1) = dwHookAddress - (dwAddress + 5);

	// Reprotect segment
	DWORD dwOld2 = 0;
	VirtualProtect((void *)dwAddress, 5, dwOld, &dwOld2);
}

void JmpHook(DWORD dwAddress, DWORD dwHookAddress)
{
	Hook(dwAddress,dwHookAddress,0xE9);
}

void CallHook(DWORD dwAddress, DWORD dwHookAddress)
{
	Hook(dwAddress,dwHookAddress,0xE8);
}

void MethodHook(DWORD dwAddress, DWORD dwHookAddress)
{
    *(DWORD *)dwAddress = dwHookAddress;
}

uint8 * JmpHookWithTrampoline(uint32 dwAddress, uint32 dwFunction, uint8 *bResultArray)
{
	// Build array for our trampoline method
	BYTE bArray[10] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00 };

	bResultArray = new uint8[10];

	// Read 5 first bytes which we will override
	memcpy(bArray, (void*)dwAddress, 5);

	// Write our jmp address
	Hook(dwAddress, dwFunction, 0xE9);

	// Update byte array with return address
	*(DWORD*)(bArray + 6) = (dwAddress + 5) - ((DWORD)bResultArray + 5);

	// Copy everything to our array
	memcpy(bResultArray, bArray, 10);

	for (BYTE b = 0; b < 10; b++)
		printf("%02X ", bResultArray[b]);
	printf("\n");

	// Return jmp method
	return bResultArray;
}

void RemoveTrampoline(uint32 dwTrampoline)
{
	// TODO: RESTORE MEMORY

	uint8 * trampoline = *(uint8**)dwTrampoline;
	if (trampoline)
		delete trampoline;
}

void Initialize(void)
{
	// Prepare headers
	PBYTE pbImageBase = (PBYTE)GetModuleHandle(NULL);
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)pbImageBase;
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)(pbImageBase + pDosHeader->e_lfanew);
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHeaders);

	// Loop thought all sections
	for(int iSection = 0; iSection < pNtHeaders->FileHeader.NumberOfSections; iSection++, pSection++)
    {
		char * szSectionName = (char*)pSection->Name;
		if(!strcmp(szSectionName,".text") || !strcmp(szSectionName,".rdata") || !strcmp(szSectionName,".textnc"))
		{
			// Unprotect segment
			DWORD dwOld = 0;//Temp variable
			VirtualProtect((void *)(pbImageBase + pSection->VirtualAddress),((pSection->Misc.VirtualSize+4095)&~4095),PAGE_EXECUTE_READWRITE,&dwOld);
		}
	}
}
};