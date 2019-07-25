#include "pch.h"

namespace Wizardry
{
	int32_t __cdecl DetourOnUpdate(float* a1)
	{
		if (!InitFirstLoad && *reinterpret_cast<int32_t*>(Addresses::GameStateOffset) == 1)
		{
			InitFirstLoad = true;
			Natives::EnableWizardry();
		}

		if (ShouldUnRegisterLua)
			Natives::UnRegisterFunction("Wizardry");

		return FpOnUpdate(a1);
	}
	void __cdecl DetourOnEnterWorld()
	{
		if (!InitFirstLoad)
			InitFirstLoad = true;
		Natives::EnableWizardry();

		FpOnEnterWorld();
	}

	DWORD WINAPI Init(void* const(param))
	{
#ifdef _DEBUG
		AllocConsole();
		SetConsoleTitle(L"Wizardry2 Debug Console");
		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);
#endif
		if (MH_Initialize() == MH_OK)
		{
			if (MH_CreateHook(LPVOID(Addresses::EnterWorld), &DetourOnEnterWorld, reinterpret_cast<LPVOID*>(&FpOnEnterWorld)) == MH_OK
				&& MH_CreateHook(LPVOID(Addresses::OnUpdate), &DetourOnUpdate, reinterpret_cast<LPVOID*>(&FpOnUpdate)) == MH_OK)
				if (MH_EnableHook(nullptr) == MH_OK)
				{
#ifdef _DEBUG
					printf("Hooked OnUpdate\n");
					printf("Hooked OnEnterWorld\n");
#endif

					while (1 & !GetAsyncKeyState(VK_F4))
						Sleep(1);

					ShouldUnRegisterLua = true;

					if (MH_DisableHook(nullptr) == MH_OK)
					{
#ifdef _DEBUG
						printf("Hooks disabled...trying to uninitialize...\n");
						Sleep(3000);
#endif
					}
				}
			if (MH_Uninitialize() == MH_OK)
			{
#ifdef _DEBUG
				printf("Uninitialize succsessful..detaching...\n");
				Sleep(3000);
#endif
			}
		}
#ifdef _DEBUG
		const auto conHandle = GetConsoleWindow();
		FreeConsole();
		PostMessage(conHandle, WM_CLOSE, 0, 0);
#endif
		FreeLibraryAndExitThread(static_cast<HMODULE>(param), NULL);
	}
}
