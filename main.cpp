#include "minesweeper.h"
#include "Eingabe.h"

Spieler* p_highscores = new Spieler[10];

int main() {
    bool gameOver = 0;
    load_Highscores();

    while (menu()) {
        Spieler spieler;
        Field field;
        field.printField();

        while (true) {
            Eingabe eingabe;
            eingabe.eingeben(field.rows, field.cols);
            gameOver = field.openCell(eingabe);
            field.printField();

            if (gameOver == true) {
                cout << "Sie haben verloren!" << endl;
                cout << "Ihre Score: " << spieler.score << endl;
                spieler.set_Spieler();
                set_Highscore(spieler);
                break;
            }
            spieler.score++;

            if (field.winCondition() == true) {
                cout << "Sie haben gewonnen" << endl;
                spieler.set_Spieler();
                set_Highscore(spieler);
                break;
            }
        }
    }
    save_Highscores();


    return 0;
}
