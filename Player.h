#ifndef SPIELER_H
#define SPIELER_H
#include <iostream>
using namespace std;

class Spieler
{
public:
    string name;
    int score;

    Spieler();
    Spieler(const Spieler& spieler);
    ~Spieler();
    void set_Spieler();

};

#endif // SPIELER_H
