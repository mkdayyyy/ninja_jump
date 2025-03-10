#ifndef NINJA_H
#define NINJA_H
#include "commonFunc.h"

class ninja {
public:
	ninja(int x, int y);
	void update(float deltaTime, bool& jumping);
	SDL_Rect getRect() const;
	void handleInput(SDL_Event& e, bool& jumping);
	bool getOnTheLeft() const;
private:
	int x, y;
	bool onTheLeft;
	bool isIntro;
	float introProgress;
	float jumpProgress;

	void updateIntro(float deltaTime);
	void updateJump(float deltaTime, bool& jumping);
};

#endif
