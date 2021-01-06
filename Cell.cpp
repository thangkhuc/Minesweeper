#include "Cell.h"

Cell :: Cell(){
    istMine = false;
    istGeoeffnet = false;
    nebeneMine = 0;
    istMarkiert = false;
}
Cell :: ~Cell(){}

bool Cell :: getIstMine()
{
    return istMine;
}

void Cell :: setIstMine(bool set)
{
    istMine = set;
}

void Cell :: setIstGeoeffnet(bool set)
{
    istGeoeffnet = set;
}

void Cell :: setIstMarkiert(bool set)
{
    istMarkiert = set;
}

void Cell :: setNebeneMine(int set)
{
    nebeneMine = set;
}

bool Cell :: getIstMarkiert()
{
    return istMarkiert;
}

int Cell :: getNebeneMine()
{
    return nebeneMine;
}

bool Cell :: getIstGeoeffnet()
{
    return istGeoeffnet;
}
