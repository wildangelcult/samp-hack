#include "dx.h"

BOOL CALLBACK enumWins(HWND hWin, LPARAM lp) {
	DWORD pid;
	GetWindowThreadProcessId(hWin, &pid);
	if (GetCurrentProcessId() != pid) return TRUE;

	hWindow = hWin;
	return FALSE;
}

HWND getProcessWindow() {
	hWindow = NULL;

	EnumWindows(enumWins, NULL);

	return hWindow;
}

bool getD3D9Device(void** pTable, size_t size) {
	if (!pTable) return false;

	IDirect3D9* D3DPtr = Direct3DCreate9(D3D_SDK_VERSION);

	if (!D3DPtr) return false;

	IDirect3DDevice9* dummyDevicePtr = nullptr;

	D3DPRESENT_PARAMETERS d3dPresParams = {};
	d3dPresParams.Windowed = false;
	d3dPresParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPresParams.hDeviceWindow = getProcessWindow();

	HRESULT dummyDeviceCreate = D3DPtr->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dPresParams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPresParams, &dummyDevicePtr);

	if (dummyDeviceCreate != S_OK) {
		d3dPresParams.Windowed = true;
		HRESULT dummyDeviceCreate = D3DPtr->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dPresParams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPresParams, &dummyDevicePtr);

		if (dummyDeviceCreate != S_OK) {
			D3DPtr->Release();
			return false;
		}
	}

	/*
	D3DDISPLAYMODE displayMode{ 0 };
	if (D3DPtr->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode) == D3D_OK) {
		windowWidth = displayMode.Width;
		windowHeight = displayMode.Height;
	}*/


	memcpy(pTable, *(void***)(dummyDevicePtr), size);
	dummyDevicePtr->Release();
	D3DPtr->Release();
	return true;
}