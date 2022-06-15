#pragma once
#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_dx9.h"
#include "ImGui\imgui_impl_win32.h"
#include <d3d9.h>
#include <tchar.h>
#include <Windows.h>
#include "XorStr.h"

class Menu
{
public:
	DWORD CreateAppWindow();
	void MainMenu();

	void Start();
	void End();
};
