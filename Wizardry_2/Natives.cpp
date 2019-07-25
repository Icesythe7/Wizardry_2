#include "pch.h"

namespace Natives
{
	int32_t RunLua(const char* luaString)
	{
		return reinterpret_cast<int32_t(__cdecl*)(const char*, const char*, int32_t a3)>(Addresses::FrameScriptExecute)(luaString, luaString, 0);
	}

	int32_t RegisterFunction(const char* luaName, const uintptr_t theFunction)
	{
		const auto textSectionEnd = *reinterpret_cast<uint32_t*>(Addresses::TextSectionEnd);

		if (theFunction >= textSectionEnd)
		{
			const auto dif = theFunction - textSectionEnd;
			*reinterpret_cast<uint32_t*>(Addresses::TextSectionEnd) = textSectionEnd + dif + 1;
		}

		return reinterpret_cast<int32_t(__cdecl*)(const char*, uintptr_t)>(Addresses::FrameScriptRegister)(luaName, theFunction);
	}

	int32_t UnRegisterFunction(const char* luaName)
	{
		return reinterpret_cast<int32_t(__cdecl*)(const char*)>(Addresses::FrameScriptUnRegister)(luaName);
	}

	bool SpellHandleTerrianClick(const Vector3& position)
	{
		const auto pos = new TerrainClickData{ 0, position.x, position.y, position.z };
		return reinterpret_cast<bool(__cdecl*)(TerrainClickData*)>(Addresses::SpellHandleTerrainClickPtr)(pos);
	}

	int64_t GetGuidByKeyword(const char* keyword)
	{
		return reinterpret_cast<int64_t(__cdecl*)(const char*)>(Addresses::GetGuidByKeywordPtr)(keyword);
	}

	uintptr_t ClntObjMgrObject(const int64_t guid)
	{
		return reinterpret_cast<uintptr_t(__cdecl*)(int64_t, int32_t)>(Addresses::ClntObjMgrObjectPtr)(guid, -1);
	}

	int32_t GetVirtualFunction(const uintptr_t addr, const int32_t offset)
	{
		return addr ? *reinterpret_cast<int32_t*>(*reinterpret_cast<int32_t*>(addr) + 4 * offset) : 0;
	}

	Vector3 GetObjectPosition(const uintptr_t object)
	{
		const auto ptr = GetVirtualFunction(object, 11);
		Vector3 res;
		if (ptr)			
			reinterpret_cast<void(__thiscall*)(int32_t, Vector3*)>(ptr)(object, &res);
		return res;
	}

	void EnableWizardry()
	{
		RegisterFunction("Wizardry", reinterpret_cast<uintptr_t>(Lua::Wizardry));
		RunLua("print('[Wizardry 2] by Icesythe7 loaded!')");
		RunLua(R"(print('[Wizardry 2] example usage -> /run Wizardry("target", "Blizzard")'))");
	}
}