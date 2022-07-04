#include <Windows.h>
#include <iostream>
#include <thread>

#include "hooks.h"
#include "global.h"
#include "gui.h"
#include "aimbot.h"

bool exitThreads = false;

void autoOffRadio() {
    INPUT wheelUp = { 0 };
    INPUT wheelDown = { 0 };
    wheelUp.type = wheelDown.type = INPUT_MOUSE;
    wheelUp.mi.dwFlags = wheelDown.mi.dwFlags = MOUSEEVENTF_WHEEL;
    wheelUp.mi.mouseData = WHEEL_DELTA;
    wheelDown.mi.mouseData = -WHEEL_DELTA;

    while (!exitThreads) {
        if (G::config.misc.autoOffRadio) {
            if (*G::chatOpen == 0 && G::localplayerPtr->currVehicleID != 0xFFFF && *G::radio != 13) {
                if (*G::radio <= 6) {
                    SendInput(1, &wheelDown, sizeof(INPUT));
                }
                else {
                    SendInput(1, &wheelUp, sizeof(INPUT));
                }
            }
        }
        Sleep(100);
    }
}

void holdHorn() {
    INPUT in = { 0 };
    in.type = INPUT_KEYBOARD;
    in.ki.wVk = 0x48;

    while (!exitThreads) {
        if (G::config.misc.holdHorn) {
            if (*G::chatOpen == 0 && G::localplayerPtr->currVehicleID != 0xFFFF) {
                in.ki.dwFlags = 0;
                SendInput(1, &in, sizeof(INPUT));
                Sleep(10);
                in.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &in, sizeof(INPUT));
                Sleep(10);
            }
        } 
    }
}

DWORD WINAPI mainThread(HMODULE hModule) {
    //AllocConsole();
    //FILE* f;
    //freopen_s(&f, "CONOUT$", "w", stdout);

    if (!G::samp) {
        while (!G::samp) {
            G::samp = (stSamp*)mem::FindDMAAddy(G::sampBase + 0x21A0F8, { 0x0 });
            Sleep(5);
        }
        Sleep(30000);
    }
    G::localplayerPtr = G::samp->poolsPtr->playerpoolPtr->localplayerPtr;
    G::cam = (camera*)(mem::FindDMAAddy(G::gtaBase + 0x1542F4, { 0x0 }) - 0x4c);
    G::chatOpen = (uint8_t*)mem::FindDMAAddy(G::sampBase + 0x21A10C, { 0x54 });

    std::thread t1(autoOffRadio);
    t1.detach();
    std::thread t2(holdHorn);
    t2.detach();
    
    CONFIG::init();
    HOOKS::hook();

    while (1/*!GetAsyncKeyState(VK_END)*/) {
        if (GetAsyncKeyState(VK_INSERT) & 1) {
            G::menuVisible = !G::menuVisible;
        }

        if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            G::config.misc.freecam = !G::config.misc.freecam;
        }
    }

    exitThreads = true;
    HOOKS::unhook();
    DRAW::release();
    GUI::shutdown();

    //fclose(f);
    //FreeConsole();
    //FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)mainThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}