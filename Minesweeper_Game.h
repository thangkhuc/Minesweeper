#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H
#include "field.h"
#include <unistd.h>

class MinesweeperGame : public Field
{
private:
    Player player;
    string zug;
    static MinesweeperGame* games;
public:
    MinesweeperGame();

    bool menu();
    void play(); //menupunkt
    bool tutorial(); //menupunkt
    bool highscores(); //menupunkt
    bool demo(); //menupunkt
    void add_game(); //add the current game into the "games" array
    void print_highscores() const;
    void save_game() const;
    void load_saveGame(); //load saved Games into the "games" array
    void set_zug(const Eingabe&); // save each move into "zug" attribute  through insert value
};

#endif // MINESWEEPER_GAME_H
