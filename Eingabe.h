#ifndef EINGABE_H
#define EINGABE_H
#include <iostream>
using namespace std;

class Eingabe
{
private:
    int row;
    int col;
    bool markieren;
    bool markeRemove;
public:
    Eingabe();
    Eingabe(int _row, int _col, bool _markieren, bool markeRemove);
    ~Eingabe();

    void typUmwandlung(string eingabe);
    void eingeben(int rows, int cols);
    int getRow();
    int getColum();
    bool getMarkieren();
    bool getMarkeRemove();
};

#endif // EINGABE_H
