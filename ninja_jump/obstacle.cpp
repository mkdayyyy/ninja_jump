﻿#include "obstacle.h"

const int obstacle::OBSTACLE_SIZE = 40;
float obstacle::SPEED = 200.0;
std::vector<obstacle> obstacle::obstacles;
std::vector<obstacle> obstacle::squirrels;
std::vector<obstacle> obstacle::blades;
float obstacle::spawnTime = 0.0;
float obstacle::shieldSpawnTime = 0.0;

bool obstacle::birdExists = false;
bool obstacle::squirrelExists = false;

SDL_Texture* obstacle::ropeTexture = nullptr;
SDL_Texture* obstacle::leftHouseTexture = nullptr;
SDL_Texture* obstacle::rightHouseTexture = nullptr;
SDL_Texture* obstacle::spikeTexture = nullptr;
SDL_Texture* obstacle::shieldTexture = nullptr;
SDL_Texture* obstacle::throwerTexture = nullptr;
SDL_Texture* obstacle::squirrelTextures[4] = { nullptr, nullptr, nullptr, nullptr };
SDL_Texture* obstacle::birdTextures[3] = { nullptr, nullptr, nullptr };
SDL_Texture* obstacle::bladeTextures[4] = { nullptr, nullptr, nullptr, nullptr };

obstacle::obstacle(int x, int y,int w,int h, obstacleType type) : x(x), y(static_cast<float>(y)),width(w),height(h), type(type) {
	// ham khoi tao
	if (type == obstacleType::SQUIRREL) {
		currentTexture = squirrelTextures[0];
	}
	else if (type == obstacleType::BIRD) {
		currentTexture = birdTextures[0];
		freezeTime = 0;
		movingDown = false;
	}
	else if (type == obstacleType::BLADE) {
		currentTexture = bladeTextures[0];
	}
}

void obstacle::update(float deltaTime) {
	if (type == obstacleType::SQUIRREL) {
		if (movingRight) {
			x += 2; // di chuyen sang phai
			if (x + width >= WINDOW_WIDTH - WALL_WIDTH) {
				movingRight = false; // doi huong
			}
		}
		else {
			x -= 2; // di chuyen sang trai
			if (x <= WALL_WIDTH) {
				movingRight = true; // doi huong
			}
		}
		y += (SPEED * deltaTime);
	}
	else if (type == obstacleType::BIRD) {
		if (x ==WALL_WIDTH) {
			birdMovingRight = true;
		}
		else if(x==WINDOW_WIDTH-WALL_WIDTH-35) {
			birdMovingRight = false;
		}
		if (y <= 180) {
			y += (SPEED * deltaTime);
		}
		else {
			if (!movingDown) {
				freezeTime += deltaTime;
				if (freezeTime >= 5.0) {
					movingDown = true;
				}
			}
			else {
				// di chuyen xuong
				if (birdMovingRight) { x += 3; }
				else { x -= 3; }
				y += 2;
			}
		}
	}
	else if (type == obstacleType::BLADE) {
		if (x == WALL_WIDTH - 13) bladeMovingRight = true;
		else if (x == WINDOW_WIDTH - WALL_WIDTH - 50) bladeMovingRight = false;
		if (bladeMovingRight) x += 2;
		else x -= 2;
		y += (400 * deltaTime );
	}
	else {
		y += (SPEED * deltaTime);
	}

		
}

SDL_Rect obstacle::getRect() const {
	return { x,static_cast<int>(y),width,height };
}

int obstacle::getY() const{
	return static_cast<int>(y);
}

