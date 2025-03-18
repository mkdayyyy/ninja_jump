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

    //quan li game
    bool running = true;
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

    while (state == MENU) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                return 0;
            }
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
                    return 0;
                }
            }
        }

        //in background menu
        SDL_Rect dstRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
        SDL_RenderCopy(renderer, menuTexture, NULL, &dstRect);

        //ve nut 
        playButton.render(renderer);
        exitButton.render(renderer);

        SDL_RenderPresent(renderer);
    }

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0; // doi sang giay
        lastTime = currentTime;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { running = false; }

            if(state==PLAYING) {
                ninja.handleInput(e, jumping);
            }
        }
            
        if(state==PLAYING) {
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

            SDL_RenderPresent(renderer);
        }

        while (state == GAME_OVER) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = false;
                    return 0; // Thoat game hoan toan
                }
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
                        lastTime = SDL_GetTicks();// tranh xung dot thoi gian, vat can sinh ra trc khi restart
                        SDL_Delay(100); //tranh xung dot
                        Mix_PlayChannel(-1, gameOverSound, 0);

                        break; // thoat vong lap gameover de tiep tuc choi
                    }
                    else if (menuButton.isClicked(mouseX, mouseY)) {
                        Mix_PlayChannel(-1, clickSound, 0);
                        state = MENU;
                    }
                }
            }

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
        while (state == MENU) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = false;
                    return 0;
                }
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
                        return 0;
                    }
                }

            }
            //reset trang thai game
            score = 0;
            obstacle::SPEED = 200.0;
            ninja = { WALL_WIDTH, WINDOW_HEIGHT - NINJA_SIZE };
            obstacle::getObstacles().clear();
            obstacle::getSquirrels().clear();
            obstacle::birdExists = false;
            obstacle::squirrelExists = false;
            jumping = false;
            lastTime = SDL_GetTicks();// tranh xung dot thoi gian, vat can sinh ra trc khi restart
            SDL_Delay(100); //tranh xung dot

            //in background menu
            SDL_Rect dstRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
            SDL_RenderCopy(renderer, menuTexture, NULL, &dstRect);

            //ve nut 
            playButton.render(renderer);
            exitButton.render(renderer);

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