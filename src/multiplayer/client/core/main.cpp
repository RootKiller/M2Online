/////////////////////////////////////////////
//
//	    Mafia 2 Online @ main.cpp
//        Project: core (Client)
//
//////////////////////////////////////////////

#include <includes.h>

namespace Mafia2
{

	class CVector3
	{
	public:
		float x, y, z;
	};

	class CQuaternion
	{
	public:
		float w, x, y, z;
	};

	class CGameObjectBase
	{
	public:
		unsigned int vtable; // 0-4
	};

	class CHumanUnknownSubclass // may be CEntity(?)
	{
	public:
		unsigned char pad[208];				// 4-208
		float fHealth;						// 208-212
		unsigned char pad2[20];				// 212-232
		unsigned char ucInvulnerability;	// 232-233 (maybe just bool)
	};

	class C_HumanInventory : public CGameObjectBase
	{
	public:
		char AddWeapon(int, int);
	};

	char _declspec(naked) C_HumanInventory::AddWeapon(int, int)
	{
		_asm
		{
			mov eax, 0x95B030
			jmp eax
		}
	}

	// Unknown structure - maybe RefPointer or something like that
	struct SUnknownStruct
	{
		unsigned int unknown;
	};

	class CHuman
	{
	public:
		CHumanUnknownSubclass * pUnknown1; // 0-4
		//unsigned char pad[156];				// 4-160

		
		int SetHealth(float);
		float GetHealth();

		int SetMaxHealth(float); 
		float GetMaxHealth();

		bool GetInvulnerability();
		int SetInvulnerability(bool);

		void * AnimPlay(SUnknownStruct *, const char *a3, char a4, char a5, unsigned int a6, float a7, float a8, float a9);

		//char InventoryAddWeapon(int weaponId, int ammoCount);
	};

	void _declspec(naked) * CHuman::AnimPlay(SUnknownStruct *, const char *a3, char a4, char a5, unsigned int a6, float a7, float a8, float a9)
	{
		_asm
		{
			mov eax, 0x994630
			jmp eax
		}
	}

	bool _declspec(naked) CHuman::GetInvulnerability()
	{
		_asm
		{
			mov eax, 0x91DFE0
			jmp eax
		}
	}

	int _declspec(naked) CHuman::SetInvulnerability(bool)
	{
		_asm
		{
			mov eax, 0x91DFD0
			jmp eax
		}
	}

	int _declspec(naked) CHuman::SetHealth(float)
	{
		_asm
		{
			mov eax, 0x93B8C0
			jmp eax
		}
	}

	float _declspec(naked) CHuman::GetHealth()
	{
		_asm
		{
			mov eax, 0x91DEF0
			jmp eax
		}
	}

	int _declspec(naked) CHuman::SetMaxHealth(float)
	{
		_asm
		{
			mov eax, 0x93B920
			jmp eax
		}
	}

	float _declspec(naked) CHuman::GetMaxHealth()
	{
		_asm
		{
			mov eax, 0x91DF00
			jmp eax
		}
	}

	class CPlayer : public CGameObjectBase
	{
	public:
		// unsigned int vtable; = 0x018F14B8 0-4	
		unsigned char pad[24];				// 4-28
		unsigned int* unknown_ptr;			// 28-32 (scripting object pointer?)
		unsigned char pad2[128];			// 32-160
		C_HumanInventory *pInventory;		// 160-164
		CHuman *pHuman;						//164-168

		
		CVector3 * GetPosition(CVector3 *);
		CVector3 * SetPosition(CVector3 *);

		CVector3 * GetDirection(CVector3 *);
		CVector3 * SetDirection(CVector3 *);

		CQuaternion * GetRotation(CQuaternion *);
		CQuaternion * SetRotation(CQuaternion *);
	}; 

	CVector3 _declspec(naked) * CPlayer::GetPosition(CVector3 *)
	{
		_asm
		{
			mov eax, 0x938250
			jmp eax
		}
	}

	CVector3 _declspec(naked) * CPlayer::SetPosition(CVector3*)
	{
		_asm
		{
			mov eax, 0x94E960
			jmp eax
		}
	}
 
