#include "obstacle.h"

const int obstacle::OBSTACLE_SIZE = 40;
const float obstacle::SPEED = 200.0;
std::vector<obstacle> obstacle::obstacles;
float obstacle::spawnTime = 0.0;

obstacle::obstacle(int x, int y) : x(x), y(static_cast<float>(y)) {
	//khoi tao toa do
}

void obstacle::update(float deltaTime) {
	y += (SPEED * deltaTime);
}

SDL_Rect obstacle::getRect() const {
	return { x,static_cast<int>(y),OBSTACLE_SIZE,OBSTACLE_SIZE };
}

int obstacle::getY() const{
	return static_cast<int>(y);
}

void obstacle::spawnObs(float deltaTime) {
	spawnTime += deltaTime;
	if (spawnTime >= OBSTACLE_SPAWN_TIME) {
		int randomX = WALL_WIDTH + std::rand() % (WINDOW_WIDTH - 2 * WALL_WIDTH - obstacle::OBSTACLE_SIZE);
		obstacles.push_back(obstacle(randomX, -obstacle::OBSTACLE_SIZE));
		spawnTime = 0.0;
	}
}

void obstacle::obsRun(float deltaTime) {
	for (auto it = obstacles.begin(); it != obstacles.end();) {
		it->update(deltaTime);
		if (it->getY() > WINDOW_HEIGHT) {
			it = obstacles.erase(it);
		}
		else {
			it++;
		}
	}
}

const std::vector<obstacle>& obstacle::getObstacles() {
	return obstacles;
}