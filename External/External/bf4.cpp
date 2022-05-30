#include "bf4.h"
#include "menu.h"
#include "offset.h"

HANDLE pHandle;
HWND Target;
DWORD PID;
BYTE WriteUnlock = 1;

extern bool NoRecoilSpread;
extern bool Unlock;
extern bool Damage;

extern float WriteRecoilSpread;
extern int BulletPerShot;

bool IsValid(DWORD_PTR ptr)
{
	if (ptr && HIWORD(ptr) != NULL) return true; else return false;
}

void BF::GetProcessHandle()
{
	// Find BF4 Window
    Target = FindWindowA(NULL, "Battlefield 4");
    if (!Target)
    {
        exit(0);
    }
    GetWindowThreadProcessId(Target, &PID);
	// Get pHandle
    pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    if (!pHandle)
    {
        std::exit(0);
    }

	// Hide Console Window
    ShowWindow(GetConsoleWindow(), HIDE_WINDOW);
}

// No Recoil, No Spread
void BF::RecoilSpread()
{
	if (NoRecoilSpread)
	{
		DWORD_PTR Weapon = 0;

		ReadProcessMemory(pHandle, (void*)(OFFSET_WEAPON), &Weapon, sizeof(DWORD_PTR), NULL);
		if (!IsValid(Weapon))
			return;
		ReadProcessMemory(pHandle, (void*)(Weapon + 0x128), &Weapon, sizeof(DWORD_PTR), NULL);
		ReadProcessMemory(pHandle, (void*)(Weapon + 0x30), &Weapon, sizeof(DWORD_PTR), NULL);

		WriteProcessMemory(pHandle, (void*)(Weapon + 0x430), &WriteRecoilSpread, sizeof(float), NULL);
		WriteProcessMemory(pHandle, (void*)(Weapon + 0x438), &WriteRecoilSpread, sizeof(float), NULL);
		WriteProcessMemory(pHandle, (void*)(Weapon + 0x434), &WriteRecoilSpread, sizeof(float), NULL);
		WriteProcessMemory(pHandle, (void*)(Weapon + 0x43C), &WriteRecoilSpread, sizeof(float), NULL);
	}
}

// Unlock All
void BF::UnlockAll()
{
	if (Unlock)
	{
		DWORD_PTR UnlockT = 0;

		ReadProcessMemory(pHandle, (void*)(OFFSET_BFSETTING), &UnlockT, sizeof(DWORD_PTR), NULL);
		if (!IsValid(UnlockT))
			return;
		WriteProcessMemory(pHandle, (void*)(UnlockT + 0x54), &WriteUnlock, sizeof(BYTE), NULL);
	}
}

// Damage Hack
// Tested online until 2
void BF::DamageHack()
{
	if (Damage)
	{
		DWORD_PTR WeaponD = 0;

		ReadProcessMemory(pHandle, (void*)(OFFSET_WEAPON), &WeaponD, sizeof(DWORD_PTR), NULL);
		if (!IsValid(WeaponD))
			return;
		ReadProcessMemory(pHandle, (void*)(WeaponD + 0x128), &WeaponD, sizeof(DWORD_PTR), NULL);
		ReadProcessMemory(pHandle, (void*)(WeaponD + 0x10), &WeaponD, sizeof(DWORD_PTR), NULL);
		WriteProcessMemory(pHandle, (void*)(WeaponD + 0xD8), &BulletPerShot, sizeof(int), NULL);
	}
}