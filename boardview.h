#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <SDL.h>
#include <vector>
#include "Board.h"
#include "Graphics.h"

class BoardView {
public:
    BoardView(SDL_Renderer* renderer);
    ~BoardView();

    void render();
    void handleEvent(SDL_Event& event);
    Board* getBoard() { return board; }
    enum GameState { PLAYING, WIN };
    GameState gameState;
    void resetBoard();

private:
    int selectedX, selectedY;
    int offsetX, offsetY;
    std::vector<std::pair<int, int>> path;
    SDL_Renderer* renderer;
    Board* board;
    int cellSize;
    std::vector<SDL_Texture*> textures;
    void loadTextures();
    Uint32 pathStartTime = 0;
    Uint32 winStartTime = 0;
};

#endif

