#include "commonFunc.h"
#include "ninja.h"
#include "obstacle.h"
#include "button.h"
#include "LTexture.h"
#include "menu.h"
#include "buttonManager.h"
#include "checkCollision.h"

void loadAllTextures(SDL_Renderer* renderer);
void resetGame(int& score, ninja& ninja, bool& jumping, Uint32& lastTime);

int main(int argc, char* argv[]) {
    //khoi tao
    initSDL();
    SDL_Window* window = createWindow();
    SDL_Renderer* renderer=createRenderer(window);
    loadAllTextures(renderer);
    initButtons(renderer);
    loadHighScore();
    ninja ninja(WALL_WIDTH, WINDOW_HEIGHT - NINJA_SIZE);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    //quan li game
    bool running = true;
    bool playMusic = true;
    bool playSound = true;
    bool jumping = false;
    bool shieldActive = false;
    Uint32 shieldStartTime = 0;
    int score = 0;
    GameState state = MENU;

	Mix_Volume(-1, MIX_MAX_VOLUME / 3); // am thanh hieu ung
	Mix_VolumeMusic(MIX_MAX_VOLUME / 10); // am thanh nen
	Mix_PlayMusic(backgroundMusic, -1); // choi nhac nen

    Uint32 lastTime = SDL_GetTicks(); // lay thoi gian trc khi chay

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0; // doi sang giay
        lastTime = currentTime;

        //kiem tra thoi gian khien hoat dong
        obstacle::checkShield(shieldActive, currentTime,shieldStartTime);

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }

            if (state == MENU) {
                handleMenuEvents(e, state, running);
            }
            else if (state == PLAYING) {
                handlePlayngEvents(e, state);
                ninja.handleInput(e, jumping);
            }
            else if (state == OPTION) {
                handleOptionEvents(e, state, playMusic, playSound);
            }
            else if (state == PAUSE) {
                handlePauseEvents(e, state, score, ninja, jumping, lastTime);
            }
            else if (state == GAME_OVER) {
                handleGameOverEvents(e, state, score, ninja, jumping, lastTime);
            }
        }
        if (state == MENU) {
           //reset game
            resetGame(score,ninja,jumping,lastTime);

            renderMainMenu(renderer);
        }
        else if(state==PLAYING) {
            //khoi chay intro va jumping
            ninja.update(deltaTime, jumping);
            ninja.animate(jumping);

            //tao vat can
            obstacle::spawnObs(deltaTime, ninja.getOnTheLeft());
            obstacle::obsRun(deltaTime, score);

            //kiem tra va cham giua ninja va obs
            bool checkVacham = false;
            SDL_Rect ninjaRect = ninja.getRect();
            checkVacham |= checkObstacleCollision(ninjaRect, score, shieldActive, shieldStartTime, jumping);
            checkVacham |= checkSquirrelCollision(ninjaRect, score, shieldActive, jumping);
            checkVacham |= checkBladeCollision(ninjaRect, score, shieldActive, jumping);

            if (checkVacham) {
                state = GAME_OVER;
                Mix_PlayChannel(-1, fallSound, 0);
            }

            renderPlayng(renderer, score, deltaTime);

            //ve ninja
            ninja.render(renderer, jumping, shieldActive);

            for (auto& obs : obstacle::getObstacles()) obs.render(renderer); // ve obs
            for (auto& squirrel : obstacle::getSquirrels()) squirrel.render(renderer); // ve squirrel
            for (auto& blade : obstacle::getBlades()) blade.render(renderer); // ve blade
                
            SDL_RenderPresent(renderer);
        }

        else if (state == GAME_OVER) {
            updateHighScore(score);
            //hien thi man hinh gameover
            renderGameOverMenu(renderer, score);
        }
        else if (state == OPTION) {
            renderOptionMenu(renderer, playMusic, playSound);
        }
        else if (state == PAUSE) {
            renderPauseMenu(renderer);
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

void resetGame(int& score, ninja& ninja, bool& jumping, Uint32& lastTime) {
    score = 0;
    obstacle::SPEED = 200.0;
    ninja = { WALL_WIDTH, WINDOW_HEIGHT - NINJA_SIZE };
    obstacle::getObstacles().clear();
    obstacle::getSquirrels().clear();
    obstacle::getBlades().clear();
    obstacle::birdExists = false;
    obstacle::squirrelExists = false;
    jumping = false;
    lastTime = SDL_GetTicks();
    SDL_Delay(100); // tranh xung dot game 
}