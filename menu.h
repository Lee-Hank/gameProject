#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>

class Menu {
private:
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    SDL_Texture* pressAnyKeyTexture;
    int alpha;
    bool fadingIn;

public:
    Menu(SDL_Renderer* renderer);
    ~Menu();

    void render();
    void update();
    int handleEvent(SDL_Event& event);
};

#endif
