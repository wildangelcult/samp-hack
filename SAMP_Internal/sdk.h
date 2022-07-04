#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include "vector.h"
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}
#define DEFINE_MEMBER_0(type, name, offset) type name

#define SAMP_MAX_PLAYERS 1004

extern std::vector<std::string> weaponNames;

enum PlayerState
{
	PLAYER_STATE_NONE = 0,
	PLAYER_STATE_ONFOOT = 17,
	PLAYER_STATE_PASSENGER,
	PLAYER_STATE_DRIVER,
	PLAYER_STATE_WASTED = 32,
	PLAYER_STATE_SPAWNED
};

enum Gamestate
{
	GAMESTATE_WAIT_CONNECT = 9,
	GAMESTATE_CONNECTING = 13,
	GAMESTATE_AWAIT_JOIN = 15,
	GAMESTATE_CONNECTED = 14,
	GAMESTATE_RESTARTING = 18
};

enum eWeaponType
{
	WEAPONTYPE_UNARMED = 0,
	WEAPONTYPE_BRASSKNUCKLE,
	WEAPONTYPE_GOLFCLUB,
	WEAPONTYPE_NIGHTSTICK,
	WEAPONTYPE_KNIFE,
	WEAPONTYPE_BASEBALLBAT,
	WEAPONTYPE_SHOVEL,
	WEAPONTYPE_POOL_CUE,
	WEAPONTYPE_KATANA,
	WEAPONTYPE_CHAINSAW,

	// gifts
	WEAPONTYPE_DILDO1, // 10
	WEAPONTYPE_DILDO2,
	WEAPONTYPE_VIBE1,
	WEAPONTYPE_VIBE2,
	WEAPONTYPE_FLOWERS,
	WEAPONTYPE_CANE,

	WEAPONTYPE_GRENADE,
	WEAPONTYPE_TEARGAS,
	WEAPONTYPE_MOLOTOV,
	WEAPONTYPE_ROCKET,
	WEAPONTYPE_ROCKET_HS, // 20
	WEAPONTYPE_FREEFALL_BOMB,

	// FIRST SKILL WEAPON
	WEAPONTYPE_PISTOL,			// handguns
	WEAPONTYPE_PISTOL_SILENCED,
	WEAPONTYPE_DESERT_EAGLE,
	WEAPONTYPE_SHOTGUN,			// shotguns
	WEAPONTYPE_SAWNOFF_SHOTGUN,	// one handed
	WEAPONTYPE_SPAS12_SHOTGUN,
	WEAPONTYPE_MICRO_UZI,		// submachine guns
	WEAPONTYPE_MP5,
	WEAPONTYPE_AK47, // 30  	// machine guns 
	WEAPONTYPE_M4,
	WEAPONTYPE_TEC9,			// this uses stat from the micro_uzi
	// END SKILL WEAPONS

	WEAPONTYPE_COUNTRYRIFLE,	// rifles
	WEAPONTYPE_SNIPERRIFLE,
	WEAPONTYPE_ROCKETLAUNCHER,	// specials
	WEAPONTYPE_ROCKETLAUNCHER_HS,
	WEAPONTYPE_FLAMETHROWER,
	WEAPONTYPE_MINIGUN,
	WEAPONTYPE_REMOTE_SATCHEL_CHARGE,
	WEAPONTYPE_DETONATOR, // 40	// plastic explosive
	WEAPONTYPE_SPRAYCAN,
	WEAPONTYPE_EXTINGUISHER,
	WEAPONTYPE_CAMERA,
	WEAPONTYPE_NIGHTVISION,
	WEAPONTYPE_INFRARED,
	WEAPONTYPE_PARACHUTE,
	WEAPONTYPE_LAST_WEAPONTYPE,

	WEAPONTYPE_ARMOUR,
	// these are possible ways to die
	WEAPONTYPE_RAMMEDBYCAR,
	WEAPONTYPE_RUNOVERBYCAR, // 50
	WEAPONTYPE_EXPLOSION,
	WEAPONTYPE_UZI_DRIVEBY,
	WEAPONTYPE_DROWNING,
	WEAPONTYPE_FALL,
	WEAPONTYPE_UNIDENTIFIED,	// Used for damage being done
	WEAPONTYPE_ANYMELEE,
	WEAPONTYPE_ANYWEAPON,
	WEAPONTYPE_FLARE,

	// Added by us
	WEAPONTYPE_TANK_GRENADE,
};

