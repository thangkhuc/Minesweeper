#include "minesweeper.h"

bool menu() // true fuer spielen, flase fuer beenden
{
    int eingabe;
    cout << "\t\t------------------------------" << endl;
    cout << "\t\t| Willkommen bei Minesweeper |" << endl;
    cout << "\t\t------------------------------" << endl;
    cout << "(1) Spielen\t(2) Einleitung\t(3) Highscores\t(4) Beenden" << endl;

    cin >> eingabe;
    while (eingabe <= 0 || eingabe > 4) {
        cout << "ungueltige Eingabe!" << endl;
        cin >> eingabe;
    }

    switch (eingabe) {
    case 1: return true;
    case 2: return einleitung();
    case 3: return highscores();
    case 4: return false;
    }
}

bool einleitung()
{
    int eingabe;
    cout << "\t\t--------------" << endl;
    cout << "\t\t| EINLEITUNG |" << endl;
    cout << "\t\t--------------" << endl;
    cout << "-Das Spiel ist normalerweise beendet, wenn eine Mine aufgedeckt wird.\n"
        "-Das Spiel wird fortgesetzt, wenn Sie ein leeres Feld aufdecken.\n"
        "-Wird beim Aufdecken eines Feldes eine Zahl angezeigt, steht diese fuer die Anzahl der Minen, die in den benachbarten 8 Feldern verborgen sind.\n"
        "-Anhand dieser Angabe kann abgeleitet werden, unter welchen der angrenzenden Feldern sich Minen befinden und auf welche Felder gefahrlos geklickt werden kann.\n\n" << endl;
    cout << "(1) Spielen\t(2) Menu\t(3) Beenden" << endl;

    cin >> eingabe;
    while (eingabe != 1 && eingabe != 2 && eingabe != 3) {
        cout << "ungueltige Eingabe" << endl;
        cin >> eingabe;
    }

    if (eingabe == 1)
        return true;
    else if (eingabe == 3)
        return false;
    else
        return menu();
}

bool highscores()
{
    int eingabe;
    highscores_ausgeben();
    cout << "(1) Spielen\t(2) Menu\t(3) Beenden" << endl;
    cin >> eingabe;
    while (eingabe != 1 && eingabe != 2 && eingabe != 3) {
        cout << "ungueltige Eingabe" << endl;
        cin >> eingabe;
    }

    if (eingabe == 1)
        return true;
    else if (eingabe == 3)
        return false;
    else
        return menu();
}

void set_Highscore(Spieler spieler)
{
    // schreibt das Score in der Highscore Tabelle ein
    for (int i = 0; i < 10 ; ++i ) {
        if (spieler.score > p_highscores[i].score) {
            for (int j = 9; j > i ; --j)
                p_highscores[j] = p_highscores[j - 1];
            p_highscores[i] = spieler;
            break;
        }
    }

}
void save_Highscores()
{
    ofstream highscores_Save("C:/Users/DELL 7480/Documents/Minesweeper/highscores_Save.txt");
    for (int i = 0; i < 10 ; ++i ) {
        highscores_Save << p_highscores[i].name << "\n";
        highscores_Save << p_highscores[i].score << "\n";
    }
}

void load_Highscores()
{
    ifstream highscores_Save("C:/Users/DELL 7480/Documents/Minesweeper/highscores_Save.txt");
    string score;

    for(int i = 0; i < 10; i++) {
        getline(highscores_Save, p_highscores[i].name);
        getline(highscores_Save, score);

        int betrag = 0;
        for (unsigned int j = 0; j < score.length() ; ++j ) {
            betrag = betrag * 10 + score.at(j) - '0';
        }
        p_highscores[i].score = betrag;

    }
}

void highscores_ausgeben(){
    cout << "\t\t--------------" << endl;
    cout << "\t\t| HIGHSCORES |" << endl;
    cout << "\t\t--------------" << endl;
    cout.width(10);
    cout << right << "SPIELER\t\t\t\t\t" << right << "SCORE" << endl;
    for (int i = 0; i < 10 ; ++i ) {
        cout.width(20);
        cout << left << p_highscores[i].name << "\t\t\t" << right << p_highscores[i].score << endl;
    }
}

