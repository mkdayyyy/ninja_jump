#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include "commonFunc.h"

enum obstacleType { ROPE, LEFTHOUSE, RIGHTHOUSE, SPIKE, BIRD, SQUIRREL}; // loai vat can

class obstacle {
public:
	obstacle(int x, int y, int w, int h, obstacleType type); // khoi tao
	void update(float deltaTime);//cap nhat vi tri vat can
	SDL_Rect getRect() const; // ve vat can
	int getY() const; // lay vi tri y cua vat can
	void render(SDL_Renderer* renderer); // in obs
	obstacleType getType() const { return type; } // lay loai vat can

	//quan li vat can (dùng stactic vì mấy hàm này ko liên qua đến class obs mà là quản lí các obs )
	static void spawnObs(float deltaTime, bool onTheLeft); // tao vat can
	static void obsRun(float deltaTime, int& score); // cap nhat vi tri vat can
	static void loadTextures(SDL_Renderer* renderer); // lay hinh anh obs
	static void freeTextures(); // giai phong hinh anh obs
	static std::vector<obstacle>& getObstacles(); // lay danh sach vat can
	static std::vector<obstacle>& getSquirrels(); // lay danh sach squirrel

	static float SPEED; //speed cua vat can (pixel/s)
	static const int OBSTACLE_SIZE; // size cua vat can

	void animate(); // chuyen frame

private:
	int x;
	float y;
	int width, height; // chieu rong va chieu cao cua vat can
	static float spawnTime; // thoi gian spawn vat can
	obstacleType type; // loai vat can

	bool movingRight = true; // kiem tra huong cua squirrel 

	float freezeTime = 0.0; // kiem tra bird dung yen dc bao lau
	bool movingDown = false; // kiem tra huong cua bird

	static std::vector<obstacle> obstacles; // danh sach vat can
	static std::vector<obstacle> squirrels; // danh sach squirrel
	static bool birdExists; // theo doi bird in ra hay chua
	static bool squirrelExists; // theo doi squirrel in ra hay chua
	


	static SDL_Texture* ropeTexture; // hinh anh vat can rope
	static SDL_Texture* leftHouseTexture; // hinh anh vat can left house
	static SDL_Texture* rightHouseTexture; // hinh anh vat can right house
	static SDL_Texture* spikeTexture; // hinh anh vat can spike

	int frameIndex = 0; // chi so frame hien tai
	int animationSpeed = 6;  // toc do animation
	SDL_Texture* currentTexture = nullptr;
	static SDL_Texture* squirrelTextures[4];  // danh sach frame squirrel
	static SDL_Texture* birdTextures[3];  // danh sach frame bird
};

#endif