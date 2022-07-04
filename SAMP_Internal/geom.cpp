#include "geom.h"
/*
bool world2screen(Vector3 pos, Vector2& screen) {
	Vector4 clipCoords;
	clipCoords.x = pos.x * G::viewmatrix[0] + pos.y * G::viewmatrix[1] + pos.z * G::viewmatrix[2] + G::viewmatrix[3];
	clipCoords.y = pos.x * G::viewmatrix[4] + pos.y * G::viewmatrix[5] + pos.z * G::viewmatrix[6] + G::viewmatrix[7];
	clipCoords.z = pos.x * G::viewmatrix[8] + pos.y * G::viewmatrix[9] + pos.z * G::viewmatrix[10] + G::viewmatrix[11];
	clipCoords.w = pos.x * G::viewmatrix[12] + pos.y * G::viewmatrix[13] + pos.z * G::viewmatrix[14] + G::viewmatrix[15];

	if (clipCoords.w < 0.1f) {
		return false;
	}

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (G::windowWidth / 2 * NDC.x) + (NDC.x + G::windowWidth / 2);
	screen.y = -(G::windowHeight / 2 * NDC.y) + (NDC.y + G::windowHeight / 2);
	return true;
}*/

bool world2screen(D3DXVECTOR3* pos, D3DXVECTOR3* out) {
	D3DVIEWPORT9 viewPort;
	D3DXMATRIX view, projection, world;

	G::devicePtr->GetViewport(&viewPort);
	G::devicePtr->GetTransform(D3DTS_VIEW, &view);
	G::devicePtr->GetTransform(D3DTS_PROJECTION, &projection);
	D3DXMatrixIdentity(&world);

	D3DXVec3Project(out, pos, &viewPort, &projection, &view, &world);
	if (out->z < 1) {
		return true;
	}
	return false;
}

float calc3DDistance(Vector3 src, Vector3 dst) {
	return sqrt(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2) + pow(src.z - dst.z, 2));
}

float calc2DDistance(Vector2 src, Vector2 dst) {
	return sqrt(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2));
}