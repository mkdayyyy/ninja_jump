#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include "commonFunc.h"

enum obstacleType {ROPE,LEFTHOUSE,RIGHTHOUSE,SPIKE};

class obstacle {
public:
	obstacle(int x, int y, int w, int h, obstacleType type); // khoi tao
	void update(float deltaTime);//cap nhat vi tri vat can
	SDL_Rect getRect() const; // ve vat can
	int getY() const; // lay vi tri y cua vat can
	void render(SDL_Renderer* renderer); // in obs
	obstacleType getType() const { return type; } // lay loai vat can

	//quan li vat can (dùng stactic vì mấy hàm này ko liên qua đến class obs mà là quản lí các obs )
	static void spawnObs(float deltaTime,bool onTheLeft);
	static void obsRun(float deltaTime,int& score);
	static void loadTextures(SDL_Renderer* renderer); // lay hinh anh obs
	static void freeTextures(); // giai phong hinh anh obs
	//lay danh sach vat can
	static std::vector<obstacle>& getObstacles();

	static float SPEED; //speed cua vat can (pixel/s)
	static const int OBSTACLE_SIZE; // size cua vat can

private:
	int x;
	float y;
	int width, height;
	static float spawnTime;
	obstacleType type;
	static std::vector<obstacle> obstacles; // danh sach vat can

	static SDL_Texture* ropeTexture;
	static SDL_Texture* leftHouseTexture;
	static SDL_Texture* rightHouseTexture;
	static SDL_Texture* spikeTexture;
};

#endif