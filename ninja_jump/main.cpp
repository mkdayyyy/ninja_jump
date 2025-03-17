#include "commonFunc.h"
#include "ninja.h"
#include "obstacle.h"
#include "button.h"
#include "LTexture.h"

int main(int argc, char* argv[]) {
    initSDL();
    SDL_Window* window = createWindow();
    SDL_Renderer* renderer=createRenderer(window);
    obstacle::loadTextures(renderer); // tai hinh anh obs
    ninja::loadTextures(renderer); // tai hinh anh ninja
    loadCommonTexture(renderer); // tai hinh anh nen

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
                state = handleMenuClick(e.button.x, e.button.y, running);
            }
        }

        // in menu
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //in background menu
        SDL_Rect dstRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
        SDL_RenderCopy(renderer, menuTexture, NULL, &dstRect);

        //ve nut play
        SDL_SetRenderDrawColor(renderer,0, 0, 255, 255);
        std::string play = "Play";
        SDL_RenderFillRect(renderer, &playBut.rectBut);
        renderText(renderer, play, playBut.rectBut.x + 30, playBut.rectBut.y + 15,true);

        //ve nut quit
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &quitBut.rectBut);
        std::string quit = "Quit";
        renderText(renderer,quit, quitBut.rectBut.x + 30, quitBut.rectBut.y + 15,true);

        

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

            //kiem tra va cham giua ninja va obs
            SDL_Rect ninjaRect = ninja.getRect();
            for (const auto& obs : obstacle::getObstacles()) { // &obs de chinh sua vao obs cua obstacles chu ko phai tao 1 ban sao
                SDL_Rect obsRect = obs.getRect();
                if (SDL_HasIntersection(&ninjaRect, &obsRect)) {
                    if (obs.getType() == obstacleType::ROPE) {
                        continue;
                    }
                    state = GAME_OVER;
                    Mix_PlayChannel(-1, fallSound, 0);
                }
            }

			//kiem tra va cham giua ninja va squirrel
			for (const auto& squirrel : obstacle::getSquirrels()) {
				SDL_Rect squirrelRect = squirrel.getRect();
				if (SDL_HasIntersection(&ninjaRect, &squirrelRect)) {
					state = GAME_OVER;
					Mix_PlayChannel(-1, fallSound, 0);
				}
			}
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // ve ingame back
            SDL_Rect dstRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
            SDL_RenderCopy(renderer, ingameTexture, &dstRect, NULL);

            //ve ninja, sau nay chen anh
            /*SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &ninjaRect);*/
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
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
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
            }

            //hien thi man hinh gameover
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            std::string restartText = "Game Over! Press R to Restart";
            renderText(renderer,restartText , 30, 250,true);

            std::string scoreText = "Score: " + std::to_string(score);
            renderText(renderer, scoreText, 200, 300,true);

            SDL_RenderPresent(renderer);
        }
        
        limitFPS(currentTime);
    }

    obstacle::freeTextures();
    destroySDL();
    return 0;
}