void obstacle::spawnObs(float deltaTime,bool onTheLeft) {
	spawnTime += deltaTime;
	shieldSpawnTime += deltaTime;
	if (spawnTime >= OBSTACLE_SPAWN_TIME && shieldSpawnTime<20) {
		int randType = rand() % 6; // random loai vat can
		
		obstacleType type = static_cast<obstacleType>(randType);

		int spawnX, spawnY,width,height;
		switch (type) {
		case obstacleType::ROPE:
			if (squirrelExists) return;
			spawnX = WALL_WIDTH;
			spawnY = 74;
			width = 388;
			height = 74;
			break;
		case obstacleType::LEFTHOUSE:
			spawnX = WALL_WIDTH;
			spawnY = 43;
			width = 50;
			height = 43;
			break;
		case obstacleType::RIGHTHOUSE:
			spawnX = WINDOW_WIDTH-WALL_WIDTH-50;
			spawnY = 31;
			width = 70;
			height = 31;
			break;
		case obstacleType::SPIKE:
			spawnX = (rand() % 2 == 0) ? WALL_WIDTH : (WINDOW_WIDTH - WALL_WIDTH - 30); // random xuat hien trai hoac phai;
			spawnY = -40; // spawnY am tai vi muon xuat hien bat ngo 
			width = 30;
			height = 81;
			break;
		case obstacleType::BIRD:
			if (birdExists) return;
			spawnX = (rand() % 2 == 0) ? WALL_WIDTH : (WINDOW_WIDTH - WALL_WIDTH - 35); // random xuat hien trai hoac phai
			width = 35;
			height = 33;
			spawnY = 33;
			birdExists = true;
			break;
		case obstacleType::THROWER:
			spawnX = (rand() % 2 == 0) ? WALL_WIDTH-13 : (WINDOW_WIDTH - WALL_WIDTH - 50); // random xuat hien trai hoac phai
			width = 60;
			height = 60;
			spawnY = 60;
			break;
		}
		obstacles.push_back(obstacle(spawnX, -spawnY, width, height, type));
		spawnTime = 0.0;

		// Neu la rope thi them squirrel
		if (type == obstacleType::ROPE && !squirrelExists) {
			squirrels.push_back(obstacle(spawnX + 50, -spawnY, 35, 19, obstacleType::SQUIRREL));
			squirrelExists = true;
		}

		//neu la thrower thi them blade
		if (type == obstacleType::THROWER) {
			blades.push_back(obstacle(spawnX, -spawnY, 30, 30, obstacleType::BLADE));
		}
	}
	else if (shieldSpawnTime >= 20) {
		obstacleType type = obstacleType::SHIELD;
		int spawnX, spawnY, width, height;
		spawnX = (rand() % 2 == 0) ? WALL_WIDTH : (WINDOW_WIDTH - WALL_WIDTH - 50); // random xuat hien trai hoac phai
		width = 50;
		height = 50;
		spawnY = 50;
		obstacles.push_back(obstacle(spawnX, -spawnY, width, height, type));
		spawnTime = 0.0;
		shieldSpawnTime = 0.0;
	}
}

void obstacle::obsRun(float deltaTime,int& score) {
	SPEED = 200 + score*5; //them do kho cho game
	//OBSTACLE_SPAWN_TIME = std::max(0.5, 2.0 - (float)(score / 5));

	//cap nhat vi tri obs ,score
	for (auto it = obstacles.begin(); it != obstacles.end();) { // it != obs.end vì đây ko phải index (index là obs.size())
		it->update(deltaTime);
		it->animate(); // chuyen frame
		if (it->getY() > WINDOW_HEIGHT) {
			if (it->type == obstacleType::ROPE) {
				squirrelExists = false;
				squirrels.clear();
			}
			else if (it->type == obstacleType::BIRD) {
				birdExists = false;
			}
			it = obstacles.erase(it);
			score+=1;
		}
		else {
			it++;
		}
	}

	//cap nhat vi tri squirrel
	for (auto it = squirrels.begin(); it != squirrels.end();) {
		it->update(deltaTime);
		it->animate(); // chuyen frame
		if (it->getY() > WINDOW_HEIGHT) {
			it = squirrels.erase(it);
		}
		else {
			it++;
		}
	}

	//cap nhat vi tri blade
	for (auto it = blades.begin(); it != blades.end();) {
		it->update(deltaTime);
		it->animate(); // chuyen frame
		if (it->getY() > WINDOW_HEIGHT) {
			it = blades.erase(it);
		}
		else {
			it++;
		}
	}
}

std::vector<obstacle>& obstacle::getObstacles() {
	return obstacles;
}

std::vector<obstacle>& obstacle::getSquirrels() {
	return squirrels;
}

std::vector<obstacle>& obstacle::getBlades() {
	return blades;
}

