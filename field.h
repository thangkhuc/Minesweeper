#ifndef FIELD_H
#define FIELD_H
#include "Cell.h"
#include <random>
#include "Eingabe.h"
#include "Player.h"
#include <fstream>

class Field{
protected:
    int rows, cols;
    Cell** p_field;
    vector<int> minePos;
    int mineNumber;
public:
    Field();
    ~Field();

    void setMinePos();
    void printField() const;
    void minePosSort();
    bool openCell(Eingabe);
    int  aroundMineCount(Eingabe) const;
    void explode();
    void placeMine();
    void setSize(); // Set size of field
    bool winCondition() const;
};

#endif // FIELD_H
