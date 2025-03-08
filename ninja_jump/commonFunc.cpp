#include "commonFunc.h"

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Khong khoi tao dc sdl: %s\n", SDL_GetError());
        exit(1);
    }
}

SDL_Window* createWindow() {
    SDL_Window* window = SDL_CreateWindow("Ninja Jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Khong khoi tao dc window: %s\n", SDL_GetError());
        exit(1);
    }
    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Khong khoi tao dc renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
    return renderer;
}

void limitFPS(Uint32 currentTime) {
    Uint32 frameEnd = SDL_GetTicks();
    Uint32 frameDuration = frameEnd - currentTime;
    if (frameDuration < FRAME_TIME) {
        SDL_Delay(FRAME_TIME - frameDuration);
    }
}

void destroySDL() {
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);
    SDL_Quit();
}