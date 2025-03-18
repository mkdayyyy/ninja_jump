#include "commonFunc.h"

Mix_Chunk* jumpSound = NULL;
Mix_Chunk* hitSound = NULL;
Mix_Chunk* gameOverSound = NULL;
Mix_Chunk* fallSound = NULL;
Mix_Chunk* clickSound = NULL;
Mix_Music* backgroundMusic = NULL;
Mix_Chunk* landSound = NULL;

SDL_Texture* menuTexture = nullptr;
SDL_Texture* ingameTexture = nullptr;
SDL_Texture* scorebar = nullptr;
SDL_Texture* playPic = nullptr;
SDL_Texture* exitPic = nullptr;
SDL_Texture* gameOverPanel = nullptr;
SDL_Texture* tryAgainPic = nullptr;
SDL_Texture* gameOverBack = nullptr;


float bgY = 568;

void initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Khong khoi tao dc SDL: %s\n", SDL_GetError());
        exit(1);
    }
    //load font 
    if (TTF_Init() < 0) {
        printf("Khong khoi tao dc SDL_ttf: %s\n", TTF_GetError());
        exit(1);
    }
    font = TTF_OpenFont("res/font/AzeretMono-Medium.ttf", 24);
    if (!font) {
        printf("Khong tai dc font: %s\n", TTF_GetError());
        exit(1);
    }
    //khoi tao am thanh
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Lỗi khởi tạo SDL_mixer: %s\n", Mix_GetError());
        exit(1);
    }

    //load am thanh hieu ung
    jumpSound = Mix_LoadWAV("res/sound/jump.wav");
    fallSound = Mix_LoadWAV("res/sound/fall_1.wav");
    hitSound = Mix_LoadWAV("res/sound/hit.wav");
    gameOverSound = Mix_LoadWAV("res/sound/gameover.wav");
    clickSound = Mix_LoadWAV("res/sound/click.wav");
    landSound = Mix_LoadWAV("res/sound/land.wav");

    //load am nhac
    backgroundMusic = Mix_LoadMUS("res/sound/music.ogg");


}

SDL_Window* createWindow() {
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(hitSound);
    Mix_FreeChunk(gameOverSound);
    Mix_FreeChunk(fallSound);
    Mix_CloseAudio();
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderText(SDL_Renderer* renderer, std::string& text, int x, int y,bool centerX) {
    SDL_Color textColor = { 0,0,0,255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect = { x,y,surface->w,surface->h };

    if (centerX) {
        textRect.x = (WINDOW_WIDTH - surface->w) / 2; //can giua
    }

    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

}

SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

void loadCommonTexture(SDL_Renderer* renderer) {
    menuTexture = loadTexture("res/menu/back.png", renderer);
    ingameTexture = loadTexture("res/background/back1.png", renderer);
    scorebar = loadTexture("res/button/scorebar.png", renderer);
    gameOverPanel = loadTexture("res/menu/gameover_panel.png", renderer);
    gameOverBack = loadTexture("res/menu/back2.png", renderer);

}

void renderIngameText(SDL_Renderer* renderer, SDL_Texture* ingameTexture,float deltaTime) {
    bgY -= obstacle::SPEED * deltaTime;

    if (bgY <=100) {
        bgY = 568;
    }
    SDL_Rect rectBg = { 0,bgY,WINDOW_WIDTH,WINDOW_HEIGHT };
    SDL_RenderCopy(renderer, ingameTexture, &rectBg, NULL);

}
