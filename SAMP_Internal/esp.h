#pragma once
#include "dx.h"
#include "draw.h"
#include "sdk.h"
#include "global.h"
#include "geom.h"

#define GAME_UNIT_MAGIC 100
#define VIRTUAL_SCREEN_WIDTH 800
#define PLAYER_HEIGHT 2.f
#define PLAYER_WIDTH 1.f;
const float PLAYER_ASPECT_RATIO = PLAYER_HEIGHT / PLAYER_WIDTH;
namespace ESP {
	void allInOne(remoteplayer* player);
	void draw();
};