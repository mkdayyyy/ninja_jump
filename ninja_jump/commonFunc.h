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
#include "obstacle.h"
#include "ninja.h"


static SDL_Window* window = NULL;  // khoi tao window
static SDL_Renderer* renderer = NULL; //tao renderer
static TTF_Font* font = NULL; //them font cho van ban

//cac bien global
const int WINDOW_WIDTH = 480; // chieu dai cua window
const int WINDOW_HEIGHT = 600; // chieu cao cua windo
const int WALL_WIDTH = 46; // chieu dai cua tuong
const std::string WINDOW_TITLE = "Ninja Jump"; //tieu de cua window
const int NINJA_SIZE = 30; //kich thuoc cua ninja
const float JUMP_DURATION = 0.3; // thoi gian 1 lan ninja nhay
const float INTRO_DURATION = 0.5; // thoi gian intro 
static float OBSTACLE_SPAWN_TIME = 2; // thoi gian obs spawn 
const Uint32 TARGET_FPS = 144; //fps
const Uint32 FRAME_TIME = 1000 / TARGET_FPS; // thoi gian moi khung hinh de dc fps nhu mong muon
extern Mix_Chunk* jumpSound; // am thanh nhay
extern Mix_Chunk* hitSound; // am thanh khi va cham
extern Mix_Chunk* gameOverSound; // am thanh khi thua game
extern Mix_Chunk* fallSound; // am thanh khi nga
extern Mix_Music* backgroundMusic; // am thanh nen
extern Mix_Chunk* clickSound; // am thanh khi click
extern Mix_Chunk* landSound; // am thanh khi dap dat
static enum GameState { MENU, PLAYING, GAME_OVER, PAUSE, OPTION }; // quan li trang thai game
static bool gameReset = false; // reset game moi khi an vao play
extern SDL_Texture* menuTexture; // hinh anh menu background
extern SDL_Texture* ingameTexture; // hinh anh background khi chay game
extern SDL_Texture* scorebar; // hinh anh scoreBar
extern SDL_Texture* gameOverPanel; // panel trong gameover
extern SDL_Texture* gameOverBack; // background gameover
extern SDL_Texture* pauseMenu; //menu pause game
extern SDL_Texture* offSlash; // dau gach do

extern float bgY; // 

void initSDL(); //kiem tra init
SDL_Window* createWindow(); //kiem tra tao window
SDL_Renderer* createRenderer(SDL_Window* window); //kiem tra tao renderer
void limitFPS(Uint32 currentTime); //gioi han fps
void destroySDL(); //giai phong bo nho,sdl
void renderText(SDL_Renderer* renderer, std::string& text, int x, int y,bool centerX); //in van ban
SDL_Texture* loadTexture(const std::string& file,SDL_Renderer* renderer); //tai hinh anh
void loadCommonTexture(SDL_Renderer* renderer);
//void renderText(SDL_Renderer* renderer);
void renderIngameText(SDL_Renderer* renderer, SDL_Texture* ingameTexture,float deltaTime);
#endif
