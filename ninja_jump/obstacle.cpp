#include "obstacle.h"

const int obstacle::SIZE = 40;
const float obstacle::SPEED = 200.0;

obstacle::obstacle(int x, int y) : x(x), y(y) {
	//khoi tao toa do
}

void obstacle::update(float deltaTime) {
	y += static_cast<int>(SPEED * deltaTime);
}

SDL_Rect obstacle::rect() const {
	return { x,y,SIZE,SIZE };
}

int obstacle::getY() const{
	return y;
}
