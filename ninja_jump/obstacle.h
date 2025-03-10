#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include "commonFunc.h"



class obstacle {
public:
	obstacle(int x, int y); // khoi tao
	void update(float deltaTime);//cap nhat vi tri vat can
	SDL_Rect getRect() const; // ve vat can
	int getY() const; // lay vi tri y cua vat can

	//quan li vat can (dùng stactic vì mấy hàm này ko liên qua đến class obs mà là quản lí các obs )
	static void spawnObs(float deltaTime,bool onTheLeft);
	static void obsRun(float deltaTime,int& score);

	//lay danh sach vat can
	static std::vector<obstacle>& getObstacles();

	static float SPEED; //speed cua vat can (pixel/s)
	static const int OBSTACLE_SIZE; // size cua vat can

private:
	int x;
	float y;
	static float spawnTime;
	static std::vector<obstacle> obstacles; // danh sach vat can
};

#endif