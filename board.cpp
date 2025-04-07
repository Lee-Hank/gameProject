#include "Board.h"
#include <algorithm>
#include <ctime>

Board::Board(int rows, int cols) : rows(rows), cols(cols), _x(-1), _y(-1) {
    pokemons.resize(rows + 2, std::vector<int>(cols + 2, -1));
    initializeBoard();
}

void Board::initializeBoard() {
    std::vector<int> pokemonTypes;
    int numPairs = (rows * cols) / 2;

    srand(time(nullptr));

    for (int i = 0; i < numPairs; ++i) {
        int type = i % 12;
        pokemonTypes.push_back(type);
        pokemonTypes.push_back(type);
    }

    std::random_shuffle(pokemonTypes.begin(), pokemonTypes.end());

    int index = 0;
    for (int i = 1; i <= rows; ++i) {
        for (int j = 1; j <= cols; ++j) {
            pokemons[i][j] = pokemonTypes[index++];
        }
    }
}



Board::~Board() {}

bool Board::selectPokemon(int x, int y) {
    if (_x == -1 && _y == -1) {
        _x = x;
        _y = y;
        return false;
    }

    if(_x == x && _y == y){
        _x = -1;
        _y = -1;
        return false;
    }

    if (pokemons[x][y] != pokemons[_x][_y] || !canConnect(_x, _y, x, y)) {
        _x = -1;
        _y = -1;
        return false;
    }

    return true;
}

bool Board::canConnect(int _x, int _y, int x, int y) {
    auto path = findPath(_x, _y, x, y);
    return path.size() >= 2 && path.size() <= 4;
}

std::vector<std::pair<int, int>> Board::findPath(int _x, int _y, int x, int y) {
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};

    std::vector<std::vector<int>> grid(rows+2, std::vector<int>(cols+2, 0));
    for (int i = 0; i < rows+2; ++i) {
        for (int j = 0; j < cols+2; ++j) {
            grid[i][j] = (pokemons[i][j] != -1);
        }
    }

    std::deque<std::pair<int, int>> queue;
    std::vector<std::vector<std::pair<int, int>>> trace(rows+2, std::vector<std::pair<int, int>>(cols+2, {-1, -1}));

    queue.push_back({x, y});
    trace[x][y] = {-2, -2};
    grid[x][y] = grid[_x][_y] = 0;

    while (!queue.empty()) {
        auto u = queue.front();
        queue.pop_front();

        if (u.first == _x && u.second == _y) break;

        for (int i = 0; i < 4; ++i) {
            int nx = u.first + dx[i];
            int ny = u.second + dy[i];

            while (nx >= 0 && nx <= rows+1 && ny >= 0 && ny <= cols+1 && grid[nx][ny] == 0) {
                if (trace[nx][ny].first == -1) {
                    trace[nx][ny] = u;
                    queue.push_back({nx, ny});
                }
                nx += dx[i];
                ny += dy[i];
            }
        }
    }

    std::vector<std::pair<int, int>> path;
    if (trace[_x][_y].first != -1) {
        while (_x != -2) {
            path.push_back({_x, _y});
            auto temp = trace[_x][_y];
            _x = temp.first;
            _y = temp.second;
        }
    }
    return path;
}

void Board::removePokemon(int x, int y) {
    pokemons[x][y] = -1;
}

int Board::getPokemonAt(int x, int y) {
    return pokemons[x][y];
}

bool Board::isBoardEmpty() {
    for (int i = 1; i <= rows; ++i) {
        for (int j = 1; j <= cols; ++j) {
            if (pokemons[i][j] != -1) {
                return false;
            }
        }
    }
    return true;
}
