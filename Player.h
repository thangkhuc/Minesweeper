#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
using namespace std;

class Player
{
public:
    string name;
    int score;

    Player();
    Player(const Player& spieler);
    ~Player();
    void set_name();

};

#endif // PLAYER_H
