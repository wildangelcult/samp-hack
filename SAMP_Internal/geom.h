#pragma once
#include "vector.h"
#include "global.h"
#include "dx.h"
bool world2screen(D3DXVECTOR3* pos, D3DXVECTOR3* out);

float calc3DDistance(Vector3 src, Vector3 dst);
float calc2DDistance(Vector2 src, Vector2 dst);