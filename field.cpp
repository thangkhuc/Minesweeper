#include "Field.h"

Field :: Field(){
    Field :: setSize();

    p_field = new Cell*[rows]; // Spielfeld initialisieren
    for (int i = 0; i < cols ; ++i )
        p_field[i] = new Cell[cols];

    p_minePos = new int[mineNumber];// minen initialisieren
    Field :: setMinePos(); //minewerte definieren
    Field :: placeMine();
}

void Field :: placeMine(){
    int mineCout = 0;

    for (int row = 0; row < rows ; ++row ) {
        for (int col = 0; col < cols ; ++col ) {
            if (row * rows + col == p_minePos[mineCout]) {
                p_field[row][col].istMine = true;
                ++mineCout;
            }
            else
                p_field[row][col].istMine = false;
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
    if (p_field[eingabe.row][eingabe.col].istGeoeffnet == true)// false wenn das Cell schon geoeffnet ist
        return false;

    if (eingabe.markieren == true) {
        p_field[eingabe.row][eingabe.col].istMarkiert = true;
        return false;
    }
    else if (eingabe.markeRemove == true){
        p_field[eingabe.row][eingabe.col].istMarkiert = false;
        return false;
    }
    else {
        p_field[eingabe.row][eingabe.col].istGeoeffnet = true;

        if (p_field[eingabe.row][eingabe.col].istMine == true) { // return true wenn das Cell ein Bombe ist
            Field :: explodieren();
            return true;
        }
        else {
            p_field[eingabe.row][eingabe.col].nebeneMine = Field :: aroundMineCount(eingabe);

            if (p_field[eingabe.row][eingabe.col].nebeneMine == 0) {//Wenn es keine Mine neben gibt, dann oeffnet 8 nebene Cells
                int row1 = eingabe.row == 0 ? 0 : -1;
                int col1 = eingabe.col == 0 ? 0 : -1;
                int row2 = eingabe.row == rows - 1 ? 0 : 1;
                int col2 = eingabe.col == cols - 1 ? 0 : 1;

                for (int r = row1; r <= row2 ; ++r ) {
                    for (int c = col1; c <= col2 ; ++c ) {
                        Eingabe eingabe1(eingabe.row + r, eingabe.col + c, false, false);
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
    int row1 = eingabe.row == 0 ? 0 : -1; // wenn das Cell an der obenen Grenze ist, ist row1 0
    int col1 = eingabe.col == 0 ? 0 : -1; // wenn das Cell an der rechtenen Grenze ist, ist col1 0
    int row2 = eingabe.row == rows - 1 ? 0 : 1; // wenn das Cell an der untenen Grenze ist, ist row2 0
    int col2 = eingabe.col == cols - 1 ? 0 : 1; // wenn das Cell an der linken Grenze ist, ist col2 0

    for (int r = row1; r <= row2 ; ++r ) { // gehen durch 8 nebenen Cells durch
        for (int c = col1; c <= col2 ; ++c ) {
            if (p_field[eingabe.row + r][eingabe.col + c].istMine == true)
                ++count;
        }
    }
    return count;
}

void Field :: explodieren(){
    for (int i = 0; i < mineNumber ; ++i )
        p_field[p_minePos[i] / rows][p_minePos[i] % cols].istGeoeffnet = true;
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
            if (p_field[row][col].istMarkiert == true)
                cout << "p";
            else if (p_field[row][col].istGeoeffnet == false)
                cout << "*";
            else {
                if (p_field[row][col].istMine == true)
                    cout << "0";                
                else if (p_field[row][col].nebeneMine == 0)
                    cout << "_";
                else
                    cout << p_field[row][col].nebeneMine;
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
            if (p_field[i][j].istGeoeffnet == false)
                ++count;
        }
    }

    if (count == mineNumber)
        return true;
    else
        return false;
}

Field :: ~Field(){}
