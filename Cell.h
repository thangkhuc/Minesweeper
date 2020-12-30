#ifndef CELL_H
#define CELL_H
#include <iostream>
using namespace std;

class Cell{
public:
    Cell();
    ~Cell();

    bool istMine;
    bool istGeoeffnet;
    int nebeneMine;
    bool istMarkiert;

};

#endif // CELL_H
