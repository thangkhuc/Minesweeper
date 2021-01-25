#include "Cell.h"

Cell :: Cell(){
    istMine = false;
    istGeoeffnet = false;
    nebeneMine = 0;
    istMarkiert = false;
}

Cell :: ~Cell(){}

void Cell :: setIstMine(bool set) {istMine = set;}

void Cell :: setIstGeoeffnet(bool set) {istGeoeffnet = set;}

void Cell :: setIstMarkiert(bool set) {istMarkiert = set;}

void Cell :: setNebeneMine(int set) {nebeneMine = set;}

bool Cell :: getIstMarkiert() const {return istMarkiert;}

int  Cell :: getNebeneMine() const {return nebeneMine;}

bool Cell :: getIstGeoeffnet() const {return istGeoeffnet;}

bool Cell :: getIstMine() const {return istMine;}
