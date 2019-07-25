#pragma once
#include "pch.h"

namespace Wizardry
{
	//typedefs
	typedef int32_t(__cdecl* onupdate)(float*);
	typedef void(__cdecl* onenterworld)();

	//vars
	inline onupdate FpOnUpdate = nullptr;
	inline onenterworld FpOnEnterWorld = nullptr;
	inline bool InitFirstLoad;
	inline bool ShouldUnRegisterLua;

	//functions
	int32_t __cdecl DetourOnUpdate(float* a1);
	void __cdecl DetourOnEnterWorld();
	DWORD WINAPI Init(void* const(param));
}