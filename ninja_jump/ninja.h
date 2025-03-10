#ifndef NINJA_H
#define NINJA_H
#include "commonFunc.h"

class ninja {
public:
	ninja(int x, int y); // khoi tao 
	void update(float deltaTime, bool& jumping); //cap nhat vi tri ninja
	SDL_Rect getRect() const; // lay rect cua ninja
	void handleInput(SDL_Event& e, bool& jumping); // quan li dau vao
	bool getOnTheLeft() const; // lay bool onTheLeft de su dung

private:
	int x, y;
	bool onTheLeft;
	bool isIntro;
	float introProgress;
	float jumpProgress;

	void updateIntro(float deltaTime); //chay intro
	void updateJump(float deltaTime, bool& jumping); // ninja nhay
};

#endif
