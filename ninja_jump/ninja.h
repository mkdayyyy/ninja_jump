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
	void render(SDL_Renderer* renderer, bool jumping); // in animation ninja
	
	static void loadTextures(SDL_Renderer* renderer); // lay hinh anh ninja
	void animate(bool jumping); //chuyen frame

private:
	int x, y; // toa do cua ninja
	//int width, height; // chieu rong va chieu dai cua ninja
	bool onTheLeft; 
	bool isIntro; 
	float introProgress;
	float jumpProgress;

	int frameIndex = 0;
	int animationSpeed = 10;
	void updateIntro(float deltaTime); //chay intro
	void updateJump(float deltaTime, bool& jumping); // ninja nhay
	static SDL_Texture* ninjaRunTextures[3]; // danh sach frame ninja khi chay
	static SDL_Texture* ninjaJumpTextures[4]; // danh sach frame ninja khi nhay
};

#endif
