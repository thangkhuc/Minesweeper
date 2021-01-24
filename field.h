#ifndef FIELD_H
#define FIELD_H
#include "Cell.h"
#include <random>
#include "Eingabe.h"
#include "Player.h"
#include <fstream>

class Field{
private:
    int rows, cols;
    Cell** p_field;
    int* p_minePos;
    int mineNumber;
    static Player* p_highscores; // static variable
public:
    Field();
    ~Field();

    void setMinePos();
    void printField() const;
    void minePosSort();
    bool openCell(Eingabe);
    int  aroundMineCount(Eingabe) const;
    void explodieren();
    void placeMine();
    void setSize(); // Set size of field
    bool winCondition() const;
    void menu();
    void spielen();
    void einleitung();
    void highscores();
    void set_Highscore(const Player&);
    void print_highscores() const;
    void save_Highscores() const;
    void load_Highscores() const;// nimm die gespeicherten Highscores aus gespeichertem Platz
};

#endif // FIELD_H
