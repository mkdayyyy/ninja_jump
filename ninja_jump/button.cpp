#include "button.h"

button playBut = { WINDOW_WIDTH / 2 - 50, 250, 100, 50 };
button quitBut = { WINDOW_WIDTH / 2 - 50, 320, 100, 50 };

bool button::isClick(int mousex, int mousey) {
	return (mousex >= rectBut.x && mousex <= rectBut.x + rectBut.w &&
		    mousey >= rectBut.y && mousey <= rectBut.y + rectBut.h);
}

GameState handleMenuClick(int mousex, int mousey, bool& running) {
	
	if (playBut.isClick(mousex, mousey)) {
		return PLAYING;
	}
	if (quitBut.isClick(mousex, mousey)) {
		SDL_Quit();
		exit(0);
		return MENU;
	}
	return MENU;
}