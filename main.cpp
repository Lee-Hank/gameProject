#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;
    if (!game.init("Pokemon", 1200, 750)) {
        return -1;
    }

    game.run();
    game.cleanup();

    return 0;
}
