#pragma once
#include "commonFunc.h"

class button {
public:
	button(); // Ham khoi tao ban dau
	button(int x, int y, int w, int h, const std::string& texturePath, SDL_Renderer* renderer); // Ham khoi tao day du
	void render(SDL_Renderer* renderer); // render button
	bool isClicked(int mouseX, int mouseY); // check clicked

private:
	SDL_Rect rect; // khung button
	SDL_Texture* texture = nullptr; // texture button
};
