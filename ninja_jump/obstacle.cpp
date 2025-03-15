#include "obstacle.h"

const int obstacle::OBSTACLE_SIZE = 40;
float obstacle::SPEED = 200.0;
std::vector<obstacle> obstacle::obstacles;
float obstacle::spawnTime = 0.0;

SDL_Texture* obstacle::ropeTexture = nullptr;
SDL_Texture* obstacle::leftHouseTexture = nullptr;
SDL_Texture* obstacle::rightHouseTexture = nullptr;
SDL_Texture* obstacle::spikeTexture = nullptr;

obstacle::obstacle(int x, int y,int w,int h, obstacleType type) : x(x), y(static_cast<float>(y)),width(w),height(h), type(type) {
	//khoi tao toa do
}

void obstacle::update(float deltaTime) {
	y += (SPEED * deltaTime);
	/*if (y > 600) {
		obstacles.erase(obstacles.begin());
	}*/
}

SDL_Rect obstacle::getRect() const {
	return { x,static_cast<int>(y),OBSTACLE_SIZE,OBSTACLE_SIZE };
}

int obstacle::getY() const{
	return static_cast<int>(y);
}

void obstacle::spawnObs(float deltaTime,bool onTheLeft) {
	spawnTime += deltaTime;
	if (spawnTime >= OBSTACLE_SPAWN_TIME) {
		int randType = rand() % 4;
		obstacleType type = static_cast<obstacleType>(randType);

		int spawnX, spawnY,width,height;
		switch (type) {
		case obstacleType::ROPE:
			spawnX = 100;
			spawnY = 74;
			width = 300;
			height = 74;
			break;
		case obstacleType::LEFTHOUSE:
			spawnX = 100;
			spawnY = 43;
			width = 50;
			height = 43;
			break;
		case obstacleType::RIGHTHOUSE:
			spawnX = WINDOW_WIDTH-WALL_WIDTH-70;
			spawnY = 31;
			width = 70;
			height = 31;
			break;
		case obstacleType::SPIKE:
			spawnX = 100;
			spawnY = -81;
			width = 30;
			height = 81;
			break;
		}



		obstacles.push_back(obstacle(spawnX, -spawnY, width, height, type));
		spawnTime = 0.0;
	}
}

void obstacle::obsRun(float deltaTime,int& score) {
	SPEED = 200 + score*5; //them do kho cho game
	//OBSTACLE_SPAWN_TIME = std::max(0.5, 2.0 - (float)(score / 5));

	//cap nhat vi tri obs ,score
	for (auto it = obstacles.begin(); it != obstacles.end();) { // it != obs.end vì đây ko phải index (index là obs.size())
		it->update(deltaTime);
		if (it->getY() > WINDOW_HEIGHT) {
			it = obstacles.erase(it);
			score+=1;
		}
		else {
			it++;
		}
	}
}

std::vector<obstacle>& obstacle::getObstacles() {
	return obstacles;
}

void obstacle::loadTextures(SDL_Renderer* renderer) {
	ropeTexture = loadTexture("res/obstacles/rope/rope.png", renderer);
	leftHouseTexture = loadTexture("res/obstacles/houses/b1.png", renderer);
	rightHouseTexture = loadTexture("res/obstacles/houses/b2.png", renderer);
	spikeTexture = loadTexture("res/obstacles/spike/spikes.png", renderer);
}

void obstacle::freeTextures() {
	SDL_DestroyTexture(ropeTexture);
	SDL_DestroyTexture(leftHouseTexture);
	SDL_DestroyTexture(rightHouseTexture);
	SDL_DestroyTexture(spikeTexture);
}

void obstacle::render(SDL_Renderer* renderer) {
	SDL_Rect dstRect = { x, y, width, height };

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
		SDL_RenderCopy(renderer, spikeTexture, NULL, &dstRect);
		break;
	}
}