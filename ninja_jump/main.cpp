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
            ninja.handleInput(e, jumping);
        }

        ninja.update(deltaTime, jumping); //khoi chay intro va jumping

        //tao vat can
        obstacle::spawnObs(deltaTime);
        obstacle::obsRun(deltaTime);

        //kiem tra va cham giua ninja va obs
        SDL_Rect ninjaRect = ninja.getRect();
        for (const auto& obs : obstacle::getObstacles()) { // &obs de chinh sua vao obs cua obstacles chu ko phai tao 1 ban sao
            SDL_Rect obsRect = obs.getRect();
            if (SDL_HasIntersection(&ninjaRect, &obsRect)) {
                running = false;
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

        SDL_RenderPresent(renderer);
        
        limitFPS(currentTime);
    }

    destroySDL();
    return 0;
}

