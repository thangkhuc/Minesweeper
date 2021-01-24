#include "Player.h"

Player::Player()
{
    name = "_";
    score = 0;
}

Player :: Player(const Player& spieler) // kopierkonstruktur
    : name(spieler.name), score(spieler.score){}

void Player :: set_name()
{
    cout << "Geben Sie Ihre Name ein: " << endl;
    fflush(stdin);
    getline(cin, name);
}

Player :: ~Player(){}