	CVector3 _declspec(naked) * CPlayer::GetDirection(CVector3 *)
	{
		_asm
		{
			mov eax, 0x91A290
			jmp eax
		}
	}
	
	CVector3 _declspec(naked) * CPlayer::SetDirection(CVector3 *)
	{
		_asm
		{
			mov eax, 0x94E9C0
			jmp eax
		}
	}

	CQuaternion _declspec(naked) * CPlayer::GetRotation(CQuaternion *)
	{
		_asm
		{
			mov eax, 0x91A310
			jmp eax
		}
	}

	CQuaternion _declspec(naked) * CPlayer::SetRotation(CQuaternion *)
	{
		_asm
		{
			mov eax, 0x94EA80
			jmp eax
		}
	}


	class CUnknown : public CGameObjectBase // Probably CGame
	{
	public:
		CPlayer * GetPlayerByIndex(unsigned int index);

		static CUnknown  * Get()
		{
			return *(CUnknown **)0x01ABFE14;
		}
	};

	unsigned int _sub_5B5BC0 = 0x005B5BC0;
	CPlayer _declspec(naked) * CUnknown::GetPlayerByIndex(unsigned int index)
	{
		_asm jmp _sub_5B5BC0;
	}

	class C_WrapperEntityPos : public CGameObjectBase
	{
	public:
		// 0198A300 - vtable
		CVector3 * GetPosition(CVector3 *);
		CVector3 * SetPosition(CVector3 *);

		CQuaternion * GetRotation(CQuaternion *);
		CQuaternion * SetRotation(CQuaternion *);

		CVector3 * GetDirection(CVector3 *);
		CVector3 * SetDirection(CVector3 *);

		//bool IsVisibleFromCamera();
	};

	
	/*bool C_WrapperEntityPos::IsVisibleFromCamera()
	{
		bool bRetnVal = false;
		_asm
		{
			mov ecx, this
			mov eax, 0xD7D3C0
			call eax
			mov bRetnVal, al
		}
		return bRetnVal;
	}*/

	CVector3 _declspec(naked) * C_WrapperEntityPos::GetPosition(CVector3 *)
	{
		_asm
		{
			mov eax, 0xD6C630
			jmp eax
		}
	}

	CVector3 _declspec(naked) * C_WrapperEntityPos::SetPosition(CVector3 *)
	{
		_asm
		{
			mov eax, 0xD6C690
			jmp eax
		}
	}
	
	CQuaternion _declspec(naked) * C_WrapperEntityPos::GetRotation(CQuaternion *)
	{
		_asm
		{
			mov eax, 0xD6C6F0
			jmp eax
		}
	}

	CQuaternion _declspec(naked) * C_WrapperEntityPos::SetRotation(CQuaternion *)
	{
		_asm
		{
			mov eax, 0xD6C6D0
			jmp eax
		}
	}
	
	CVector3 _declspec(naked) * C_WrapperEntityPos::GetDirection(CVector3 *)
	{
		_asm
		{
			mov eax, 0xD6C660
			jmp eax
		}
	}

	CVector3 _declspec(naked) * C_WrapperEntityPos::SetDirection(CVector3 *)
	{
		_asm
		{
			mov eax, 0xD6C6B0
			jmp eax
		}
	}

	class C_WrapperPlayer : public C_WrapperEntityPos
	{
	public:
		int SetDrunk();
	};

	int _declspec(naked) C_WrapperPlayer::SetDrunk()
	{
		_asm
		{
			mov eax, 0xD6F300
			jmp eax
		}
	}

	class CPlayerModelManager : public C_WrapperEntityPos
	{
	public:
		bool ChangePlayerModel(const char *, int);

		static CPlayerModelManager * Get()
		{
			return *(CPlayerModelManager**)0x1ABFE5C;
		}
	};
	
	bool _declspec(naked) CPlayerModelManager::ChangePlayerModel(const char *, int)
	{
		_asm
		{
			mov eax, 0x5CBE30
			jmp eax
		}
	}