void obstacle::loadTextures(SDL_Renderer* renderer) {
	//vat can ko co animation
	ropeTexture = loadTexture("res/obstacles/rope/rope.png", renderer);
	leftHouseTexture = loadTexture("res/obstacles/houses/b1.png", renderer);
	rightHouseTexture = loadTexture("res/obstacles/houses/b2.png", renderer);
	spikeTexture = loadTexture("res/obstacles/spike/spikes.png", renderer);
	shieldTexture = loadTexture("res/shield/shield.png", renderer);
	throwerTexture = loadTexture("res/obstacles/thrower/thrower.png", renderer);

	//vat can co animation
	squirrelTextures[0] = loadTexture("res/obstacles/squirrels/SQ1.png", renderer);
	squirrelTextures[1] = loadTexture("res/obstacles/squirrels/SQ2.png", renderer);
	squirrelTextures[2] = loadTexture("res/obstacles/squirrels/SQ3.png", renderer);
	squirrelTextures[3] = loadTexture("res/obstacles/squirrels/SQ4.png", renderer);

	birdTextures[0] = loadTexture("res/obstacles/bird/bird1.png", renderer);
	birdTextures[1] = loadTexture("res/obstacles/bird/bird2.png", renderer);
	birdTextures[2] = loadTexture("res/obstacles/bird/bird3.png", renderer);

	bladeTextures[0] = loadTexture("res/obstacles/blade/1.png", renderer);
	bladeTextures[1] = loadTexture("res/obstacles/blade/2.png", renderer);
	bladeTextures[2] = loadTexture("res/obstacles/blade/3.png", renderer);
	bladeTextures[3] = loadTexture("res/obstacles/blade/4.png", renderer);
}

void obstacle::freeTextures() {
	SDL_DestroyTexture(ropeTexture);
	SDL_DestroyTexture(leftHouseTexture);
	SDL_DestroyTexture(rightHouseTexture);
	SDL_DestroyTexture(spikeTexture);
	SDL_DestroyTexture(shieldTexture);
	SDL_DestroyTexture(throwerTexture);

	for (int i = 0; i < 4; i++) {
		SDL_DestroyTexture(squirrelTextures[i]);
		SDL_DestroyTexture(bladeTextures[i]);
	}
	for (int i = 0; i < 3; i++) {
		SDL_DestroyTexture(birdTextures[i]);
	}
}

void obstacle::render(SDL_Renderer* renderer) {
	SDL_Rect dstRect = { x, y, width, height };
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	switch (type) {
	case obstacleType::ROPE:
		SDL_RenderCopy(renderer, ropeTexture, NULL, &dstRect);
		break;
	case obstacleType::LEFTHOUSE:
		SDL_RenderCopy(renderer, leftHouseTexture, NULL, &dstRect);
		break;
	case obstacleType::RIGHTHOUSE:
		SDL_RenderCopy(renderer, rightHouseTexture, NULL, &dstRect);
		break;
	case obstacleType::SPIKE:
		if (x == WALL_WIDTH) flip = SDL_FLIP_NONE;
		else flip = SDL_FLIP_HORIZONTAL;
		SDL_RenderCopyEx(renderer, spikeTexture, NULL, &dstRect, 0, NULL, flip);
		break;
	case obstacleType::BIRD:
		flip = birdMovingRight ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		SDL_RenderCopyEx(renderer, currentTexture, NULL, &dstRect, 0, NULL, flip);
		break;
	case obstacleType::SQUIRREL:
		flip = movingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
		SDL_RenderCopyEx(renderer, currentTexture, NULL, &dstRect, 0, NULL, flip);
		break;
	case obstacleType::SHIELD:
		SDL_RenderCopy(renderer, shieldTexture, NULL, &dstRect);
		break;
	case obstacleType::THROWER:
		if (x == WALL_WIDTH - 13) flip = SDL_FLIP_NONE;
		else flip = SDL_FLIP_HORIZONTAL;
		SDL_RenderCopyEx(renderer, throwerTexture, NULL, &dstRect, 0, NULL, flip);
		break;
	case obstacleType::BLADE:
		SDL_RenderCopy(renderer, currentTexture, NULL, &dstRect);
		break;
	}

}

void obstacle::animate() {
	static int count = 0;
	count++;

	if (count > animationSpeed) {
		if (type == obstacleType::SQUIRREL) {
			frameIndex = (frameIndex + 1) % 4;  // 4 frames cho squirrel
		}
		else if (type == obstacleType::BIRD) {
			frameIndex = (frameIndex + 1) % 3;  // 3 frames cho bird
		}
		else if (type == obstacleType::BLADE) {
			frameIndex = (frameIndex + 1) % 4; // 4 frames cho blade
		}
		count = 0;
	}

	if (type == obstacleType::SQUIRREL) {
		currentTexture = squirrelTextures[frameIndex];
	}
	else if (type == obstacleType::BIRD) {
		currentTexture = birdTextures[frameIndex];
	}
	else if (type == obstacleType::BLADE) {
		currentTexture = bladeTextures[frameIndex];
	}
}

void obstacle::checkShield(bool& shieldActive, Uint32 currentTime,Uint32 shieldStartTime) {
	if (shieldActive && currentTime - shieldStartTime >= 8000) {
		shieldActive = false;
	}
}