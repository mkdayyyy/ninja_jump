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


static SDL_Window* window = NULL;  // khoi tao window
static SDL_Renderer* renderer = NULL; //tao renderer
static TTF_Font* font = NULL; //them font cho van ban

//cac bien global
const int WINDOW_WIDTH = 500; // chieu dai cua window
const int WINDOW_HEIGHT = 600; // chieu cao cua windo
const int WALL_WIDTH = 100; // chieu dai cua tuong
const std::string WINDOW_TITLE = "Ninja Jump";
const int NINJA_SIZE = 50; //kich thuoc cua ninja
const float JUMP_DURATION = 0.3; // thoi gian 1 lan ninja nhay
const float INTRO_DURATION = 0.5; // thoi gian intro 
static float OBSTACLE_SPAWN_TIME = 2; // thoi gian obs spawn 
const Uint32 TARGET_FPS = 144; //fps
const Uint32 FRAME_TIME = 1000 / TARGET_FPS; // thoi gian moi khung hinh de dc fps nhu mong muon
static Mix_Chunk* jumpSound = NULL; // am thanh nhay
static Mix_Chunk* hitSound = NULL; // am thanh khi va cham
static Mix_Chunk* gameOverSound = NULL; // am thanh khi thua game
static Mix_Chunk* fallSound = NULL; // am thanh khi nga

void initSDL(); //kiem tra init
SDL_Window* createWindow(); //kiem tra tao window
SDL_Renderer* createRenderer(SDL_Window* window); //kiem tra tao renderer
void limitFPS(Uint32 currentTime); //gioi han fps
void destroySDL(); //giai phong bo nho,sdl
void renderText(SDL_Renderer* renderer, std::string& text, int x, int y,bool centerX); //in van ban

#endif
