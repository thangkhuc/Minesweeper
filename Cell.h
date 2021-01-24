#ifndef CELL_H
#define CELL_H
#include <iostream>
using namespace std;

class Cell{
private:
    bool istMine;
    bool istGeoeffnet;
    int nebeneMine;
    bool istMarkiert;
public:
    Cell();
    ~Cell();

    bool getIstMine() const;
    bool getIstGeoeffnet() const;
    bool getIstMarkiert() const;
    int  getNebeneMine() const;
    void setIstMine(bool);
    void setIstGeoeffnet(bool);
    void setIstMarkiert(bool);
    void setNebeneMine(int);

};

#endif // CELL_H
