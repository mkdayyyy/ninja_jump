#include "obstacle.h"

const int obstacle::OBSTACLE_SIZE = 40;
float obstacle::SPEED = 200.0;
std::vector<obstacle> obstacle::obstacles;
std::vector<obstacle> obstacle::squirrels;
float obstacle::spawnTime = 0.0;

SDL_Texture* obstacle::ropeTexture = nullptr;
SDL_Texture* obstacle::leftHouseTexture = nullptr;
SDL_Texture* obstacle::rightHouseTexture = nullptr;
SDL_Texture* obstacle::spikeTexture = nullptr;
SDL_Texture* obstacle::squirrelTextures[4] = { nullptr, nullptr, nullptr, nullptr };
SDL_Texture* obstacle::birdTextures[3] = { nullptr, nullptr, nullptr };

obstacle::obstacle(int x, int y,int w,int h, obstacleType type) : x(x), y(static_cast<float>(y)),width(w),height(h), type(type) {
	// ham khoi tao
	if (type == obstacleType::SQUIRREL) {
		currentTexture = squirrelTextures[0];
	}
	else if (type == obstacleType::BIRD) {
		currentTexture = birdTextures[0];
	}
}

void obstacle::update(float deltaTime) {
	if (type == obstacleType::SQUIRREL) {
		x += (x < WINDOW_WIDTH / 2) ? 2 : -2; // squirrel di chuyen ngang
	}
	y += (SPEED * deltaTime);
	
}

SDL_Rect obstacle::getRect() const {
	return { x,static_cast<int>(y),width,height };
}

int obstacle::getY() const{
	return static_cast<int>(y);
}

void obstacle::spawnObs(float deltaTime,bool onTheLeft) {
	spawnTime += deltaTime;
	if (spawnTime >= OBSTACLE_SPAWN_TIME) {
		int randType = rand() % 5; // random loai vat can
		//int randType = 6;
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
		//case obstacleType::SQUIRREL:
		//	spawnX = (rand() % 2 == 0) ? 100 : (WINDOW_WIDTH - WALL_WIDTH - 35); // random xuat hien trai hoac phai
		//	width = 35;
		//	height = 19;
		//	spawnY = -height;
		//	break;
		case obstacleType::BIRD:
			spawnX = (rand() % 2 == 0) ? 100 : (WINDOW_WIDTH - WALL_WIDTH - 35); // random xuat hien trai hoac phai
			
			width = 35;
			height = 33;
			spawnY = -height;
			break;
		}

		obstacles.push_back(obstacle(spawnX, -spawnY, width, height, type));
		spawnTime = 0.0;

		// Neu la rope thi them squirrel
		if (type == obstacleType::ROPE) {
			squirrels.push_back(obstacle(spawnX + 50, -spawnY, 35, 19, obstacleType::SQUIRREL));
		}
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
				squirrels.clear();
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
}

std::vector<obstacle>& obstacle::getObstacles() {
	return obstacles;
}

std::vector<obstacle>& obstacle::getSquirrels() {
	return squirrels;
}

void obstacle::loadTextures(SDL_Renderer* renderer) {
	//vat can ko co animation
	ropeTexture = loadTexture("res/obstacles/rope/rope.png", renderer);
	leftHouseTexture = loadTexture("res/obstacles/houses/b1.png", renderer);
	rightHouseTexture = loadTexture("res/obstacles/houses/b2.png", renderer);
	spikeTexture = loadTexture("res/obstacles/spike/spikes.png", renderer);

	//vat can co animation
	squirrelTextures[0] = loadTexture("res/obstacles/squirrels/SQ1.png", renderer);
	squirrelTextures[1] = loadTexture("res/obstacles/squirrels/SQ2.png", renderer);
	squirrelTextures[2] = loadTexture("res/obstacles/squirrels/SQ3.png", renderer);
	squirrelTextures[3] = loadTexture("res/obstacles/squirrels/SQ4.png", renderer);

	birdTextures[0] = loadTexture("res/obstacles/bird/bird1.png", renderer);
	birdTextures[1] = loadTexture("res/obstacles/bird/bird2.png", renderer);
	birdTextures[2] = loadTexture("res/obstacles/bird/bird3.png", renderer);
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
	case obstacleType::BIRD:
		SDL_RenderCopy(renderer, currentTexture, NULL, &dstRect);
		break;
	case obstacleType::SQUIRREL:
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
		count = 0;
	}

	if (type == obstacleType::SQUIRREL) {
		currentTexture = squirrelTextures[frameIndex];
	}
	else if (type == obstacleType::BIRD) {
		currentTexture = birdTextures[frameIndex];
	}
}