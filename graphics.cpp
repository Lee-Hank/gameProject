#include "Graphics.h"

SDL_Window* Graphics::window = nullptr;
SDL_Renderer* Graphics::renderer = nullptr;

bool Graphics::init(const char* title, int width, int height) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        return false;
    }
    return true;
}

void Graphics::clear() {
    SDL_RenderClear(renderer);
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}

void Graphics::cleanup() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

SDL_Texture* Graphics::loadTexture(SDL_Renderer* renderer, const std::string& path) {
    return IMG_LoadTexture(renderer, path.c_str());
}

void Graphics::renderTexture(SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect dest = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

SDL_Renderer* Graphics::getRenderer() {
    return renderer;
}
