#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
class obstacle {
public:
	obstacle(int x, int y); // khoi tao
	void update(float deltaTime);//cap nhat vi tri vat can
	SDL_Rect rect() const; // ve vat can
	int getY() const; // lay vi tri y cua vat can

	static const float SPEED; //speed cua vat can (pixel/s)
	static const int SIZE; // size cua vat can
private:
	int x, y;
};

#endif