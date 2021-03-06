#include "Eingabe.h"

Eingabe :: Eingabe()
{   
    row = 0;
    col = 0;
    markieren = false;
    markeRemove = false;
}

Eingabe :: Eingabe(int row, int col, bool markieren, bool markeRemove)
{
    this->row = row;
    this->col = col;
    this->markieren = markieren;
    this->markeRemove = markeRemove;
}

Eingabe :: ~Eingabe(){}

void Eingabe :: typUmwandlung(string eingabe)
{
    unsigned int pos = 0;

    for (int i = 0; i < 2 ; ++i) {
        while (pos < eingabe.length() && !isdigit(eingabe.at(pos))){
            if (eingabe.at(pos) == ' M')
                markieren = true;
            else if (eingabe.at(pos) == 'R')
                markeRemove = true;
            pos++;
        }

        int betrag = 0;
        while (pos < eingabe.length() && isdigit(eingabe.at(pos))){
            betrag = betrag * 10 + eingabe.at(pos) - '0';
            pos++;
        }

        if (i == 0)
            row = betrag;
        else
            col = betrag;
    }
}

void Eingabe :: eingeben(int rows, int cols){
    string a;
    while (true) {
        cout << "Geben Sie ein Feld in solcher Form ein: (Option) (row-number) (colum-number) " << endl;
        fflush(stdin);
        getline(cin, a);

        typUmwandlung(a);
        if (row <= rows && col <= cols && row != 0 && col != 0) {
            --row;
            --col;
            break;
        }
        cout << "ungueltige Eingabe" << endl;

    }
}

int  Eingabe :: getRow() const {return row;}

int  Eingabe :: getColum() const {return col;}

bool Eingabe :: getMarkieren() const {return markieren;}

bool Eingabe :: getMarkeRemove() const {return markeRemove;}
