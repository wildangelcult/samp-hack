#pragma once
#include "dx.h"
#include "global.h"
#include "config.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

typedef LRESULT(CALLBACK* tWndProc)(HWND, UINT, WPARAM, LPARAM);

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace GUI {
	void init();
	void frame();
	void shutdown();
};