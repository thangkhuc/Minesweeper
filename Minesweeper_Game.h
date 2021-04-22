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
    bool demo(int); //menupunkt

    void addGame(); //add the current game into the "games" array
    void printHighscores() const;
    void saveGame() const;
    void loadSaveGame(); //load saved Games into the "games" array
    void setZug(const Eingabe&); // save each move into "zug" attribute  through insert value
};

#endif // MINESWEEPER_GAME_H
