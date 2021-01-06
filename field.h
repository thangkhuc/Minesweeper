#ifndef FIELD_H
#define FIELD_H
#include "Cell.h"
#include <random>
#include "Eingabe.h"
#include "spieler.h"
#include <fstream>

extern Spieler* p_highscores;

class Field{
private:
    int rows, cols;
    Cell** p_field;
    int* p_minePos;
    int mineNumber;
public:
    Field();
    ~Field();

    void setMinePos();
    void printField();
    void minePosSort();
    bool openCell(const Eingabe eingabe);
    int aroundMineCount(const Eingabe eingabe);
    void explodieren();
    void placeMine();
    void setSize();
    bool winCondition();
    void menu();
    void spielen();
    void einleitung();
    void highscores();
    void set_Highscore(Spieler spieler);
    void highscores_ausgeben();
    void save_Highscores();
};

void load_Highscores();// nimm die gespeicherten Highscores aus gespeichertem Platz
#endif // FIELD_H
