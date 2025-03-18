#include "ninja.h"

SDL_Texture* ninja::ninjaRunTextures[3] = { nullptr,nullptr,nullptr };
SDL_Texture* ninja::ninjaJumpTextures[4] = { nullptr,nullptr,nullptr,nullptr };

ninja::ninja(int x, int y) :x(x), y(y), onTheLeft(true), isIntro(true), introProgress(0.0), jumpProgress(0.0) {
	//ham khoi tao
}

void ninja::handleInput(SDL_Event& e, bool& jumping) {
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && !jumping) {
		jumping = true;
		jumpProgress = 0.0;
		Mix_PlayChannel(-1, jumpSound, 0);
	}
}

void ninja::update(float deltaTime, bool& jumping) {
	if (isIntro) {
		updateIntro(deltaTime);
	}
	if (jumping) {
		updateJump(deltaTime, jumping);
	}
	animate(jumping);
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

bool ninja::getOnTheLeft() const {
	return onTheLeft;
}

void ninja::loadTextures(SDL_Renderer* renderer) {
	// load hinh anh ninja run
	ninjaRunTextures[0] = loadTexture("res/run/1.png", renderer);
	ninjaRunTextures[1] = loadTexture("res/run/2.png", renderer);
	ninjaRunTextures[2] = loadTexture("res/run/3.png", renderer);

	// load hinh anh ninja jump
	ninjaJumpTextures[0] = loadTexture("res/run/7.png", renderer);
	ninjaJumpTextures[1] = loadTexture("res/run/8.png", renderer);
	ninjaJumpTextures[2] = loadTexture("res/run/9.png", renderer);
	ninjaJumpTextures[3] = loadTexture("res/run/10.png", renderer);
}

void ninja::render(SDL_Renderer* renderer, bool jumping) {
	SDL_Rect dstRect;
	SDL_RendererFlip flip = onTheLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;;
	if (jumping) {
		dstRect = { x,y,88,62 };
		SDL_RenderCopyEx(renderer, ninjaJumpTextures[frameIndex], NULL, &dstRect, 0, NULL, flip);
	}
	else {
		dstRect = { x, y, 30, 60 };
		SDL_RenderCopyEx(renderer, ninjaRunTextures[frameIndex], NULL, &dstRect, 0, NULL, flip);
	}
}

void ninja::animate(bool jumping) {
	static int count = 0;
	count++;
	if (count > animationSpeed) {
		if (jumping) {
			frameIndex = (frameIndex + 1) % 4; // 4 frames cho nhảy
		}
		else {
			frameIndex = (frameIndex + 1) % 3; // 3 frames cho chạy
		}
		count = 0;
	}
}

int ninja::getX() const {
	return x;
}