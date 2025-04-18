#include "Game.h"
#include "Menu.h"
#include <SDL_image.h>
#include <iostream>

Game::Game() : window(nullptr), renderer(nullptr), boardView(nullptr), backgroundTexture(nullptr), isRunning(false) {}

Game::~Game() {}

bool Game::init(const char* title, int width, int height) {
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "IMG_Init failed\n";
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "SDL_CreateWindow failed\n";
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "SDL_CreateRenderer failed\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Sound falsed\n";
        return false;
    }

    backgroundMusic = Mix_LoadMUS("sound/1.mp3");
    if (!backgroundMusic) {
        std::cout << "Sound falsed\n";
        return false;
    }

    Mix_PlayMusic(backgroundMusic, -1);

    Menu menu(renderer);
    bool inMenu = true;
    while (inMenu) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            int action = menu.handleEvent(event);
            if (action == 1) {
                inMenu = false;
            } else if (action == 2) {
                cleanup();
                return false;
            }
        }
        menu.update();
        menu.render();
        SDL_Delay(16);
    }

    boardView = new BoardView(renderer);

    SDL_Surface* bgSurface = IMG_Load("assets/background.png");
    if (!bgSurface) {
        std::cout << "background failed\n";
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    if (!backgroundTexture) {
        std::cout << "background failed\n";
        return false;
    }

    isRunning = true;
    return true;
}

void Game::run() {
    while (isRunning) {
        processEvents();
        render();
    }
}

void Game::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        } else {
            boardView->handleEvent(event);
        }
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    if (backgroundTexture) {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }

    boardView->render();
    SDL_RenderPresent(renderer);
}

void Game::cleanup() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }

    delete boardView;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    if (backgroundMusic) {
    Mix_FreeMusic(backgroundMusic);
    backgroundMusic = nullptr;
    }

    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
}
