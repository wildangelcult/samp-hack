#include "esp.h"

void ESP::allInOne(remoteplayer* player) {
	Vector3 center3D = player->data->actor->gtaPed->max->pos, center2D;
	Vector3 topPos3D = center3D, botPos3D = center3D, topPos2D, botPos2D;
	center3D.z -= 0.1;
	topPos3D.z += 0.82;
	botPos3D.z -= 1.1;
	if (world2screen((D3DXVECTOR3*)&center3D, (D3DXVECTOR3*)&center2D) && world2screen((D3DXVECTOR3*)&topPos3D, (D3DXVECTOR3*)&topPos2D) && world2screen((D3DXVECTOR3*)&botPos3D, (D3DXVECTOR3*)&botPos2D)) {
		float height = botPos2D.y - topPos2D.y;
		float width = height / PLAYER_ASPECT_RATIO;
		float x = center2D.x - width / 2;
		float y = center2D.y - height / 2;
		if (G::config.esp.ESPBox) {
			if (G::config.esp.mateBox) {
				DRAW::outline(x, y, width, height, 0, 2, (G::localplayerPtr->teamID == player->data->teamID) ? G::config.esp.calcColors.mateBoxColor : G::config.esp.calcColors.ESPBoxColor);
			}
			else {
				DRAW::outline(x, y, width, height, 0, 2, G::config.esp.calcColors.ESPBoxColor);
			}
		}

		if (G::config.esp.healthESP) {
			float healthPer = player->data->health / 100.f;
			DRAW::line(x + width + 6, y + height, x + width + 6, y + height * (1 - healthPer), 4, G::config.esp.calcColors.healthESPColor);
		}

		if (G::config.esp.armorESP) {
			float armorPer = player->data->armor / 100.f;
			DRAW::line(x - 6, y + height, x - 6, y + height * (1 - armorPer), 4, G::config.esp.calcColors.armorESPColor);
		}

		if (G::config.esp.nameESP) {
			DRAW::text(player->name.c_str(), x + width / 2, y - FONT_HEIGHT - 3, G::config.esp.calcColors.nameESPColor);
		}

		if (G::config.esp.snapLines) {
			Vector3 localPos3D = G::localplayerPtr->actor->gtaPed->max->pos, localPos2D;
			if (world2screen((D3DXVECTOR3*)&localPos3D, (D3DXVECTOR3*)&localPos2D)) {
				DRAW::line(localPos2D.x, localPos2D.y, center2D.x, center2D.y, 2, G::config.esp.calcColors.snapLinesColor);
			}
		}

		if (G::config.esp.weaponESP) {
			if (player->data->state == PLAYER_STATE_ONFOOT) {
				DRAW::text(weaponNames[player->data->onFoot_currWeapon].c_str(), botPos2D.x, botPos2D.y, G::config.esp.calcColors.weaponESPColor);
			}
			else if (player->data->state == PLAYER_STATE_DRIVER) {
				DRAW::text(weaponNames[player->data->inCar_currWeapon].c_str(), botPos2D.x, botPos2D.y, G::config.esp.calcColors.weaponESPColor);
			}
			else if (player->data->state == PLAYER_STATE_PASSENGER) {
				DRAW::text(weaponNames[player->data->passenger_currWeapon].c_str(), botPos2D.x, botPos2D.y, G::config.esp.calcColors.weaponESPColor);
			}
		}
	}
}

void ESP::draw() {
	unsigned int i = 0;
	remoteplayer* currentPlayer;
	for (i = 0; i <= G::samp->poolsPtr->playerpoolPtr->maxID; ++i) {
		if (i == G::samp->poolsPtr->playerpoolPtr->localID)
			continue;

		if (!(currentPlayer = G::samp->poolsPtr->playerpoolPtr->remoteplayersPtrs[i]) || !G::samp->poolsPtr->playerpoolPtr->isListed[i])
			continue;

		if (!currentPlayer->data->actor || !(currentPlayer->data->actor->gtaPed->hp > 0))
			continue;

		allInOne(currentPlayer);
	}
}