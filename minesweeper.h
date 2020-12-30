#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include "spieler.h"
#include "Field.h"
#include <fstream>

extern Spieler* p_highscores;

bool menu();
bool einleitung();
bool highscores();
void set_Highscore(Spieler spieler);
void highscores_ausgeben();
void save_Highscores();
void load_Highscores();// nimm die gespeicherten Highscores aus gespeichertem Platz

#endif // MINESWEEPER_H
