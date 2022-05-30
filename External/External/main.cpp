#include <thread>
#include "bf4.h"
#include "menu.h"

bool Active = true;

Menu GUI = Menu();
BF BF4 = BF();

int main()
{
	BF4.GetProcessHandle();	// Get pHandle
	GUI.Start();	// Start Menu

	while (Active)
	{
		BF4.RecoilSpread();
		BF4.UnlockAll();
		BF4.DamageHack();
		Sleep(500);
	}

	GUI.End();
	return 0;
}
