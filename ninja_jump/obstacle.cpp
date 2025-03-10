#include "obstacle.h"

const int obstacle::OBSTACLE_SIZE = 40;
float obstacle::SPEED = 200.0;
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

void obstacle::spawnObs(float deltaTime,bool onTheLeft) {
	spawnTime += deltaTime;
	if (spawnTime >= OBSTACLE_SPAWN_TIME) {
		int randomX = onTheLeft ? WALL_WIDTH : WINDOW_WIDTH - WALL_WIDTH - obstacle::OBSTACLE_SIZE;
		obstacles.push_back(obstacle(randomX, -obstacle::OBSTACLE_SIZE));
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