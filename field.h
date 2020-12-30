#ifndef FIELD_H
#define FIELD_H
#include "Cell.h"
#include <random>
#include "Eingabe.h"

class Field{
public:
    int rows, cols;
    Cell** p_field;
    int* p_minePos;
    int mineNumber;

    Field();
    ~Field();

    void setMinePos();
    void printField();
    void minePosSort();
    bool openCell(Eingabe eingabe);
    int aroundMineCount(Eingabe eingabe);
    void explodieren();
    void placeMine();
    void setSize();
    bool winCondition();

};


#endif // FIELD_H
