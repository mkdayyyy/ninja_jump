#pragma once
#include "commonFunc.h"

class button { 
public:
	button(int x, int y, int w, int h, const std::string& texturePath, SDL_Renderer* renderer); // ham khoi tao
	void render(SDL_Renderer* renderer); // render hinh anh button
	bool isClicked(int mouseX, int mouseY); // kiem tra chuot co an vao button hay ko
private:
	SDL_Rect rect; // khung button
	SDL_Texture* texture;
};