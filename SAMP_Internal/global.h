#pragma once
#include <Windows.h>
#include <cstdint>
#include "dx.h"
#include "mem.h"
#include "sdk.h"
#define FLOATARR_2_D3DCOLOR(color) (D3DCOLOR_COLORVALUE(color[0], color[1], color[2], color[3]))

struct tConfig {
	struct {
		bool enabled = false;
		DWORD aimKey = VK_LMENU;
		bool dontShootMates = false;
		float heightChange = 0.f;
		float fov = 180.f;
		bool prediction = false;
		unsigned int predictionLvl = 6;
		bool smoothAim = false;
		float smoothSpeed = 10.f;
	} aimbot;

	struct {
		bool ESPBox = false;
		float ESPBoxColor[4] = { 1.f, 0.f, 0.f, 1.f };
		bool mateBox = false;
		float mateBoxColor[4] = { 0.f, 1.f, 0.f, 1.f };
		bool snapLines = false;
		float snapLinesColor[4] = { 1.f, 0.f, 0.f, 1.f };
		bool healthESP = false;
		float healthESPColor[4] = { 1.f, 0.f, 0.f, 1.f };
		bool armorESP = false;
		float armorESPColor[4] = { 0.f, 0.f, 1.f, 1.f };
		bool nameESP = false;
		float nameESPColor[4] = { 1.f, 1.f, 1.f, 1.f };
		bool weaponESP = false;
		float weaponESPColor[4] = { 1.f, 1.f, 1.f, 1.f };
		
		struct {
			D3DCOLOR ESPBoxColor = D3DCOLOR_ARGB(255, 255, 0, 0);
			D3DCOLOR mateBoxColor = D3DCOLOR_ARGB(255, 0, 255, 0);
			D3DCOLOR snapLinesColor = D3DCOLOR_ARGB(255, 255, 0, 0);
			D3DCOLOR healthESPColor = D3DCOLOR_ARGB(255, 255, 0, 0);
			D3DCOLOR armorESPColor = D3DCOLOR_ARGB(255, 0, 0, 255);
			D3DCOLOR nameESPColor = D3DCOLOR_ARGB(255, 255, 255, 255);
			D3DCOLOR weaponESPColor = D3DCOLOR_ARGB(255, 255, 255, 255);
		} calcColors;
	} esp;

	struct {
		bool freecam = false;
		float freecamSpeed = 3.f;
		bool autoOffRadio = false;
		bool holdHorn = false;
	} misc;
};

namespace G {
	extern bool guiInitialized;
	extern bool menuVisible;

	extern uintptr_t gtaBase;
	extern uintptr_t sampBase;
	extern bool* bOptionsOpened;
	extern camera* cam;
	extern stSamp* samp;
	extern uint8_t* radio;
	extern uint8_t* chatOpen;

	extern float* viewmatrix;
	extern LPDIRECT3DDEVICE9 devicePtr;
	extern int windowWidth;
	extern int windowHeight;

	extern tConfig config;

	extern localplayer* localplayerPtr;

	extern bool freecamPatched;
};