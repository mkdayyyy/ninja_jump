#include "buttonManager.h"

// Định nghĩa thực tế các button
button playButton;
button exitButton;
button optionButton;
button tryAgainButton;
button menuButton;
button pauseButton;
button musicButton;
button soundButton;
button quitButton;
button continueButton;
button restartButton;

// Setup ảnh cho từng button
void initButtons(SDL_Renderer* renderer) {
    playButton = button(WINDOW_WIDTH / 2 - 50, 250, 100, 50, "res/button/but_play.png", renderer);
    exitButton = button(WINDOW_WIDTH / 2 - 50, 320, 100, 50, "res/button/but_exit.png", renderer);
    optionButton = button(10, 10, 40, 40, "res/menu/options.png", renderer);
    tryAgainButton = button(175, 270, 130, 50, "res/button/but_try.png", renderer);
    menuButton = button(175, 340, 130, 50, "res/button/but_menu.png", renderer);
    pauseButton = button(440, 10, 30, 30, "res/menu/pause_btn.png", renderer);
    musicButton = button(150, 230, 80, 80, "res/menu/music_btn.png", renderer);
    soundButton = button(250, 230, 80, 80, "res/menu/sound_btn.png", renderer);
    quitButton = button(WINDOW_WIDTH / 2 - 50, 500, 100, 50, "res/menu/QUITBTN.png", renderer);
    continueButton = button(175, 220, 130, 50, "res/button/but_con.png", renderer);
    restartButton = button(175, 280, 130, 50, "res/button/but_res.png", renderer);
}
