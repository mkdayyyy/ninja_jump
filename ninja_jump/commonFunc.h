#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <ctime>
#include <string>
#include <algorithm>


static SDL_Window* window = NULL; 
static SDL_Renderer* renderer = NULL;
static TTF_Font* font = NULL; //them font cho van ban

//cac bien global
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 600;
const int WALL_WIDTH = 100;
const int NINJA_SIZE = 50;
const float JUMP_DURATION = 0.3;
const float INTRO_DURATION = 0.5;
static float OBSTACLE_SPAWN_TIME = 2;
const Uint32 TARGET_FPS = 144; 
const Uint32 FRAME_TIME = 1000 / TARGET_FPS;

void initSDL(); //kiem tra init
SDL_Window* createWindow(); //kiem tra tao window
SDL_Renderer* createRenderer(SDL_Window* window); //kiem tra tao renderer
void limitFPS(Uint32 currentTime); //gioi han fps
void destroySDL(); //giai phong bo nho, sdl
void renderText(SDL_Renderer* renderer, std::string& text, int x, int y,bool centerX);
#endif
