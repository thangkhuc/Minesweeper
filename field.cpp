#include "field.h"

Field::Field(){}

Field::~Field(){
    for (int i = 0; i < rows ;i++ )
        delete[] p_field[i];
    delete p_field;
}

void Field::placeMine()
{
    int mineCout = 0;

    for (int row = 0; row < rows ; ++row ) {
        for (int col = 0; col < cols ; ++col ) {
            if (row * rows + col == minePos[mineCout]) {
                p_field[row][col].setIstMine(true);
                ++mineCout;
            }
            else
                p_field[row][col].setIstMine(false);
        }
    }
}

void Field::setSize()
{
    int eingabe;

    cout << "Waehlen Sie die Schwierigkeit aus:\n(1) 10x10 mit 10 Minen"
            "\t(2) 20x20 mit 50 Minen\t(3) 30x30 mit 100 Mine" << endl;
    cin >> eingabe;
    while (eingabe != 1 && eingabe != 2 && eingabe != 3) {
        cout << "ungueltige Eingabe" << endl;
        cin >> eingabe;
    }

    rows = eingabe * 10;
    cols = eingabe * 10;

    if (eingabe == 1) mineNumber = 10;
    else if (eingabe == 2) mineNumber = 50;
    else mineNumber = 100;

    // Spielfeld initialisieren
    p_field = new Cell*[rows];
    for (int i = 0; i < cols ; ++i )
        p_field[i] = new Cell[cols];

    setMinePos(); //minewerte definieren
    placeMine();
}

void Field::setMinePos()
{
    bool check;

    for (int i = 0; i < mineNumber ; ++i ) {
        do{
            check = false;
            minePos.push_back(rand() % (rows * cols));
            for (int j = 0; j < i ; ++j ) {
                if (minePos[i] == minePos[j]) {// check ob es den Zufallswert schon im Array gibt
                    check = true;
                    minePos.pop_back();
                }
            }
        }while (check == true);
    }
    minePosSort();
}

void Field::minePosSort()
{
    int temp;
    for (int i = 0; i < mineNumber ; ++i) {
        for (int j = i + 1; j < mineNumber ; ++j ) {
            if (minePos[i] > minePos[j]) {
                temp = minePos[i];
                minePos[i] = minePos[j];
                minePos[j] = temp;
            }
        }
    }
}

bool Field::openCell(Eingabe eingabe)
{
    if (p_field[eingabe.getRow()][eingabe.getColum()].getIstGeoeffnet() == true) //return false wenn das Cell schon geoeffnet ist
        return false;
    else if (eingabe.getMarkieren() == true) {
        p_field[eingabe.getRow()][eingabe.getColum()].setIstMarkiert(true);
        return false;
    }
    else if (eingabe.getMarkeRemove() == true){
        p_field[eingabe.getRow()][eingabe.getColum()].setIstMarkiert(false);
        return false;
    }
    else {
        p_field[eingabe.getRow()][eingabe.getColum()].setIstGeoeffnet(true);

        if (p_field[eingabe.getRow()][eingabe.getColum()].getIstMine() == true) { //return true wenn das Cell ein Bombe ist
            explode();
            return true;
        }
        else {
            p_field[eingabe.getRow()][eingabe.getColum()].setNebeneMine(aroundMineCount(eingabe));

            if (p_field[eingabe.getRow()][eingabe.getColum()].getNebeneMine() == 0) {//Wenn es keine Mine neben gibt, dann oeffnet 8 nebene Cells
                int row1 = eingabe.getRow() == 0 ? 0 : -1;
                int col1 = eingabe.getColum() == 0 ? 0 : -1;
                int row2 = eingabe.getRow() == rows - 1 ? 0 : 1;
                int col2 = eingabe.getColum() == cols - 1 ? 0 : 1;

                for (int r = row1; r <= row2 ; ++r ) {
                    for (int c = col1; c <= col2 ; ++c ) {
                        Eingabe eingabe1(eingabe.getRow() + r, eingabe.getColum() + c, false, false);
                        openCell(eingabe1);
                    }
                }
                return false;
            }
            return false;
        }
    }
}

int Field::aroundMineCount(Eingabe eingabe) const
{
    int count = 0;
    int row1 = eingabe.getRow() == 0 ? 0 : -1; // wenn das Cell an der obenen Grenze ist, ist row1 0
    int col1 = eingabe.getColum() == 0 ? 0 : -1; // wenn das Cell an der rechtenen Grenze ist, ist col1 0
    int row2 = eingabe.getRow() == rows - 1 ? 0 : 1; // wenn das Cell an der untenen Grenze ist, ist row2 0
    int col2 = eingabe.getColum() == cols - 1 ? 0 : 1; // wenn das Cell an der linken Grenze ist, ist col2 0

    for (int r = row1; r <= row2 ; ++r ) { // gehen durch 8 nebenen Cells
        for (int c = col1; c <= col2 ; ++c ) {
            if (p_field[eingabe.getRow() + r][eingabe.getColum() + c].getIstMine() == true)
                ++count;
        }
    }
    return count;
}

void Field::explode() // set all the cells with mine as opened
{
    for (int i = 0; i < mineNumber ; ++i )
        p_field[minePos[i] / rows][minePos[i] % cols].setIstGeoeffnet(true);
}

void Field::printField() const
{
    cout << "  " ;
    for (int i = 0; i < cols ; ++i ) {
        cout.width(3);
        cout << right << i + 1;
    }
    cout << endl;
    for (int i = 0; i < cols + 1; ++i ) {
        cout << "---" ;
    }
    cout << endl;

    for (int row = 0; row < rows ; ++row ) {
        cout.width(3);
        cout << left << row + 1 << "|";
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

bool Field::winCondition() const
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
