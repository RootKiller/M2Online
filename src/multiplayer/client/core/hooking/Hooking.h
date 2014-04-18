/////////////////////////////////////////////
//
//	    Mafia 2 Online @ Hooking.h
//        Project: core (Client)
//
//////////////////////////////////////////////

#pragma once

namespace Hooking
{
void Initialize(void);

void Hook(DWORD dwAddress, DWORD dwHookAddress, unsigned char ucOpcode);
void JmpHook(DWORD dwAddress, DWORD dwHookAddress);
void CallHook(DWORD dwAddress, DWORD dwHookAddress);
void MethodHook(DWORD dwAddress, DWORD dwHookAddress);
uint8 * JmpHookWithTrampoline(uint32 dwAddress, uint32 dwFunction,uint8 *bResultArray = 0);

void RemoveTrampoline(uint32 dwTrampoline);

template <class T>
static void Write(DWORD dwAddress, T value)
{
	*(T*)dwAddress = value;
}

template <class T>
static T Read(DWORD dwAddress)
{
	return *(T*)dwAddress;
}
};