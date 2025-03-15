#pragma once
#include "commonFunc.h"

struct button { // dung struct vi button la 1 cau truc don gian
	SDL_Rect rectBut;

	bool isClick(int mousex, int mousey);
};

extern button playBut; // khai bao nut play
extern button quitBut; // khai bao nut quit

GameState handleMenuClick(int mousex, int mousey, bool& running);