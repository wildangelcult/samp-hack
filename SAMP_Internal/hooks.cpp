#include "hooks.h"
#include <iostream>

void* d3d9Devices[119];
tEndScene oEndScene;
uint16_t prevLocalTimer = 0;
void APIENTRY hEndScene(LPDIRECT3DDEVICE9 oDevicePtr) {
    if (!G::devicePtr) {
        G::devicePtr = oDevicePtr;
    }

    if (!G::guiInitialized) GUI::init();

    if (*G::bOptionsOpened || prevLocalTimer != G::localplayerPtr->actor->gtaPed->timer) {
        if (G::menuVisible) GUI::frame();
        if (G::config.esp.ESPBox || G::config.esp.healthESP || G::config.esp.armorESP || G::config.esp.nameESP || G::config.esp.snapLines || G::config.esp.weaponESP)
            ESP::draw();

    }
    prevLocalTimer = G::localplayerPtr->actor->gtaPed->timer;

    if (G::samp->gamestate == GAMESTATE_CONNECTED && G::localplayerPtr->actor->gtaPed->state != ACTOR_STATE_DYING && G::localplayerPtr->actor->gtaPed->state != ACTOR_STATE_DEAD) {
        if (G::config.aimbot.enabled) {
            if (GetAsyncKeyState(G::config.aimbot.aimKey)) {
                AIMBOT::aim();
            }
        }

        FREECAM::handle();
    }
    oEndScene(G::devicePtr);
}


void HOOKS::hook() {
    if (getD3D9Device(d3d9Devices, sizeof(d3d9Devices))) {
        oEndScene = (tEndScene)mem::TrampHook32((BYTE*)d3d9Devices[42], (BYTE*)hEndScene, 7);
    }
}

void HOOKS::unhook() {
    mem::Patch((BYTE*)d3d9Devices[42], (BYTE*)oEndScene, 7);
}