	class CUnknown3 : public CGameObjectBase
	{
	public:
		C_WrapperPlayer* sub_D95450(unsigned int * unknown);

		static CUnknown3 * Get()
		{
			return *(CUnknown3 **)0x1CC14A8;
		}
	};

	C_WrapperPlayer _declspec(naked) * CUnknown3::sub_D95450(unsigned int *unknown)
	{
		_asm
		{
			mov eax, 0xD95450
			jmp eax
		}
	}

	class CEntityBase : public C_WrapperEntityPos
	{
	public:
		void __thiscall Activate()
		{
			_asm
			{
				mov eax, [ecx]
				call [ebp+32]
			}
		}
	};

	class CEntityWrapper : public CGameObjectBase
	{
	public:
		CEntityBase * GetEntityByName(const char *name);

		static CEntityWrapper * Get()
		{
			return *(CEntityWrapper**)0x01CC14A8;
		}
	};


	CEntityBase _declspec(naked) * CEntityWrapper::GetEntityByName(const char *name)
	{
		_asm
		{
			mov eax, 0xD955A0
			jmp eax
		}
	}

	int _declspec(naked) sub_B2FC70(const char *weather_template)
	{
		_asm
		{
			mov eax, 0xB2FC70
			jmp eax
		}
	}

	class CTraffic
	{
	public:
		unsigned char pad[93]; // 0-93
		unsigned char ucPolice;// 93-94

		char SetPolice(char);
		char SwitchGenerators(char);

		static CTraffic * Get()
		{
			return *(CTraffic**)0x01CBFF00;
		}
	};

	char _declspec(naked) CTraffic::SetPolice(char)
	{
		_asm
		{
			mov eax, 0xA25940
			jmp eax
		}
	}

	char _declspec(naked) CTraffic::SwitchGenerators(char)
	{
		_asm
		{
			mov eax, 0xAAB870
			jmp eax
		}
	}
	
};

bool g_bPrinted = false;
void _cdecl MainLoop()
{

	//if (GetAsyncKeyState(VK_F5))
	{
		Mafia2::CUnknown *pUnknown = Mafia2::CUnknown::Get();
		if (pUnknown)
		{
			Mafia2::CPlayer * pPlayer = pUnknown->GetPlayerByIndex(0);
			if (pPlayer)
			{
				Mafia2::CUnknown3 *pUnknown3 = Mafia2::CUnknown3::Get();
				if (pUnknown3)
				{
					Mafia2::C_WrapperPlayer *pUnknown4 = pUnknown3->sub_D95450(pPlayer->unknown_ptr);//Create scripting object from entity?

					if (g_bPrinted == false)
					{
						Info("Player: %p(%p), Human: %p", pPlayer, pPlayer->vtable, pPlayer->pHuman);
						g_bPrinted = true;
					}

					Mafia2::CVector3 vec;
					//144					
					/*Mafia2::CVector3 vec;
					pPlayer->GetPosition(&vec);
					Info("Position: %f,%f,%f", vec.x, vec.y, vec.z);

					if (GetAsyncKeyState(VK_F5))
					{
						vec.z += 0.5f;
						pUnknown4->SetPosition(&vec);
					}

					Mafia2::CQuaternion quat;
					pPlayer->GetRotation(&quat);
					Info("Rotation: %f,%f,%f,%f", quat.w, quat.x, quat.y, quat.z);

					pPlayer->GetDirection(&vec);
					Info("Direction: %f,%f,%f", vec.x, vec.y, vec.z);


					Info("Health: %f", pPlayer->pHuman->GetHealth());
					Info("Human unknown1 health: %f", pPlayer->pHuman->pUnknown1->fHealth);*/

					if (GetAsyncKeyState(VK_F10))
					{
						pPlayer->pHuman->SetHealth(10.0f);

					}

					if (GetAsyncKeyState(VK_F6))
					{
						Mafia2::CPlayerModelManager::Get()->ChangePlayerModel("vitarmy", -1);
					}

					if (GetAsyncKeyState(VK_F7) && 98==4)
					{
						Mafia2::CEntityBase *pEntity = Mafia2::CEntityWrapper::Get()->GetEntityByName("M02BruskyObjectiveCar");
						Info("%p", pEntity->vtable);

						pEntity->Activate();
						pPlayer->GetPosition(&vec);
						pEntity->SetPosition(&vec);
					}

					if (GetAsyncKeyState(VK_F8))
					{
						//pUnknown4->SetDrunk();

						pPlayer->pInventory->AddWeapon(14, 999);
					}

					if (GetAsyncKeyState(VK_F9))
					{
						// Disable traffic
						//*(DWORD *)0x01AA92AC = 0;

						Mafia2::CTraffic::Get()->ucPolice = FALSE;
						//Mafia2::CTraffic::Get()->SwitchGenerators(false);
						//Mafia2::CTraffic::Get()->SetPolice(false);
					}

					if (GetAsyncKeyState(VK_F11))
					{
						Mafia2::SUnknownStruct s;
						
						pPlayer->pHuman->AnimPlay(&s, "sc_Vito_wakeup_L", true, true, 0, 0.0f, 0.30000001f, 0.30000001f);
					}

					if (GetAsyncKeyState(VK_F9))
					{
						pPlayer->pHuman->SetInvulnerability(pPlayer->pHuman->GetInvulnerability() == false);
					
						// Crashy as hell
					//	Mafia2::sub_B2FC70("DT02NewStart2");
					}
					//Info("Invulnerability: %s", pPlayer->pHuman->GetInvulnerability() ? "yes" : "no");
				}
			}
		} 

	}
}

