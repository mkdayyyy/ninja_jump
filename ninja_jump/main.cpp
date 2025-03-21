#include "commonFunc.h"
#include "ninja.h"
#include "obstacle.h"
#include "button.h"
#include "LTexture.h"

void loadAllTextures(SDL_Renderer* renderer);

int main(int argc, char* argv[]) {
    initSDL();
    SDL_Window* window = createWindow();

    SDL_Renderer* renderer=createRenderer(window);
    loadAllTextures(renderer);
    button playButton(WINDOW_WIDTH / 2 - 50, 250, 100, 50, "res/button/but_play.png", renderer);
    button exitButton(WINDOW_WIDTH / 2 - 50, 320, 100, 50, "res/button/but_exit.png", renderer);
    button tryAgainButton(175, 270, 130, 50, "res/button/but_try.png", renderer);
    button menuButton(175, 340, 130, 50, "res/button/but_menu.png", renderer);
    button pauseButton(440, 10, 30, 30, "res/menu/pause_btn.png", renderer);
    button optionButton(10, 10, 40, 40, "res/menu/options.png", renderer);
    button musicButton(150, 230, 80, 80, "res/menu/music_btn.png", renderer);
    button soundButton(250, 230, 80, 80, "res/menu/sound_btn.png", renderer);
    button quitButton(WINDOW_WIDTH / 2 - 50, 500, 100, 50, "res/menu/QUITBTN.png", renderer);
    button continueButton(175, 220, 130, 50, "res/button/but_con.png", renderer);
    button restartButton(175, 280, 130, 50, "res/button/but_res.png", renderer);

    //quan li game
    bool running = true;
    bool playMusic = true;
    bool playSound = true;
    bool jumping = false;
    int score = 0;
	Mix_Volume(-1, MIX_MAX_VOLUME / 3); // am thanh hieu ung
	Mix_VolumeMusic(MIX_MAX_VOLUME / 10); // am thanh nen
	Mix_PlayMusic(backgroundMusic, -1); // choi nhac nen

    //quan li trang thai game
    GameState state = MENU;

    ninja ninja(WALL_WIDTH, WINDOW_HEIGHT - NINJA_SIZE);// khoi tao ninja 
	std::srand(static_cast<unsigned>(std::time(nullptr))); // khoi tao random
    
    Uint32 lastTime = SDL_GetTicks(); // lay thoi gian trc khi chay

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0; // doi sang giay
        lastTime = currentTime;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { running = false; }

            if (state == MENU) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    if (playButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        state = PLAYING;
                    }
                    else if (exitButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        running = false;
                    }
                    else if (optionButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        state = OPTION;
                    }
                }
            }
            else if(state==PLAYING) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    if (pauseButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        state = PAUSE;
                    }
                }
                ninja.handleInput(e, jumping);
            }
            else if (state == GAME_OVER) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    if (tryAgainButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        score = 0;
                        obstacle::SPEED = 200.0;
                        state = PLAYING;
                        ninja = { WALL_WIDTH, WINDOW_HEIGHT - NINJA_SIZE };
                        obstacle::getObstacles().clear();
                        obstacle::getSquirrels().clear();
                        obstacle::birdExists = false;
                        obstacle::squirrelExists = false;
                        jumping = false;
                        lastTime = SDL_GetTicks(); 
                        SDL_Delay(100); 
                        Mix_PlayChannel(-1, gameOverSound, 0);
                    }
                    else if (menuButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        state = MENU;
                    }
                }
            }
            else if (state == OPTION) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    if (musicButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        if(playMusic) {
                            Mix_HaltMusic();
                            playMusic = !playMusic;
                        }
                        else {
                            Mix_PlayMusic(backgroundMusic, -1);
                            playMusic = !playMusic;
                        }                    
                    }
                    if (soundButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        if (playSound) {
                            Mix_Volume(-1, 0);
                            playSound = !playSound;
                        }
                        else {
                            Mix_Volume(-1, MIX_MAX_VOLUME / 3);
                            playSound = !playSound;
                        }
                    }
                    if (quitButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        state = MENU;
                    }
                }
            }
            else if (state == PAUSE) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    if (menuButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        state = MENU;
                    }
                    if (restartButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        score = 0;
                        obstacle::SPEED = 200.0;
                        state = PLAYING;
                        ninja = { WALL_WIDTH, WINDOW_HEIGHT - NINJA_SIZE };
                        obstacle::getObstacles().clear();
                        obstacle::getSquirrels().clear();
                        obstacle::birdExists = false;
                        obstacle::squirrelExists = false;
                        jumping = false;
                        lastTime = SDL_GetTicks(); 
                        SDL_Delay(100); 
                        state = PLAYING;
                    }
                    if (continueButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, gameOverSound, 0);
                        state = PLAYING;
                    }
                }
            }
        }
        if (state == MENU) {
           //reset lai game 
            score = 0;
            obstacle::SPEED = 200.0;
            ninja = { WALL_WIDTH, WINDOW_HEIGHT - NINJA_SIZE };
            obstacle::getObstacles().clear();
            obstacle::getSquirrels().clear();
            obstacle::birdExists = false;
            obstacle::squirrelExists = false;
            jumping = false;
            lastTime = SDL_GetTicks();
            SDL_Delay(100);

            //in background menu
            SDL_Rect dstRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
            SDL_RenderCopy(renderer, menuTexture, NULL, &dstRect);

            //ve nut 
            playButton.render(renderer);
            exitButton.render(renderer);
            optionButton.render(renderer);

            SDL_RenderPresent(renderer);
        }
        else if(state==PLAYING) {
            //khoi chay intro va jumping
            ninja.update(deltaTime, jumping);
            ninja.animate(jumping);

            //tao vat can
            obstacle::spawnObs(deltaTime, ninja.getOnTheLeft());
            obstacle::obsRun(deltaTime, score);

            bool checkVacham = false;
            //kiem tra va cham giua ninja va obs
            SDL_Rect ninjaRect = ninja.getRect();
            for (auto it = obstacle::getObstacles().begin(); it != obstacle::getObstacles().end();) { // &obs de chinh sua vao obs cua obstacles chu ko phai tao 1 ban sao
                SDL_Rect obsRect = it->getRect();
                if (SDL_HasIntersection(&ninjaRect, &obsRect)) {
                    if (it->getType() == obstacleType::ROPE) {
                        it++;
                        continue;
                    }
                    if (it->getType() == obstacleType::BIRD) {
                        if (jumping) {
                            Mix_PlayChannel(-1, hitSound, 0);
                            it = obstacle::getObstacles().erase(it);
                            obstacle::birdExists = false;
                            continue;
                        }
                    }
                    checkVacham = true;
                    break;
                }
                else {
                    it++;
                }
            }

			//kiem tra va cham giua ninja va squirrel
            for (auto it = obstacle::getSquirrels().begin(); it != obstacle::getSquirrels().end(); ) {
                SDL_Rect squirrelRect = it->getRect();
                if (SDL_HasIntersection(&ninjaRect, &squirrelRect)) {
                    if (jumping) {
                        Mix_PlayChannel(-1, hitSound, 0);
                        it = obstacle::getSquirrels().erase(it); // xoa squirrel khoi danh sach
                        obstacle::squirrelExists = false;
                        continue;
                    }
                    checkVacham = true;
                    break;
                }
                else {
                    ++it;
                }
            }
            if (checkVacham) {
                state = GAME_OVER;
                Mix_PlayChannel(-1, fallSound, 0);
            }

            // ve ingame back
            renderIngameText(renderer, ingameTexture,deltaTime);

            //ve ninja
            ninja.render(renderer, jumping);

            //ve obstacle
            for (auto& obs : obstacle::getObstacles()) {
                obs.render(renderer);
            }
			//ve squirrel
            for (auto& squirrel : obstacle::getSquirrels()) {
				squirrel.render(renderer);
            }
            //in bang diem
            std::string scoreText = "Score: " + std::to_string(score);
            SDL_Rect scoreBar = { 145,15,200,50 };
            SDL_RenderCopy(renderer, scorebar, NULL, &scoreBar);
            renderText(renderer, scoreText, 180, 20,true);

            //pause
            pauseButton.render(renderer);

            SDL_RenderPresent(renderer);
        }

        else if (state == GAME_OVER) {
    
            //hien thi man hinh gameover
            SDL_Rect gameOverBackRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
            SDL_RenderCopy(renderer, gameOverBack, NULL, &gameOverBackRect);

            SDL_Rect gameOverRect = { 65,100,350,350 };
            SDL_RenderCopy(renderer, gameOverPanel, NULL, &gameOverRect);

            tryAgainButton.render(renderer);
            menuButton.render(renderer);
            std::string scoreText = "Score: " + std::to_string(score);
            renderText(renderer, scoreText, 150, 130,true);

            SDL_RenderPresent(renderer);
        }
        else if (state == OPTION) {
            //in background
            SDL_Rect backRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
            SDL_RenderCopy(renderer, menuTexture, NULL, &backRect);

            //in hinh anh khung
            SDL_Rect optionRect = { 90,150,300,300 };
            SDL_RenderCopy(renderer, pauseMenu, NULL, &optionRect);


            //in hinh anh cac button
            soundButton.render(renderer);
            musicButton.render(renderer);
            quitButton.render(renderer);

            // in hinh anh dau gach do
            SDL_Rect offMusicRect,offSoundRect;
            if (!playMusic) {
                offMusicRect = { 150,230,80,80 };
                SDL_RenderCopy(renderer, offSlash, NULL, &offMusicRect);
            }
            if (!playSound) {
                offSoundRect = { 250, 230, 80, 80 };
                SDL_RenderCopy(renderer, offSlash, NULL, &offSoundRect);
            }

            SDL_RenderPresent(renderer);
        }
        else if (state == PAUSE) {

            //in menupause
            SDL_Rect pauseRect = { 90,150,300,300 };
            SDL_RenderCopy(renderer, pauseMenu, NULL, &pauseRect);

            //in cac button
            continueButton.render(renderer);
            menuButton.render(renderer);
            restartButton.render(renderer);

            SDL_RenderPresent(renderer);
        }
        
        limitFPS(currentTime);
    }

    obstacle::freeTextures();
    destroySDL();
    return 0;
}

void loadAllTextures(SDL_Renderer* renderer) {
    obstacle::loadTextures(renderer); // tai hinh anh obs
    ninja::loadTextures(renderer); // tai hinh anh ninja
    loadCommonTexture(renderer); // tai hinh anh nen
}