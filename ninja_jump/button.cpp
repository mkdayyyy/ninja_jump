#include "button.h"

button::button(int x, int y, int w, int h, const std::string& texturePath, SDL_Renderer* renderer) {
    rect = { x, y, w, h };
    texture = loadTexture(texturePath, renderer);
}

void button::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

bool button::isClicked(int mouseX, int mouseY) {
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
        mouseY >= rect.y && mouseY <= rect.y + rect.h);
}