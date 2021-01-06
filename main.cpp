#include "field.h"
#include "Eingabe.h"

Spieler* p_highscores = new Spieler[10];

int main() {
    Field field1;
    load_Highscores();

    field1.menu();

    return 0;
}
