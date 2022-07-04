#pragma once
#include <cmath>
#include "sdk.h"
#include "vector.h"
#include "global.h"

namespace AIMBOT{
	float getFov(Vector3 aimAngle);
	Vector3 calcAngle(actor_info* target);
	actor_info* getEnemy();
	void aim();
};