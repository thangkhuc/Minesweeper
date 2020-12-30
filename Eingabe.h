#ifndef EINGABE_H
#define EINGABE_H
#include <iostream>
using namespace std;

class Eingabe
{
public:
    int row;
    int col;
    bool markieren;
    bool markeRemove;

    Eingabe();
    Eingabe(int _row, int _col, bool _markieren, bool markeRemove);
    ~Eingabe();

    void typUmwandlung(string eingabe);
    void eingeben(int rows, int cols);
};

#endif // EINGABE_H
