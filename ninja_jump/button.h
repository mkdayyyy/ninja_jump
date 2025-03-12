#pragma once
#include "commonFunc.h"

struct button {
	SDL_Rect rectBut;

	bool isClick(int mousex, int mousey);
};

extern button playBut;
extern button quitBut;

GameState handleMenuClick(int mousex, int mousey, bool& running);