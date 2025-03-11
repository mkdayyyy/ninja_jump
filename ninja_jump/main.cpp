#include "commonFunc.h"
#include "ninja.h"
#include "obstacle.h"

int main(int argc, char* argv[]) {
    initSDL();

    SDL_Window* window = createWindow();
    SDL_Renderer* renderer=createRenderer(window);

    //quan li game
    bool running = true;
    bool jumping = false;
    int score = 0;
    Mix_Volume(-1, MIX_MAX_VOLUME/3);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
    Mix_PlayMusic(backgroundMusic, -1);

    //quan li trang thai game
    enum GameState { PLAYING, GAME_OVER };
    GameState state = PLAYING;

    ninja ninja(WALL_WIDTH, WINDOW_HEIGHT - NINJA_SIZE);// khoi tao ninja 
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    Uint32 lastTime = SDL_GetTicks(); // lay thoi gian trc khi chay

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

            //tao vat can
            obstacle::spawnObs(deltaTime, ninja.getOnTheLeft());
            obstacle::obsRun(deltaTime, score);

            //kiem tra va cham giua ninja va obs
            SDL_Rect ninjaRect = ninja.getRect();
            for (const auto& obs : obstacle::getObstacles()) { // &obs de chinh sua vao obs cua obstacles chu ko phai tao 1 ban sao
                SDL_Rect obsRect = obs.getRect();
                if (SDL_HasIntersection(&ninjaRect, &obsRect)) {
                    state = GAME_OVER;
                    Mix_PlayChannel(-1, fallSound, 0);
                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            //ve tuong xam, sau nay chen anh
            SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
            SDL_Rect leftWall = { 0, 0, WALL_WIDTH, WINDOW_HEIGHT };
            SDL_Rect rightWall = { WINDOW_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, WINDOW_HEIGHT };
            SDL_RenderFillRect(renderer, &leftWall);
            SDL_RenderFillRect(renderer, &rightWall);

            //ve ninja, sau nay chen anh
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &ninjaRect);

            //ve obstacle
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            for (auto& obs : obstacle::getObstacles()) {
                SDL_Rect obsRect = obs.getRect();
                SDL_RenderFillRect(renderer, &obsRect);
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

    destroySDL();
    return 0;
}