#pragma pack(1)
class camera {
public:
	union {
		DEFINE_MEMBER_N(short, mode, 0x30);
		DEFINE_MEMBER_N(float, alpha, 0xd0);
		DEFINE_MEMBER_N(float, alphaSpeed, 0xd4);
		DEFINE_MEMBER_N(float, fov, 0xd8);
		DEFINE_MEMBER_N(float, fovSpeed, 0xdc);
		DEFINE_MEMBER_N(float, beta, 0xe0);
		DEFINE_MEMBER_N(float, betaSpeed, 0xe4);
		DEFINE_MEMBER_N(Vector3, forward, 0x1b4);
		DEFINE_MEMBER_N(Vector3, source, 0x1c0);
		DEFINE_MEMBER_N(Vector3, up, 0x1d8);
		DEFINE_MEMBER_N(Vector3, cameraPos, 0x854);
	};
};

#pragma pack(1)
class matrix {
public:
	union {
		DEFINE_MEMBER_N(Vector3, pos, 0x30);
	};
};

#define ACTOR_STATE_DRIVING		50
#define ACTOR_STATE_DYING		54
#define ACTOR_STATE_DEAD		55

#pragma pack(1)
class actor_info {
public:
	union {
		DEFINE_MEMBER_N(matrix*, max, 0x14);
		DEFINE_MEMBER_N(uint16_t, timer, 0x2c);
		DEFINE_MEMBER_N(Vector3, speed, 0x44);
		DEFINE_MEMBER_N(unsigned int, state, 0x530);
		DEFINE_MEMBER_N(float, hp, 0x540);
	};
};

#pragma pack(1)
class ped {
public:
	union {
		DEFINE_MEMBER_N(actor_info*, gtaEnt, 0x40);
		DEFINE_MEMBER_N(actor_info*, gtaPed, 0x2a4);
	};
};

#pragma pack(1)
class localplayer {
public:
	union {
		DEFINE_MEMBER_0(ped*, actor, 0x0);
		DEFINE_MEMBER_N(uint16_t, currVehicleID, 0x14);
		DEFINE_MEMBER_N(Vector3, aimCenterOffset, 0xea);
		DEFINE_MEMBER_N(Vector3, aimPos, 0xf6);
		DEFINE_MEMBER_N(uint8_t, teamID, 0x108);
		DEFINE_MEMBER_N(uint8_t, currWeapon, 0x165);
	};
};

#pragma pack(1)
class remoteplayerdata {
public:
	union {
		DEFINE_MEMBER_0(ped*, actor, 0x0);
		DEFINE_MEMBER_N(uint8_t, teamID, 0x8);
		DEFINE_MEMBER_N(uint8_t, state, 0x9);
		DEFINE_MEMBER_N(Vector3, onFootPos, 0x7b);
		DEFINE_MEMBER_N(Vector3, onFootPosSpeed, 0x87);
		DEFINE_MEMBER_N(Vector3, vehiclePos, 0x93);
		DEFINE_MEMBER_N(Vector3, vehicleSpeed, 0x9f);
		DEFINE_MEMBER_N(uint8_t, onFoot_currWeapon, 0xec);
		DEFINE_MEMBER_N(uint8_t, inCar_currWeapon, 0x142);
		DEFINE_MEMBER_N(uint8_t, passenger_currWeapon, 0x184);
		DEFINE_MEMBER_N(float, armor, 0x1b8);
		DEFINE_MEMBER_N(float, health, 0x1bc);
	};
};

#pragma pack(1)
class remoteplayer {
public:
	union {
		DEFINE_MEMBER_0(remoteplayerdata*, data, 0x0);
		DEFINE_MEMBER_N(int, isNPC, 0x4);
		DEFINE_MEMBER_N(std::string, name, 0x8);
	};
};

#pragma pack(1)
class playerpool {
public:
	union {
		DEFINE_MEMBER_0(unsigned int, maxID, 0x0);
		DEFINE_MEMBER_N(uint16_t, localID, 0x4);
		DEFINE_MEMBER_N(localplayer*, localplayerPtr, 0x22);
		DEFINE_MEMBER_N(remoteplayer*, remoteplayersPtrs[SAMP_MAX_PLAYERS], 0x2e);
		DEFINE_MEMBER_N(int, isListed[SAMP_MAX_PLAYERS], 0xfde);
	};
};

#pragma pack(1)
class pools {
public:
	union {
		DEFINE_MEMBER_N(playerpool*, playerpoolPtr, 0x18);
		DEFINE_MEMBER_N(void*, vehiclepoolPtr, 0x1c);
	};
};

#pragma pack(1)
class stSamp {
public:
	union {
		DEFINE_MEMBER_N(char, ip[257], 0x20);
		DEFINE_MEMBER_N(char, hostname[259], 0x121);
		DEFINE_MEMBER_N(int, port, 0x225);
		DEFINE_MEMBER_N(int, gamestate, 0x3bd);
		DEFINE_MEMBER_N(pools*, poolsPtr, 0x3cd);
	};
};



#pragma pack()