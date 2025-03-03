#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int WALL_WIDTH = 100;
const int NINJA_SIZE = 50;

int main(int argc,char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    //Khoi tao window
    SDL_Window* window = SDL_CreateWindow("Ninja Jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Khong khoi tao dc window: %s\n", SDL_GetError());
        return 1;
    }

    //Khoi tao renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    //kiem soat game
    bool running = true;
    int ninjaX = WALL_WIDTH;
    int ninjaY = WINDOW_HEIGHT - NINJA_SIZE;
    bool onTheLeft = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { running = false; }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                if (onTheLeft) {
                    ninjaX = WINDOW_WIDTH - WALL_WIDTH - NINJA_SIZE;         
                }
                else {
                    ninjaX = WALL_WIDTH;
                }
                onTheLeft = !onTheLeft;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //ve 2 ben tuong
        SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
        SDL_Rect leftWall = { 0,0,WALL_WIDTH,WINDOW_HEIGHT };
        SDL_Rect rightWall = { WINDOW_WIDTH - WALL_WIDTH,0,WALL_WIDTH,WINDOW_HEIGHT };
        SDL_RenderFillRect(renderer, &leftWall);
        SDL_RenderFillRect(renderer, &rightWall);

        //ve ninja mau do
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect ninjaRect = { ninjaX,ninjaY,NINJA_SIZE,NINJA_SIZE };
        SDL_RenderFillRect(renderer, &ninjaRect);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);

    }
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;


}

