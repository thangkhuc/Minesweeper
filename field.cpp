#include "Field.h"

Field :: Field(){}

void Field :: placeMine(){
    int mineCout = 0;

    for (int row = 0; row < rows ; ++row ) {
        for (int col = 0; col < cols ; ++col ) {
            if (row * rows + col == p_minePos[mineCout]) {
                p_field[row][col].setIstMine(true);
                ++mineCout;
            }
            else
                p_field[row][col].setIstMine(false);
        }
    }
}

void Field :: setSize()
{
    cout << "Waehlen Sie die Schwierigkeit aus:\n(1) 10x10 mit 10 Minen"
            "\t(2) 20x20 mit 50 Minen\t(3) 30x30 mit 100 Mine" << endl;
    int eingabe;
    cin >> eingabe;
    while (eingabe != 1 && eingabe != 2 && eingabe != 3) {
        cout << "ungueltige Eingabe" << endl;
        cin >> eingabe;
    }

        if (eingabe == 1) {
            rows = 10;
            cols = 10;
            mineNumber = 10;
        }
        else if (eingabe == 2) {
            rows = 20;
            cols = 20;
            mineNumber = 50;
        }
        else {
            rows = 30;
            cols = 30;
            mineNumber = 100;
        }

    p_field = new Cell*[rows]; // Spielfeld initialisieren
    for (int i = 0; i < cols ; ++i )
        p_field[i] = new Cell[cols];

    p_minePos = new int[mineNumber];// minen initialisieren
    Field :: setMinePos(); //minewerte definieren
    Field :: placeMine();
}

void Field :: setMinePos(){
    bool check;

    for (int i = 0; i < mineNumber ; ++i ) {
        do{
            check = false;
            p_minePos[i] = rand() % (rows * cols);
            for (int j = 0; j < i ; ++j ) {
                if (p_minePos[i] == p_minePos[j])// check ob es den Zufallswert schon im Array gibt
                    check = true;
            }
        }while (check == true);
    }
    Field :: minePosSort();
}

void Field :: minePosSort() {
    int temp;
    for (int i = 0; i < mineNumber ; ++i) {
        for (int j = i + 1; j < mineNumber ; ++j ) {
            if (p_minePos[i] > p_minePos[j]) {
                temp = p_minePos[i];
                p_minePos[i] = p_minePos[j];
                p_minePos[j] = temp;
            }
        }
    }
}

bool Field :: openCell(Eingabe eingabe){
    if (p_field[eingabe.getRow()][eingabe.getColum()].getIstGeoeffnet() == true)// false wenn das Cell schon geoeffnet ist
        return false;

    if (eingabe.getMarkieren() == true) {
        p_field[eingabe.getRow()][eingabe.getColum()].setIstMarkiert(true);
        return false;
    }
    else if (eingabe.getMarkeRemove() == true){
        p_field[eingabe.getRow()][eingabe.getColum()].setIstMarkiert(false);
        return false;
    }
    else {
        p_field[eingabe.getRow()][eingabe.getColum()].setIstGeoeffnet(true);

        if (p_field[eingabe.getRow()][eingabe.getColum()].getIstMine() == true) { // return true wenn das Cell ein Bombe ist
            Field :: explodieren();
            return true;
        }
        else {
            p_field[eingabe.getRow()][eingabe.getColum()].setNebeneMine(Field :: aroundMineCount(eingabe));

            if (p_field[eingabe.getRow()][eingabe.getColum()].getNebeneMine() == 0) {//Wenn es keine Mine neben gibt, dann oeffnet 8 nebene Cells
                int row1 = eingabe.getRow() == 0 ? 0 : -1;
                int col1 = eingabe.getColum() == 0 ? 0 : -1;
                int row2 = eingabe.getRow() == rows - 1 ? 0 : 1;
                int col2 = eingabe.getColum() == cols - 1 ? 0 : 1;

                for (int r = row1; r <= row2 ; ++r ) {
                    for (int c = col1; c <= col2 ; ++c ) {
                        Eingabe eingabe1(eingabe.getRow() + r, eingabe.getColum() + c, false, false);
                        Field :: openCell(eingabe1);
                    }
                }
                return false;
            }
            return false;
        }
    }
}

