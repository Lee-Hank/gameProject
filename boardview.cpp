#include "BoardView.h"

int rows = 8, cols = 12;

BoardView::BoardView(SDL_Renderer* renderer) : renderer(renderer), selectedX(-1), selectedY(-1) {
    board = new Board(rows, cols);
    cellSize = 72;
    int screenWidth, screenHeight;
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
    offsetX = (screenWidth - (cols * cellSize)) / 2;
    offsetY = (screenHeight - (rows * cellSize)) / 2;
    loadTextures();
}

BoardView::~BoardView() {
    for (auto texture : textures) {
        SDL_DestroyTexture(texture);
    }
    delete board;
}

void BoardView::resetBoard() {
    delete board;
    board = new Board(rows, cols);
    gameState = PLAYING;
}

void BoardView::loadTextures() {
    const char* imageFiles[] = {
        "assets/pokemon0.png",
        "assets/pokemon1.png",
        "assets/pokemon2.png",
        "assets/pokemon3.png",
        "assets/pokemon4.png",
        "assets/pokemon5.png",
        "assets/pokemon6.png",
        "assets/pokemon7.png",
        "assets/pokemon8.png",
        "assets/pokemon9.png",
        "assets/pokemon10.png",
        "assets/pokemon11.png"
    };

    for (const char* file : imageFiles) {
        textures.push_back(Graphics::loadTexture(renderer, file));
    }
}

void BoardView::render() {
    if (gameState == WIN) {
        SDL_Texture* winTexture = Graphics::loadTexture(renderer, "assets/win.png");
        SDL_Rect destRect = {168, 87, 864, 576};
        SDL_RenderCopy(renderer, winTexture, nullptr, &destRect);
        SDL_DestroyTexture(winTexture);

        if (SDL_GetTicks() - winStartTime > 2500) {
            resetBoard();
        }
        return;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int pokemonID = board->getPokemonAt(i + 1, j + 1);
            if (pokemonID != -1) {
                SDL_Rect destRect = {offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize};
                SDL_RenderCopy(renderer, textures[pokemonID], nullptr, &destRect);
            }
        }
    }

    if (selectedX != -1 && selectedY != -1) {
        Graphics::drawBorder(renderer,
        offsetX + selectedY * cellSize,
        offsetY + selectedX * cellSize,
        cellSize, cellSize,
        {0, 255, 0, 255});
    }

    if (!path.empty() && SDL_GetTicks() - pathStartTime < 500) {
        Graphics::drawPath(renderer, path, cellSize, offsetX, offsetY, {255, 0, 0, 255});
    } else {
        path.clear();
    }
}

void BoardView::handleEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x = 0, y = 0;
        if (event.button.y - offsetY >= 0 && event.button.x - offsetX >= 0) {
            x = (event.button.y - offsetY) / cellSize + 1;
            y = (event.button.x - offsetX) / cellSize + 1;
        }
        if (x >= 1 && x <= rows && y >= 1 && y <= cols) {
            if (selectedX == -1 && selectedY == -1) {
                if (board->getPokemonAt(x, y) != -1) {
                    selectedX = x - 1;
                    selectedY = y - 1;
                    board->_x = x;
                    board->_y = y;
                }
            } else {
                if (board->selectPokemon(x, y)) {
                    path = board->findPath(board->_x, board->_y, x, y);
                    pathStartTime = SDL_GetTicks();
                    board->removePokemon(x, y);
                    board->removePokemon(board->_x, board->_y);
                    board->_x = board->_y = -1;
                    selectedX = selectedY = -1;

                    if (board->isBoardEmpty()) {
                        winStartTime = SDL_GetTicks();
                        gameState = WIN;
                    }
                } else {
                    selectedX = selectedY = -1;
                }
            }
        }
    }
}
