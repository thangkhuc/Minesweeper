#include "Eingabe.h"

Eingabe :: Eingabe()
{   
    row = 0;
    col = 0;
    markieren = false;
    markeRemove = false;
}

Eingabe :: Eingabe(int _row, int _col, bool _markieren, bool _markeRemove)
{
    row = _row;
    col = _col;
    markieren = _markieren;
    markeRemove = _markeRemove;
}

void Eingabe :: typUmwandlung(string eingabe) //Typumwandlungkonstruktor
{
    unsigned int pos = 0;

    for (int i = 0; i < 2 ; ++i) {
        while (pos < eingabe.length() && !isdigit(eingabe.at(pos))){
            
            if (eingabe.at(pos) == 'm')
                markieren = true;
            else if (eingabe.at(pos) == 'r')
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
        Eingabe :: typUmwandlung(a);
        if (row <= rows && col <= cols && row != 0 && col != 0) {
            --row;
            --col;
            break;
        }
        cout << "ungueltige Eingabe" << endl;

    }
}
Eingabe :: ~Eingabe(){}
