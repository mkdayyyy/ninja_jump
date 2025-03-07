#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int WALL_WIDTH = 100;
const int NINJA_SIZE = 50;
const float JUMP_DURATION = 0.3;
const float INTRO_DURATION = 0.5;

void initSDL();
SDL_Window* createWindow();
SDL_Renderer* createRenderer(SDL_Window* window);
#endif
