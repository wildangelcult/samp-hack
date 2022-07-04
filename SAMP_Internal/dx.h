#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

static HWND hWindow;

typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 devicePtr);

bool getD3D9Device(void** pTable, size_t size);
HWND getProcessWindow();