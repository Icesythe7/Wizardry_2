#pragma once
#include "pch.h"

namespace Lua
{
	int32_t GetTop(uintptr_t);
	bool IsString(uintptr_t, int32_t);
	const char* ToString(uintptr_t, int32_t);
	bool IsNumber(uintptr_t, int32_t);
	double ToNumber(uintptr_t, int32_t);
	void Error(uintptr_t, const char*);
	bool CompareStrings(const char*, const char*);
	int64_t Wizardry(uintptr_t);
}