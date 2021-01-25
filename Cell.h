#ifndef CELL_H
#define CELL_H
#include <iostream>
using namespace std;

class Cell{
private:
    bool istMine;
    bool istGeoeffnet;
    int  nebeneMine;
    bool istMarkiert;
public:
    Cell();
    ~Cell();

    void setIstMine(bool);
    void setIstGeoeffnet(bool);
    void setIstMarkiert(bool);
    void setNebeneMine(int);
    bool getIstMine() const;
    bool getIstGeoeffnet() const;
    bool getIstMarkiert() const;
    int  getNebeneMine() const;

};

#endif // CELL_H
