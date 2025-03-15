#pragma once
#include "commonFunc.h"

struct button { // dung struct vi button la 1 cau truc don gian
	SDL_Rect rectBut; // vi tri cua button

	bool isClick(int mousex, int mousey); //kiem tra xem co click vao button ko
};

extern button playBut; // khai bao nut play
extern button quitBut; // khai bao nut quit

GameState handleMenuClick(int mousex, int mousey, bool& running); // xu ly click chuot