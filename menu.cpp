#include "Menu.h"
#include "Graphics.h"
#include <iostream>

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer), backgroundTexture(nullptr), pressAnyKeyTexture(nullptr), alpha(0), fadingIn(true) {
    backgroundTexture = Graphics::loadTexture(renderer, "assets/menu.png");
    pressAnyKeyTexture = Graphics::loadTexture(renderer, "assets/key.png");

    if (!backgroundTexture) {
        std::cout << "menu false\n";
    }

    if (!pressAnyKeyTexture) {
        std::cout << "key false\n";
    }
}

Menu::~Menu() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(pressAnyKeyTexture);
}

void Menu::update() {
    if (fadingIn) {
        alpha += 3;
        if (alpha >= 255) {
            alpha = 255;
            fadingIn = false;
        }
    } else {
        alpha -= 3;
        if (alpha <= 0) {
            alpha = 0;
            fadingIn = true;
        }
    }
}

void Menu::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    SDL_SetTextureAlphaMod(pressAnyKeyTexture, alpha);
    SDL_Rect textRect = { 400, 570, 400, 100 };
    SDL_RenderCopy(renderer, pressAnyKeyTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);
}

int Menu::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
        return 1;
    }
    if (event.type == SDL_QUIT) {
        return 2;
    }
    return 0;
}
