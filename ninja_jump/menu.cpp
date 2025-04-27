#include "menu.h"

extern button playButton, exitButton, optionButton;
extern button tryAgainButton, menuButton, musicButton, soundButton, quitButton;
extern button continueButton, restartButton;
extern SDL_Texture* menuTexture;
extern SDL_Texture* pauseMenu;
extern SDL_Texture* gameOverPanel;
extern SDL_Texture* gameOverBack;
extern SDL_Texture* offSlash;
extern SDL_Texture* scorebar;
extern Mix_Chunk* clickSound, * gameOverSound;
extern int highestScore;

void renderMainMenu(SDL_Renderer* renderer) {
    SDL_Rect dstRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
    SDL_RenderCopy(renderer, menuTexture, NULL, &dstRect);
    playButton.render(renderer);
    exitButton.render(renderer);
    optionButton.render(renderer);
    SDL_RenderPresent(renderer);
}

void renderOptionMenu(SDL_Renderer* renderer, bool playMusic, bool playSound) {
    SDL_Rect backRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
    SDL_RenderCopy(renderer, menuTexture, NULL, &backRect);

    SDL_Rect optionRect = { 90,150,300,300 };
    SDL_RenderCopy(renderer, pauseMenu, NULL, &optionRect);

    soundButton.render(renderer);
    musicButton.render(renderer);
    quitButton.render(renderer);

    std::string optionText = "OPTION";
    renderText(renderer, optionText, WINDOW_WIDTH / 2 - 50, 165, true, 2, WHITE);

    if (!playMusic) {
        SDL_Rect offMusicRect = { 150,230,80,80 };
        SDL_RenderCopy(renderer, offSlash, NULL, &offMusicRect);
    }
    if (!playSound) {
        SDL_Rect offSoundRect = { 250,230,80,80 };
        SDL_RenderCopy(renderer, offSlash, NULL, &offSoundRect);
    }
    SDL_RenderPresent(renderer);
}

void renderPauseMenu(SDL_Renderer* renderer) {
    SDL_Rect pauseRect = { 90,150,300,300 };
    SDL_RenderCopy(renderer, pauseMenu, NULL, &pauseRect);

    continueButton.render(renderer);
    menuButton.render(renderer);
    restartButton.render(renderer);

    std::string pauseText = "PAUSE";
    renderText(renderer, pauseText, WINDOW_WIDTH / 2 - 50, 160, true, 2, WHITE);

    SDL_RenderPresent(renderer);
}

void renderGameOverMenu(SDL_Renderer* renderer, int score) {
    SDL_Rect backRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
    SDL_RenderCopy(renderer, gameOverBack, NULL, &backRect);

    SDL_Rect panelRect = { 65,100,350,350 };
    SDL_RenderCopy(renderer, gameOverPanel, NULL, &panelRect);

    tryAgainButton.render(renderer);
    menuButton.render(renderer);

    std::string scoreText = "Score: " + std::to_string(score);
    renderText(renderer, scoreText, 150, 130, true, 1, BLACK);

    std::string highScoreText = "High Score: " + std::to_string(highestScore);
    renderText(renderer, highScoreText, 150, 190, true, 1, RED);

    SDL_RenderPresent(renderer);
}

void renderPlayng(SDL_Renderer* renderer, int score,float deltaTime) {
    renderIngameText(renderer, ingameTexture, deltaTime);
    std::string scoreText = "Score: " + std::to_string(score);
    SDL_Rect scoreBar = { 145,15,200,50 };
    SDL_RenderCopy(renderer, scorebar, NULL, &scoreBar);
    renderText(renderer, scoreText, 180, 20, true, 1, BLACK);
    pauseButton.render(renderer);
}
// ----- Handle Events -----

void handleMenuEvents(SDL_Event& e, GameState& state, bool& running) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;
        if (playButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            state = PLAYING;
        }
        else if (exitButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            running = false;
        }
        else if (optionButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            state = OPTION;
        }
    }
}

void handleOptionEvents(SDL_Event& e, GameState& state, bool& playMusic, bool& playSound) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;
        if (musicButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            if (playMusic) {
                Mix_HaltMusic();
            }
            else {
                Mix_PlayMusic(backgroundMusic, -1);
            }
            playMusic = !playMusic;
        }
        if (soundButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            if (playSound) {
                Mix_Volume(-1, 0);
            }
            else {
                Mix_Volume(-1, MIX_MAX_VOLUME / 3);
            }
            playSound = !playSound;
        }
        if (quitButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            state = MENU;
        }
    }
}

void handlePauseEvents(SDL_Event& e, GameState& state, int& score, ninja& ninja, bool& jumping, Uint32& lastTime) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;
        if (menuButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            state = MENU;
        }
        if (restartButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            score = 0;
            obstacle::SPEED = 200.0;
            ninja = { WALL_WIDTH, WINDOW_HEIGHT - NINJA_SIZE };
            obstacle::getObstacles().clear();
            obstacle::getSquirrels().clear();
            obstacle::getBlades().clear();
            obstacle::birdExists = false;
            obstacle::squirrelExists = false;
            jumping = false;
            lastTime = SDL_GetTicks();
            SDL_Delay(100); // tranh xung dot game
            Mix_PlayChannel(-1, gameOverSound, 0);
            state = PLAYING;
        }
        if (continueButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            state = PLAYING;
        }
    }
}

void handleGameOverEvents(SDL_Event& e, GameState& state, int& score, ninja& ninja, bool& jumping, Uint32& lastTime) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;
        if (tryAgainButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            score = 0;
            obstacle::SPEED = 200.0;
            ninja = { WALL_WIDTH, WINDOW_HEIGHT - NINJA_SIZE };
            obstacle::getObstacles().clear();
            obstacle::getSquirrels().clear();
            obstacle::getBlades().clear();
            obstacle::birdExists = false;
            obstacle::squirrelExists = false;
            jumping = false;
            lastTime = SDL_GetTicks();
            SDL_Delay(100); // tranh xung dot game
            state = PLAYING;
            Mix_PlayChannel(-1, gameOverSound, 0);
        }
        else if (menuButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            state = MENU;
        }
    }
}

void handlePlayngEvents(SDL_Event& e, GameState& state) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;
        if (pauseButton.isClicked(x, y)) {
            Mix_PlayChannel(-1, clickSound, 0);
            state = PAUSE;
        }
    }
}