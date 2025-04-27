#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include "button.h"

// Khai báo tất cả các button
extern button playButton;
extern button exitButton;
extern button optionButton;
extern button tryAgainButton;
extern button menuButton;
extern button pauseButton;
extern button musicButton;
extern button soundButton;
extern button quitButton;
extern button continueButton;
extern button restartButton;

// Hàm khởi tạo các button
void initButtons(SDL_Renderer* renderer);

#endif // BUTTON_MANAGER_H
