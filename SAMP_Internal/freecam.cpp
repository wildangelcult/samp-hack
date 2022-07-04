#include "freecam.h"

void FREECAM::patch() {
	mem::Nop((BYTE*)(G::gtaBase + 0x124266), 2);
	mem::Nop((BYTE*)(G::gtaBase + 0x124274), 3);
	mem::Nop((BYTE*)(G::gtaBase + 0x12428F), 3);
	mem::Nop((BYTE*)(G::gtaBase + 0x120657), 3);

	mem::Nop((BYTE*)(G::gtaBase + 0x120643), 3);
	mem::Nop((BYTE*)(G::gtaBase + 0x120646), 3);
	mem::Nop((BYTE*)(G::gtaBase + 0x10D06A), 3);

	mem::Nop((BYTE*)(G::gtaBase + 0x125BDF), 2);
	mem::Nop((BYTE*)(G::gtaBase + 0x125BED), 3);
	mem::Nop((BYTE*)(G::gtaBase + 0x125C06), 3);

	G::freecamPatched = true;
}

void FREECAM::restore() {
	mem::Patch((BYTE*)(G::gtaBase + 0x124266), (BYTE*)"\x89\x02", 2);
	mem::Patch((BYTE*)(G::gtaBase + 0x124274), (BYTE*)"\x89\x4A\x04", 3);
	mem::Patch((BYTE*)(G::gtaBase + 0x12428F), (BYTE*)"\x89\x42\x08", 3);
	mem::Patch((BYTE*)(G::gtaBase + 0x120657), (BYTE*)"\x89\x4D\x08", 3);

	mem::Patch((BYTE*)(G::gtaBase + 0x120643), (BYTE*)"\x89\x55\x00", 3);
	mem::Patch((BYTE*)(G::gtaBase + 0x120646), (BYTE*)"\x89\x45\x04", 3);
	mem::Patch((BYTE*)(G::gtaBase + 0x10D06A), (BYTE*)"\xD9\x58\x08", 3);

	mem::Patch((BYTE*)(G::gtaBase + 0x125BDF), (BYTE*)"\x89\x08", 2);
	mem::Patch((BYTE*)(G::gtaBase + 0x125BED), (BYTE*)"\x89\x50\x04", 3);
	mem::Patch((BYTE*)(G::gtaBase + 0x125C06), (BYTE*)"\x89\x48\x08", 3);

	G::freecamPatched = false;
}

void FREECAM::handle() {
	if (G::config.misc.freecam && !G::freecamPatched) {
		patch();
	}

	if (!G::config.misc.freecam && G::freecamPatched) {
		restore();
	}

	if (G::config.misc.freecam) {
		//forward
		if (GetAsyncKeyState(VK_NUMPAD8)) {
			G::cam->source += G::cam->forward * G::config.misc.freecamSpeed;
		}

		//backward
		if (GetAsyncKeyState(VK_NUMPAD5)) {
			G::cam->source -= G::cam->forward * G::config.misc.freecamSpeed;
		}

		//up
		if (GetAsyncKeyState(VK_NUMPAD9)) {
			G::cam->source += G::cam->up * G::config.misc.freecamSpeed;
		}

		//down
		if (GetAsyncKeyState(VK_NUMPAD6)) {
			G::cam->source -= G::cam->up * G::config.misc.freecamSpeed;
		}
	}
}