#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "dx.h"

#include "global.h"

#include "vector.h"

#define ABS(x) ((x < 0) ? (-(x)) : (x))

extern const int FONT_HEIGHT;

namespace colors {
	const D3DCOLOR red = D3DCOLOR_ARGB(255, 255, 0, 0);
	const D3DCOLOR green = D3DCOLOR_ARGB(255, 0, 255, 0);
	const D3DCOLOR blue = D3DCOLOR_ARGB(255, 0, 0, 255);
	const D3DCOLOR white = D3DCOLOR_ARGB(255, 255, 255, 255);
	const D3DCOLOR black = D3DCOLOR_ARGB(255, 0, 0, 0);
	const D3DCOLOR gray = D3DCOLOR_ARGB(255, 55, 55, 55);
	const D3DCOLOR light_gray = D3DCOLOR_ARGB(255, 192, 192, 192);
}

long map(long x, long in_min, long in_max, long out_min, long out_max);
float map(float x, float in_min, float in_max, float out_min, float out_max);

namespace DRAW {
	void filledRect(int x, int y, int width, int height, D3DCOLOR color);
	void line(int from_x, int from_y, int to_x, int to_y, int lineWidth, D3DCOLOR color);
	void line(Vector2 from, Vector2 to, int lineWidth, D3DCOLOR color);
	void outline(Vector2 top_left, Vector2 top_right, Vector2 bottom_right, Vector2 bottom_left, int lineWidth, D3DCOLOR color);
	void outline(int x, int y, int width, int height, int space, int lineWidth, D3DCOLOR color);
	void text(const char* text, float x, float y, D3DCOLOR color);
	void release();
};