int Field :: aroundMineCount(Eingabe eingabe){
    int count = 0;
    int row1 = eingabe.getRow() == 0 ? 0 : -1; // wenn das Cell an der obenen Grenze ist, ist row1 0
    int col1 = eingabe.getColum() == 0 ? 0 : -1; // wenn das Cell an der rechtenen Grenze ist, ist col1 0
    int row2 = eingabe.getRow() == rows - 1 ? 0 : 1; // wenn das Cell an der untenen Grenze ist, ist row2 0
    int col2 = eingabe.getColum() == cols - 1 ? 0 : 1; // wenn das Cell an der linken Grenze ist, ist col2 0

    for (int r = row1; r <= row2 ; ++r ) { // gehen durch 8 nebenen Cells durch
        for (int c = col1; c <= col2 ; ++c ) {
            if (p_field[eingabe.getRow() + r][eingabe.getColum() + c].getIstMine() == true)
                ++count;
        }
    }
    return count;
}

void Field :: explodieren(){
    for (int i = 0; i < mineNumber ; ++i )
        p_field[p_minePos[i] / rows][p_minePos[i] % cols].setIstGeoeffnet(true);
}


void Field :: printField(){
    cout << " " ;
    for (int i = 0; i < cols ; ++i ) {
        cout.width(3);
        cout << right << i + 1;
    }

    cout << endl;

    for (int row = 0; row < rows ; ++row ) {
        cout.width(3);
        cout << left << row + 1;
        for (int col = 0; col < cols ; ++col ) {
            cout.width(3);
            if (p_field[row][col].getIstMarkiert() == true)
                cout << "p";
            else if (p_field[row][col].getIstGeoeffnet() == false)
                cout << "*";
            else {
                if (p_field[row][col].getIstMine() == true)
                    cout << "0";                
                else if (p_field[row][col].getNebeneMine() == 0)
                    cout << "_";
                else
                    cout << p_field[row][col].getNebeneMine();
            }

        }
        cout << endl;
    }
}

bool Field :: winCondition()
{
    int count = 0;

    for (int i = 0; i < rows ; ++i ) {
        for (int j = 0; j < cols ; ++j ) {
            if (p_field[i][j].getIstGeoeffnet() == false)
                ++count;
        }
    }

    if (count == mineNumber)
        return true;
    else
        return false;
}

Field :: ~Field(){
    delete p_minePos;
    for (int i = 0; i < rows ;i++ )
        delete[] p_field[i];
    delete p_field;

}

void Field :: menu() // true fuer spielen, flase fuer beenden
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
    case 1: {spielen(); menu(); return;}
    case 2: {einleitung(); return;}
    case 3: {highscores(); return;}
    case 4: break;
    }
}

void Field :: spielen()
{
    Spieler spieler;
    setSize();
    printField();
    bool gameOver = false;

    while (true) {
        Eingabe eingabe;
        eingabe.eingeben(rows, cols);
        gameOver = openCell(eingabe);
        printField();

        if (gameOver == true) {
        cout << "Sie haben verloren!" << endl;
        cout << "Ihre Score: " << spieler.score << endl;
        spieler.set_Spieler();
        set_Highscore(spieler);
        break;
        }
        spieler.score++;

        if (winCondition() == true) {
        cout << "Sie haben gewonnen" << endl;
        spieler.set_Spieler();
        set_Highscore(spieler);
        break;
        }
    }

    save_Highscores();
}

void Field :: einleitung()
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

    switch (eingabe) {
    case 1: {spielen(); menu(); return;}
    case 2: {menu(); return;}
    case 3: break;
    }
}

void Field :: highscores()
{
    int eingabe;
    highscores_ausgeben();
    cout << "(1) Spielen\t(2) Menu\t(3) Beenden" << endl;
    cin >> eingabe;
    while (eingabe != 1 && eingabe != 2 && eingabe != 3) {
        cout << "ungueltige Eingabe" << endl;
        cin >> eingabe;
    }
    switch (eingabe) {
    case 1: {spielen(); menu(); return;}
    case 2:	{menu(); return;}
    case 3: break;
    }
}

void Field :: set_Highscore(Spieler spieler)
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
void Field :: save_Highscores()
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

void Field :: highscores_ausgeben(){
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
