#include "commonFunc.h"
#include "ninja.h"
#include "obstacle.h"

int main(int argc, char* argv[]) {
    initSDL();
    SDL_Window* window = createWindow();
    SDL_Renderer* renderer=createRenderer(window);

    bool running = true;
    bool jumping = false;

    ninja ninja(WALL_WIDTH, WINDOW_HEIGHT - NINJA_SIZE); // khoi tao ninja 
    
    Uint32 lastTime = SDL_GetTicks(); // lay thoi gian trc khi chay

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0;
        lastTime = currentTime;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { running = false; }
            ninja.handleInput(e, jumping);
        }

        ninja.update(deltaTime, jumping);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
        SDL_Rect leftWall = { 0, 0, WALL_WIDTH, WINDOW_HEIGHT };
        SDL_Rect rightWall = { WINDOW_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, WINDOW_HEIGHT };
        SDL_RenderFillRect(renderer, &leftWall);
        SDL_RenderFillRect(renderer, &rightWall);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect ninjaRect = ninja.getRect();
        SDL_RenderFillRect(renderer, &ninjaRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

