#pragma once
#include "pch.h"

namespace Addresses
{
	inline uintptr_t OnUpdate = 0x4A8460;
	inline uintptr_t EnterWorld = 0x528010;
	inline uintptr_t GameStateOffset = 0xBEBA40;
	inline uintptr_t FrameScriptExecute = 0x819210;
	inline uintptr_t FrameScriptRegister = 0x817F90;
	inline uintptr_t FrameScriptUnRegister = 0x817FD0;
	inline uintptr_t SpellHandleTerrainClickPtr = 0x80C340;
	inline uintptr_t TextSectionEnd = 0xD415BC;
	inline uintptr_t ClntObjMgrGetActivePlayer = 0x4D3790;
	inline uintptr_t ClntObjMgrObjectPtr = 0x4D4DB0;
	inline uintptr_t GetGuidByKeywordPtr = 0x60C1C0;
	inline uintptr_t LuaGetTop = 0x84DBD0;
	inline uintptr_t LuaIsString = 0x84DF60;
	inline uintptr_t LuaToString = 0x84E0E0;
	inline uintptr_t LuaIsNumber = 0x84DF20;
	inline uintptr_t LuaToNumber = 0x84E030;
	inline uintptr_t LuaError = 0x84F280;
}