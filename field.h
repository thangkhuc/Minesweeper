#ifndef FIELD_H
#define FIELD_H
#include "Cell.h"
#include <random>
#include "Eingabe.h"
#include "spieler.h"
#include <fstream>

class Field{
private:
    int rows, cols;
    Cell** p_field;
    int* p_minePos;
    int mineNumber;
    static Spieler* p_highscores; // static variable
public:
    Field();
    ~Field();

    void setMinePos();
    void printField() const;
    void minePosSort();
    bool openCell(Eingabe);
    int aroundMineCount(Eingabe);
    void explodieren();
    void placeMine();
    void setSize();
    bool winCondition() const;
    void menu();
    void spielen();
    void einleitung();
    void highscores();
    void set_Highscore(const Spieler& spieler);
    void print_highscores() const;
    void save_Highscores() const;
    void load_Highscores() const;// nimm die gespeicherten Highscores aus gespeichertem Platz
};

#endif // FIELD_H
