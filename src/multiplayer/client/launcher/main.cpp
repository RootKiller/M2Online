/////////////////////////////////////////////
//
//	    Mafia 2 Online @ main.cpp
//      Project: launcher (Client)
//
//////////////////////////////////////////////

#include <Windows.h>
#include <stdio.h>

void InjectDll(HANDLE hProcess, const char * szDllPath);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdLine)
{
	// Get game directory
	char szGameExePath [MAX_PATH] = { 0 }, szGamePath[MAX_PATH] = { 0 };

	HKEY hKey = 0;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Steam App 50130", NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		MessageBox(NULL, "Cannot find game executable file! #001", "Mafia 2 Online - Error", MB_ICONERROR);
		return E_FAIL;
	}

	unsigned int uiType = REG_SZ;
	unsigned int uiSize = MAX_PATH;
	if(RegQueryValueEx(hKey, "InstallLocation", NULL, (LPDWORD)&uiType, (BYTE *)szGamePath, (LPDWORD)&uiSize) != ERROR_SUCCESS)
	{
		MessageBox(NULL, "Cannot find game executable file! #002", "Mafia 2 Online - Error", MB_ICONERROR);
		return E_FAIL;
	}

	strcat(szGamePath, "\\pc\\");
	sprintf(szGameExePath, "%smafia2.exe", szGamePath);

	// Set steam environment variables
	SetEnvironmentVariable("SteamGameId", "50130");
	SetEnvironmentVariable("SteamAppID", "50130");

	// Create game process
	STARTUPINFO siStartupInfo = {0};
	PROCESS_INFORMATION piProcessInformation = {0};
	siStartupInfo.cb = sizeof(siStartupInfo);

	if(!CreateProcess(szGameExePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, szGamePath, &siStartupInfo, &piProcessInformation))
	{
		MessageBox(NULL,"Cannot create game process.","Mafia 2 Online - Error",MB_ICONERROR);
		return E_FAIL;
	}

	// Inject dll
	char szPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL,szPath,MAX_PATH);
	for(unsigned int i = strlen(szPath); i > 0; i--)
	{
		if (szPath[i] == '\\')
		{
			szPath[i] = '\0';
			break;
		}
	}
#ifdef DEBUG
	strcat(szPath,"\\core_d.dll");
#else
	strcat(szPath,"\\core.dll");
#endif

	if (GetFileAttributes(szPath) == INVALID_FILE_ATTRIBUTES)
	{
		MessageBox(NULL, "Cannot find client dynamic library. Try to reinstall mod and try again then.", "Mafia 2 Online - Error", MB_ICONERROR);

		TerminateProcess(piProcessInformation.hProcess, 0);
		return E_FAIL;
	}

	InjectDll(piProcessInformation.hProcess,szPath);

	// Restore process thread
	ResumeThread(piProcessInformation.hThread);
	return S_OK;
}

void InjectDll(HANDLE hProcess, const char * szDllPath) //TODO: Error handling
{
    size_t sLibPathLen = (strlen(szDllPath)+1);
    SIZE_T bytesWritten = 0;

    void * pRmtLibraryPath = VirtualAllocEx(hProcess, NULL, sLibPathLen, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(hProcess, pRmtLibraryPath, (void*)szDllPath, sLibPathLen, &bytesWritten);
    HMODULE hKernel32 = GetModuleHandle("Kernel32");
    FARPROC pfnLoadLibraryA = GetProcAddress(hKernel32, "LoadLibraryA");
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pfnLoadLibraryA, pRmtLibraryPath, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    VirtualFreeEx(hProcess, pRmtLibraryPath, sizeof(pRmtLibraryPath), MEM_RELEASE);
}