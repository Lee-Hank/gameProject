#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include<SDL.h>
#include <deque>
#include <utility>

class Board {
public:
    Board(int rows, int cols);
    ~Board();

    bool selectPokemon(int x, int y);
    bool canConnect(int _x, int _y, int x, int y);
    std::vector<std::pair<int, int>> findPath(int _x, int _y, int x, int y);

    int getPokemonAt(int x, int y);
    void removePokemon(int x, int y);

    int _x, _y;

    bool isBoardEmpty();
private:
    int rows, cols;
    std::vector<std::vector<int>> pokemons;
    void initializeBoard();
};

#endif
