#include "global.h"

bool G::guiInitialized = false;
bool G::menuVisible = true;

uintptr_t G::gtaBase = (uintptr_t)GetModuleHandle("gta_sa.exe");
uintptr_t G::sampBase = (uintptr_t)GetModuleHandle("samp.dll");
camera* G::cam = (camera*)(mem::FindDMAAddy(G::gtaBase + 0x1542F4, { 0x0 }) - 0x4c);
stSamp* G::samp = (stSamp*)mem::FindDMAAddy(G::sampBase + 0x21A0F8, { 0x0 });
bool* G::bOptionsOpened = (bool*)(G::gtaBase + 0x76B964);
localplayer* G::localplayerPtr = nullptr;
uint8_t* G::radio = (uint8_t*)(G::gtaBase + 0x4CB7A5);
uint8_t* G::chatOpen = (uint8_t*)mem::FindDMAAddy(G::sampBase + 0x21A10C, { 0x54 });

LPDIRECT3DDEVICE9 G::devicePtr = nullptr;
int G::windowWidth = *(int*)(G::gtaBase + 0x817044);
int G::windowHeight = *(int*)(G::gtaBase + 0x817044 + 4);

tConfig G::config;

bool G::freecamPatched = false;