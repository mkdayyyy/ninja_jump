#pragma once
#include "commonFunc.h"

bool checkObstacleCollision(const SDL_Rect& ninjaRect, int& score, bool& shieldActive, Uint32& shieldStartTime, bool jumping);
bool checkSquirrelCollision(const SDL_Rect& ninjaRect, int& score, bool& shieldActive, bool jumping);
bool checkBladeCollision(const SDL_Rect& ninjaRect, int& score, bool& shieldActive, bool jumping);
