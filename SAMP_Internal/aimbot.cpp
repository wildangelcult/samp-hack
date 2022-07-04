#include "aimbot.h"

const double PI = 3.14159265358979323846;

void sinCos(float radians, float* sine, float* cosine)
{
    *sine = sin(radians);
    *cosine = cos(radians);
}

void angleVectors(Vector3 angles, Vector3* forward) {
    float sp, sy, cp, cy;

    sinCos(angles.y, &sy, &cy);
    sinCos(angles.x, &sp, &cp);

    forward->x = cp * cy;
    forward->y = cp * sy;
    forward->z = -sp;
}


float AIMBOT::getFov(Vector3 aimAngle) {
    Vector3 ang, aim;

    angleVectors({ G::cam->alpha, G::cam->beta, 0 }, &aim);
    angleVectors(aimAngle, &ang);

    float dotProduct = ang.x * aim.x + ang.y * aim.y + ang.z * aim.z;
    float lengthSquared = aim.x * aim.x + aim.y * aim.y + aim.z * aim.z;

    return acos(dotProduct / lengthSquared) * (180 / PI);
}

Vector3 AIMBOT::calcAngle(actor_info *target) {
    Vector3 localPos = G::localplayerPtr->actor->gtaPed->max->pos;
    Vector3 posTarget = target->max->pos;

    if (G::config.aimbot.prediction) {
        posTarget += target->speed * G::config.aimbot.predictionLvl;
    }

    posTarget.z += G::config.aimbot.heightChange;

    //                                                                                                  maybe fabs
    Vector3 delta = { fabs(G::cam->cameraPos.x - posTarget.x), fabs(G::cam->cameraPos.y - posTarget.y), G::cam->cameraPos.z - posTarget.z };
    float delta2DLength = sqrt(delta.x * delta.x + delta.y * delta.y);
    float alpha = asin(delta.x / delta2DLength);
    float beta = acos(delta.x / delta2DLength);
    if ((localPos.x > posTarget.x) && (localPos.y < posTarget.y)) { beta = -beta; }//1 part
    if ((localPos.x > posTarget.x) && (localPos.y > posTarget.y)) { beta = beta; }//2 part
    if ((localPos.x < posTarget.x) && (localPos.y > posTarget.y)) { beta = (alpha + (1.5707)); }//3 part
    if ((localPos.x < posTarget.x) && (localPos.y < posTarget.y)) { beta = (-alpha - (1.5707)); }//4 part

    float pitch = atan2f(delta2DLength, delta.z) - 3.1415926 / 2;

    if (G::cam->mode == 53 || G::cam->mode == 55) {
        /*if (G::cam->fov == 50) {
            pitch -= 0.07f;
            beta += 0.03f;
        }
        else {
            pitch -= 0.1f;
            beta += 0.044f;
        }*/

        pitch -= G::cam->fov * 0.1f / 70;
        beta += G::cam->fov * 0.044f / 70;
    }

    return { pitch, beta, 0 };
}

actor_info* AIMBOT::getEnemy() {
    unsigned int i = 0;

    float currFov;
    float lowestFov = G::config.aimbot.fov;
    remoteplayer* currentPlayer;
    actor_info* result = nullptr;

    for (i = 0; i <= G::samp->poolsPtr->playerpoolPtr->maxID; ++i) {
        if (i == G::samp->poolsPtr->playerpoolPtr->localID)
            continue;

        if (!(currentPlayer = G::samp->poolsPtr->playerpoolPtr->remoteplayersPtrs[i]) || !G::samp->poolsPtr->playerpoolPtr->isListed[i])
            continue;

        if (!currentPlayer->data->actor || !(currentPlayer->data->actor->gtaPed->hp > 0))
            continue;

        if (G::config.aimbot.dontShootMates && currentPlayer->data->teamID == G::localplayerPtr->teamID)
            continue;

        currFov = getFov(calcAngle(currentPlayer->data->actor->gtaPed));
        if (currFov < lowestFov) {
            lowestFov = currFov;
            result = currentPlayer->data->actor->gtaPed;
        }
    }

    return result;
}

void AIMBOT::aim() {
    actor_info* target = getEnemy();
    if (target) {
        Vector3 angle = calcAngle(target);
        if (G::config.aimbot.smoothAim) {
            Vector3 viewangles = { G::cam->alpha, G::cam->beta, 0 };
            Vector3 delta = angle - viewangles;
            delta.correctAngles();
            angle = viewangles + delta * (G::config.aimbot.smoothSpeed / 100);
            angle.correctAngles();
            G::cam->alpha = angle.x;
            G::cam->beta = angle.y;
        }
        else {
            G::cam->alpha = angle.x;
            G::cam->beta = angle.y;
        }
    }
}