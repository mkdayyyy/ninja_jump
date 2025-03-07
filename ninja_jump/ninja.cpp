#include "ninja.h"

ninja::ninja(int x, int y) :x(x), y(y), onTheLeft(true), isIntro(true), introProgress(0.0), jumpProgress(0.0) {
	//ham khoi tao
}

void ninja::handleInput(SDL_Event& e, bool& jumping) {
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && !jumping) {
		jumping = true;
		jumpProgress = 0.0;
	}
}

void ninja::update(float deltaTime, bool& jumping) {
	if (isIntro) {
		updateIntro(deltaTime);
	}
	if (jumping) {
		updateJump(deltaTime, jumping);
	}
}

void ninja::updateIntro(float deltaTime) {
	introProgress += deltaTime / INTRO_DURATION;
	int distance = 150;
	y = static_cast<int>((WINDOW_HEIGHT - NINJA_SIZE) - introProgress * distance);
	if (introProgress >= 1) {
		isIntro = false;
		y = 400;
	}
}

void ninja::updateJump(float deltaTime, bool& jumping) {
	jumpProgress += deltaTime / JUMP_DURATION;
	int distance = WINDOW_WIDTH - 2 * WALL_WIDTH - NINJA_SIZE;

	if (onTheLeft) {
		x = static_cast<int>(WALL_WIDTH + distance * jumpProgress);
	}
	else {
		x = static_cast<int>((WINDOW_WIDTH - WALL_WIDTH - NINJA_SIZE) - distance * jumpProgress);
	}
	if (jumpProgress >= 1) {
		jumping = false;
		jumpProgress = 0.0;
		onTheLeft = !onTheLeft;
		x = onTheLeft ? WALL_WIDTH : WINDOW_WIDTH - WALL_WIDTH - NINJA_SIZE;
	}
}

SDL_Rect ninja::getRect() const {
	return { x, y, NINJA_SIZE, NINJA_SIZE };
}