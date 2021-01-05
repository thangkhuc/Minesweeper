#include "spieler.h"

Spieler::Spieler()
{
    name = "_";
    score = 0;
}

Spieler :: Spieler(const Spieler& spieler) // kopierkonstruktur
    : name(spieler.name), score(spieler.score){}

void Spieler :: set_Spieler()
{
    cout << "Geben Sie Ihre Name ein: " << endl;
    fflush(stdin);
    getline(cin, name);
}

Spieler :: ~Spieler(){}
