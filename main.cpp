#include "time.h"
#include "Minesweeper_Game.h"

int main() {
    srand(time(0));

    MinesweeperGame game;
    game.load_saveGame();

    bool state = game.menu();

    while (!state){
        MinesweeperGame game;
        state = game.menu();
    }

    return 0;
}