unsigned int MainLoopHook_retn = 0x00AC6FD5;
void _declspec(naked) MainLoopHook()
{
	_asm
	{
		call	MainLoop

		sub     esp, 1Ch
		push    ebx
		push    esi
		jmp		MainLoopHook_retn
	}
}

const char * GetDataPath()
{
	char szPath[MAX_PATH] = { 0 };
#ifdef DEBUG
	GetModuleFileName(GetModuleHandle("core_d.dll"), szPath, MAX_PATH);
#else
	GetModuleFileName(GetModuleHandle("core.dll"), szPath, MAX_PATH);
#endif
	for (uint8 i = strlen(szPath); i > 0; i--)
	{
		if (szPath[i] == '\\')
		{
			szPath[i] = '\0';
			break;
		}
	}
	return szPath;
}

//(void *this, void *a2, char *a3, char a4, char a5, unsigned int a6, int a7, int a8, int a9)

void _cdecl PlayAnimHookCallback(void *_this, void *a2, char *a3, char a4, char a5, unsigned int a6, float a7, float a8, float a9)
{
	Info("PlayAnimHookCallback(%p, %p, %s, %d, %d, %d, %f, %f, %f)", _this, a2, a3, a4, a5, a6, a7, a8, a9);
}
unsigned int PlayAnimHookRetn = 0x00994638;
void _declspec(naked) PlayAnimHook()
{
	_asm
	{
		pushad
		push [esp + 40h]
		push [esp + 40h]
		push [esp + 40h]
		push [esp + 40h]
		push [esp + 40h]
		push [esp + 40h]
		push [esp + 40h]
		push [esp + 40h]
		push ecx
		call PlayAnimHookCallback
		add esp, [4*9]
		popad
		sub     esp, 0Ch
		push    esi
		lea     eax, [esp + 4]
		jmp PlayAnimHookRetn
	}
}

int _cdecl PrintAddress(unsigned int address)
{
	Info("Retn: %p", address);
	return 1;
}

void _declspec(naked) RestartAppIfNeccessaryHook()
{
	_asm
	{
		pushad
		push [esp+20h]
		call PrintAddress
		add esp, 4h
		popad
		retn
	}
}

void _cdecl SomeSecurityFunction()
{
	// simply do nothing
	Debug("Oh dear, steam detected multiplayer - we gonna cry now..");
}

typedef VOID (WINAPI *pfnExitProcess)(UINT);
pfnExitProcess g_pfnExitProcess = 0;

