#include "checkCollision.h"

bool checkObstacleCollision(const SDL_Rect& ninjaRect, int& score, bool& shieldActive, Uint32& shieldStartTime,bool jumping) {
    for (auto it = obstacle::getObstacles().begin(); it != obstacle::getObstacles().end();) {
        SDL_Rect obsRect = it->getRect();
        if (SDL_HasIntersection(&ninjaRect, &obsRect)) {
            if (it->getType() == obstacleType::ROPE) { ++it; continue; }
            if (it->getType() == obstacleType::BIRD && jumping) {
                Mix_PlayChannel(-1, hitSound, 0);
                it = obstacle::getObstacles().erase(it);
                score++;
                obstacle::birdExists = false;
                continue;
            }
            if (it->getType() == obstacleType::SHIELD) {
                Mix_PlayChannel(-1, powerupSound, 0);
                it = obstacle::getObstacles().erase(it);
                shieldActive = true;
                shieldStartTime = SDL_GetTicks();
                continue;
            }
            if (shieldActive) {
                Mix_PlayChannel(-1, thudSound, 0);
                if (it->getType() == obstacleType::BIRD) obstacle::birdExists = false;
                it = obstacle::getObstacles().erase(it);
                shieldActive = false;
                continue;
            }
            return true;
        }
        else {
            ++it;
        }
    }
    return false;
}

bool checkSquirrelCollision(const SDL_Rect& ninjaRect, int& score, bool& shieldActive,bool jumping) {
    for (auto it = obstacle::getSquirrels().begin(); it != obstacle::getSquirrels().end();) {
        SDL_Rect rect = it->getRect();
        if (SDL_HasIntersection(&ninjaRect, &rect)) {
            if (jumping || shieldActive) {
                Mix_PlayChannel(-1, hitSound, 0);
                it = obstacle::getSquirrels().erase(it);
                score++;
                shieldActive = false;
                continue;
            }
            obstacle::squirrelExists = false;
            return true;
        }
        else {
            ++it;
        }
    }
    return false;
}

bool checkBladeCollision(const SDL_Rect& ninjaRect, int& score, bool& shieldActive,bool jumping) {
    for (auto it = obstacle::getBlades().begin(); it != obstacle::getBlades().end();) {
        SDL_Rect rect = it->getRect();
        if (SDL_HasIntersection(&ninjaRect, &rect)) {
            if (jumping || shieldActive) {
                Mix_PlayChannel(-1, hitSound, 0);
                it = obstacle::getBlades().erase(it);
                score++;
                shieldActive = false;
                continue;
            }
            return true;
        }
        else {
            ++it;
        }
    }
    return false;
}