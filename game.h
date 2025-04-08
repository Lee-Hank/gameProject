#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "BoardView.h"
#include "Menu.h"
#include <SDL_mixer.h>

enum GameState { MENU, PLAYING };

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    BoardView* boardView;
    Menu* menu;
    SDL_Texture* backgroundTexture;
    bool isRunning;
    GameState gameState;
    Mix_Music* backgroundMusic;

public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void run();
    void processEvents();
    void render();
    void cleanup();
};

#endif