VOID WINAPI Trampoline_ExitProcess(UINT a1)
{
	unsigned calladdress0 = 0;
	_asm mov eax, [esp+4]
	_asm mov calladdress0, eax
	Debug("Oh dear, steam detected multiplayer - we gonna cry now..");
	Info("ExitProcess call (%p)", calladdress0);
	//g_pfnExitProcess(a1);
}

unsigned calladdress0 = 0;
void _declspec(naked) ExitProcessHook(UINT a1)
{
	_asm mov eax, [esp]
	_asm mov calladdress0, eax

	Info("ExitProcess call (%p)", calladdress0);

	_asm retn;
}

bool _cdecl sub_DEC1F0(LPCSTR *)
{
	Debug("mhm");
	return true;
}

// Enable debugging
typedef BOOL (WINAPI *pfnNtSetInformationThread)(HANDLE ThreadHandle, ULONG ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength);
pfnNtSetInformationThread g_pfnNtSetInformationThread = 0;

BOOL WINAPI Trampoline_NtSetInformationThread(HANDLE ThreadHandle, ULONG ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength)
{
	if (ThreadInformationClass == 0x11)
	{
		Debug("Anti debug");
		return TRUE;
	}

	return g_pfnNtSetInformationThread(ThreadHandle, ThreadInformationClass, ThreadInformation, ThreadInformationLength);
}

unsigned int SomeSteamShitBack = 0x00DED147;
void _declspec(naked) SomeSteamShit()
{
	_asm
	{
		pushad
		push [esp+20h]
		call PrintAddress
		add esp, 4h
		popad

		lea eax, [esp + 1004h]
		jmp SomeSteamShit
	}
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			// Disable thread library calls
			DisableThreadLibraryCalls(hModule);

			// Startup logger
			char szLogPath[MAX_PATH] = { 0 };
			sprintf(szLogPath,"%s\\client.log", GetDataPath());
			Logger::Init(szLogPath);

#ifdef DEBUG
			// Debug console
			AllocConsole();
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
			freopen("CONIN$", "r", stdin);
#endif

			// Initialize hooking (also known as unprotect segments)
			Hooking::Initialize();

			Hooking::JmpHook(0x00AC6FD0, (DWORD)MainLoopHook);

			//g_pfnExitProcess = (pfnExitProcess)DetourFunction((PBYTE)DetourFindFunction("kernel32.dll", "ExitProcess"), (PBYTE)Trampoline_ExitProcess);
			Hooking::JmpHook((DWORD)GetProcAddress(LoadLibrary("kernel32.dll"), "ExitProcess"), (DWORD)ExitProcessHook);

			g_pfnNtSetInformationThread = (pfnNtSetInformationThread)DetourFunction((PBYTE)DetourFindFunction("ntdll.dll", "NtSetInformationThread"), (PBYTE)Trampoline_NtSetInformationThread);

			//void *__thiscall sub_994630(void *this, void *a2, char *a3, char a4, char a5, unsigned int a6, int a7, int a8, int a9)
			//Hooking::JmpHook(0x00994630, (DWORD)PlayAnimHook);

			// Disable one call of SteamAPI_RestartAppIfNeccessary (probably fix for that random game restart)
			//memset((void *)0x00401660, 0x90, 0x0B);
			//memset((void *)0x00DD139C, 0x90, 6);
			Hooking::JmpHook(0x00DED140, (DWORD)SomeSteamShit);
			//memset((void*)0x00DED140, 0x90, 0x00DED19F- 0x00DED140);

			///*(unsigned char *)0x00DED140 = 0xC3;

			// Disable protection
			//memset((void *)0x00E6E2B0, 0x90, 5);
			//Hooking::JmpHook(0x00E6E240, (DWORD)SomeSecurityFunction);
			//Hooking::JmpHook(0x00DEC1F0, (DWORD)sub_DEC1F0);

			//Hooking::JmpHook(0x00401660, (DWORD)RestartAppIfNeccessaryHook);
		} break;
	case DLL_PROCESS_DETACH:
		{
			Logger::Shutdown();
		} break;
	}
	return TRUE;
}