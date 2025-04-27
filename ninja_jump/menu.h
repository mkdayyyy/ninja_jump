#pragma once
#include "commonFunc.h"
#include "button.h"
#include "LTexture.h"
#include "buttonManager.h"

// Render tung menu
void renderMainMenu(SDL_Renderer* renderer);
void renderOptionMenu(SDL_Renderer* renderer, bool playMusic, bool playSound);
void renderPauseMenu(SDL_Renderer* renderer);
void renderGameOverMenu(SDL_Renderer* renderer, int score);
void renderPlayng(SDL_Renderer* renderer, int score,float deltaTime);

// Xu li xu kien trong cac menu
void handleMenuEvents(SDL_Event& e, GameState& state, bool& running);
void handleOptionEvents(SDL_Event& e, GameState& state, bool& playMusic, bool& playSound);
void handlePauseEvents(SDL_Event& e, GameState& state, int& score, ninja& ninja, bool& jumping, Uint32& lastTime);
void handleGameOverEvents(SDL_Event& e, GameState& state, int& score, ninja& ninja, bool& jumping, Uint32& lastTime);
void handlePlayngEvents(SDL_Event& e, GameState& state);