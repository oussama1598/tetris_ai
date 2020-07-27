#include "tetris.h"

int main() {
    Tetris game;

    while (game.is_running()) {
        game.render();
    }
}
