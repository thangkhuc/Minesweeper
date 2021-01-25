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
    Eingabe(int, int, bool, bool);
    ~Eingabe();

    void typUmwandlung(string);
    void eingeben(int, int);

    int  getRow() const;
    int  getColum() const;
    bool getMarkieren() const;
    bool getMarkeRemove() const;
};

#endif // EINGABE_H
