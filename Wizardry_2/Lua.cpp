#include "pch.h"
#include <string>

namespace Lua
{
	/// <summary>
	/// Returns the number of params for the lua function that was called.
	/// </summary>
	/// <param name="luaState">The luaState.</param>
	/// <returns>The number of params.</returns>
	int32_t GetTop(const uintptr_t luaState)
	{
		return reinterpret_cast<int32_t(__cdecl*)(uintptr_t)>(Addresses::LuaGetTop)(luaState);
	}

	/// <summary>
	/// Returns a boolean if the specified element can be converted to a string.
	/// </summary>
	/// <param name="luaState">The luaState.</param>
	/// <param name="stackPos">The position of the element to check on the stack.</param>
	/// <returns>True if the specified stack element can be converted to a string.</returns>
	bool IsString(const uintptr_t luaState, const int32_t stackPos)
	{
		return reinterpret_cast<bool(__cdecl*)(uintptr_t, int32_t)>(Addresses::LuaIsString)(luaState, stackPos);
	}

	/// <summary>
	/// Converts the specified element in lua to a const char*.
	/// </summary>
	/// <param name="luaState">The luaState.</param>
	/// <param name="stackPos">The position of the element to check on the stack.</param>
	/// <returns>A const char* of the lua string.</returns>
	const char* ToString(const uintptr_t luaState, const int32_t stackPos)
	{
		return reinterpret_cast<const char* (__cdecl*)(uintptr_t, int32_t, DWORD*)>(Addresses::LuaToString)(luaState, stackPos, nullptr);
	}

	/// <summary>
	/// Returns a boolean if the specified element can be converted to a number.
	/// </summary>
	/// <param name="luaState">The luaState.</param>
	/// <param name="stackPos">The position of the element to check on the stack.</param>
	/// <returns>True if the specified stack element can be converted to a number.</returns>
	bool IsNumber(const uintptr_t luaState, const int32_t stackPos)
	{
		return reinterpret_cast<bool(__cdecl*)(uintptr_t, int32_t)>(Addresses::LuaIsNumber)(luaState, stackPos);
	}

	/// <summary>
	/// Converts the specified element in lua to a double.
	/// </summary>
	/// <param name="luaState">The luaSate.</param>
	/// <param name="stackPos">The position of the element to check on the stack.</param>
	/// <returns>A double of the lua number.</returns>
	double ToNumber(const uintptr_t luaState, const int32_t stackPos)
	{
		return reinterpret_cast<double(__cdecl*)(uintptr_t, int32_t)>(Addresses::LuaToNumber)(luaState, stackPos);
	}

	/// <summary>
	/// Throws an error in lua.
	/// </summary>
	/// <param name="luaState">The luaState.</param>
	/// <param name="msg">The error message to display.</param>
	void Error(const uintptr_t luaState, const char* msg)
	{
		reinterpret_cast<void(__cdecl*)(uintptr_t, const char*, int32_t)>(Addresses::LuaError)(luaState, msg, 0);
	}

	/// <summary>
	/// Helper function to compare two strings.
	/// </summary>
	/// <param name="string1">The first string.</param>
	/// <param name="string2">The second string.</param>
	/// <returns>True if both strings are an exact match.</returns>
	bool CompareStrings(const char* string1, const char* string2)
	{
		return strcmp(string1, string2) == 0;
	}

	int64_t Wizardry(const uintptr_t l)
	{
		const auto numArgs = GetTop(l);
		auto errorMsg = "Incorrect number of arguments for [Wizardry(string unit, string spellName)]";

		if (numArgs == 2
			&& (errorMsg = "Incorrect parameter(1) type [string expected for unit]", IsString(l, 1))
			&& (errorMsg = "Incorrect parameter(2) type [string expected for spellName]", IsString(l, 2)))
		{
			const auto command = ToString(l, 1);
			//if (CompareStrings(command, "player") || CompareStrings(command, "target") || CompareStrings(command, "focus"))
			//{
				const auto base = Natives::ClntObjMgrObject(Natives::GetGuidByKeyword(command));
				if (base)
				{
					const auto position = Natives::GetObjectPosition(base);
					if (!position.Invalid())
					{
						const auto castIt = "CastSpellByName('" + std::string(ToString(l, 2)) + "')";
						Natives::RunLua(castIt.c_str());
						SpellHandleTerrianClick(position);
						return 0;
					}
					errorMsg = "No valid position found!";
				}
				else
					errorMsg = "No valid targets found!";
				
			/*}
			else
				errorMsg = "Invalid command entered for [Wizardry(string unit, string spellName)]";*/
		}
		Error(l, errorMsg);
		return 0;
	}
}
