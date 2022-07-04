#include "draw.h"

ID3DXLine* lineL = NULL;
ID3DXFont* fontF = NULL;
const int FONT_HEIGHT = 14;

void DRAW::filledRect(int x, int y, int width, int height, D3DCOLOR color) {
	D3DRECT rect = { x, y, x + width, y + height };
	G::devicePtr->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void DRAW::line(int from_x, int from_y, int to_x, int to_y, int lineWidth, D3DCOLOR color) {
	
	if (!lineL)
		D3DXCreateLine(G::devicePtr, &lineL);

	D3DXVECTOR2 line[2];
	line[0] = D3DXVECTOR2(from_x, from_y);
	line[1] = D3DXVECTOR2(to_x, to_y);
	lineL->SetWidth(lineWidth);
	lineL->Draw(line, 2, color);
}

void DRAW::line(Vector2 from, Vector2 to, int lineWidth, D3DCOLOR color) {
	line(from.x, from.y, to.x, to.y, lineWidth, color);
}

void DRAW::outline(Vector2 top_left, Vector2 top_right, Vector2 bottom_right, Vector2 bottom_left, int lineWidth, D3DCOLOR color) {
	line(top_left, top_right, lineWidth, color);
	line(bottom_left, bottom_right, lineWidth, color);
	line(top_left, bottom_left, lineWidth, color);
	line(top_right, bottom_right, lineWidth, color);
}

void DRAW::outline(int x, int y, int width, int height, int space, int lineWidth, D3DCOLOR color) {
	line(x + space, y + space, x + width - space, y + space, lineWidth, color);
	line(x + width - space, y + space, x + width - space, y + height - space, lineWidth, color);
	line(x + width - space, y + height - space, x + space, y + height - space, lineWidth, color);
	line(x + space, y + height - space, x + space, y + space, lineWidth, color);
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void DRAW::text(const char* text, float x, float y, D3DCOLOR color) {
	RECT rect;

	if (!fontF) {
		D3DXCreateFont(G::devicePtr, FONT_HEIGHT, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Consolas", &fontF);
	}

	SetRect(&rect, x + 1, y + 1, x + 1, y + 1);
	fontF->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

	SetRect(&rect, x , y, x, y);
	fontF->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, color);
}

void DRAW::release() {
	if (lineL) lineL->Release();
	if (fontF) fontF->Release();
}