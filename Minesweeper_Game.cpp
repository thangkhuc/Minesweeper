#include "Minesweeper_Game.h"

MinesweeperGame* MinesweeperGame :: games = new MinesweeperGame[10];

MinesweeperGame::MinesweeperGame(){}

void MinesweeperGame::add_game()
{
    for (int i = 0; i < 10 ; ++i ) {
        if (player.score > games[i].player.score) { //seek the right position and put in it
            for (int j = 9; j > i ; --j)
                games[j] = games[j - 1];
            games[i] = *this;
            break;
        }
    }
}

void MinesweeperGame::save_game() const // save all attributes of the game
{
    ofstream game_save("C:/Users/DELL 7480/Documents/Minesweeper/save_game.txt");
    for (int i = 0; i < 10 ; ++i ) {
        game_save << games[i].player.name << "\n";
        game_save << games[i].player.score << "\n";
        game_save << games[i].zug << "\n";
        game_save << games[i].rows << "\n";
        game_save << games[i].cols << "\n";
        game_save << games[i].mineNumber << "\n";

        for (int j = 0; j < games[i].mineNumber; j++)
            game_save << games[i].minePos[j] << " ";
        game_save << "\n";
    }
}

void MinesweeperGame::load_saveGame() //write saved values into each corresponding elements of the "games" attribute
{
    ifstream saveFile("C:/Users/DELL 7480/Documents/Minesweeper/save_game.txt");

    for (int i = 0; i < 10; i++) {
        string rows, cols, minePos, score, mineNumber;
        int rowBetrag = 0, colBetrag = 0, scoreBetrag = 0, mineBetrag = 0, mineNumberBetrag = 0;

        getline(saveFile, games[i].player.name);
        getline(saveFile, score);
        getline(saveFile, games[i].zug);
        getline(saveFile, rows);
        getline(saveFile, cols);
        getline(saveFile, mineNumber);
        getline(saveFile, minePos);

        for (unsigned i = 0; i < score.size(); i++)
            scoreBetrag = scoreBetrag * 10 + score.at(i) - '0';
        games[i].player.score = scoreBetrag;

        for (int i = 0; i < 2 ;i++ ) {
            rowBetrag = rowBetrag * 10 + rows.at(i) - '0';
            colBetrag = colBetrag * 10 + cols.at(i) - '0';
        }
        games[i].rows = rowBetrag;
        games[i].cols = colBetrag;

        for (unsigned j = 0; j < mineNumber.size(); j++)
            mineNumberBetrag = mineNumberBetrag * 10 + mineNumber.at(j) - '0' ;
        games[i].mineNumber = mineNumberBetrag;

        for (unsigned j = 0; j < minePos.size(); j++) {
            if (isdigit(minePos.at(j)))
                mineBetrag = mineBetrag * 10 + minePos.at(j) - '0';
            else {
                games[i].minePos.push_back(mineBetrag);
                mineBetrag = 0;
            }
        }
    }
}

void MinesweeperGame::print_highscores() const
{
    cout << "\t\t--------------" << endl;
    cout << "\t\t| HIGHSCORES |" << endl;
    cout << "\t\t--------------" << endl;
    cout.width(10);
    cout << right << "PLAYER\t\t\t\t\t" << right << "SCORE\t\t\t" << "Zuege" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    for (int i = 0; i < 10 ; ++i ) {
        cout.width(20);
        cout << left << games[i].player.name << "\t\t\t" << right << games[i].player.score;
        cout << "\t\t\t" << games[i].zug << endl;
    }
}

bool MinesweeperGame::menu() // return true to stop the game
{
    int eingabe;
    cout << "\t\t------------------------------" << endl;
    cout << "\t\t| Willkommen bei Minesweeper |" << endl;
    cout << "\t\t------------------------------" << endl;
    cout << "(1) Spielen\n(2) Einleitung\n(3) Highscores\n(4) Demo\n(5) Beenden" << endl;

    cin >> eingabe;
    while (eingabe <= 0 || eingabe > 5) {
        cout << "ungueltige Eingabe!" << endl;
        cin >> eingabe;
    }

    switch (eingabe) {
    case 1: {play(); return false;}
    case 2: return tutorial();
    case 3: return highscores();
    case 4: return demo();
    case 5: return true;
    }
}

void MinesweeperGame::play()
{
    setSize();
    printField();
    bool gameOver = false;

    while (true) {
        Eingabe eingabe;
        eingabe.eingeben(rows, cols);

        gameOver = openCell(eingabe);
        printField();
        set_zug(eingabe); //save each move into "zug"

        if (gameOver == true) {
            cout << "Sie haben verloren!" << endl;
            cout << "Ihre Score: " << player.score << endl;
            player.set_name();
            add_game();
            break;
        }
        player.score++;

        if (winCondition() == true) {
            cout << "Sie haben gewonnen" << endl;
            player.set_name();
            add_game();
            break;
        }
    }
    save_game();
}

bool MinesweeperGame::tutorial()
{
    int eingabe;
    cout << "\t\t--------------" << endl;
    cout << "\t\t| EINLEITUNG |" << endl;
    cout << "\t\t--------------" << endl;
    cout << "-Das Spiel ist normalerweise beendet, wenn eine Mine aufgedeckt wird.\n"
        "-Das Spiel wird fortgesetzt, wenn Sie ein leeres Feld aufdecken.\n"
        "-Wird beim Aufdecken eines Feldes eine Zahl angezeigt, steht diese fuer die Anzahl der Minen, die in den benachbarten 8 Feldern verborgen sind.\n"
        "-Anhand dieser Angabe kann abgeleitet werden, unter welchen der angrenzenden Feldern sich Minen befinden und auf welche Felder gefahrlos geklickt werden kann.\n\n" << endl;
    cout << "(1) Menu\t(2) Spielen\t(3) Beenden" << endl;

    cin >> eingabe;
    while (eingabe != 1 && eingabe != 2 && eingabe != 3) {
        cout << "ungueltige Eingabe" << endl;
        cin >> eingabe;
    }

    switch (eingabe) {
    case 1: {return menu();}
    case 2: {play(); return false;}
    case 3: return true;
    }
}

bool MinesweeperGame::highscores()
{
    int eingabe;
    print_highscores();
    cout << "(1) Spielen\t(2) Menu\t(3) Beenden" << endl;
    cin >> eingabe;
    while (eingabe != 1 && eingabe != 2 && eingabe != 3) {
        cout << "ungueltige Eingabe" << endl;
        cin >> eingabe;
    }
    switch (eingabe) {
    case 1: {play(); return false;}
    case 2:	return menu();
    case 3: return true;
    }
}

bool MinesweeperGame::demo() //replicate play() funcion with the saved moves of the best game
{
    bool gameOver = false;

    games[0].p_field = new Cell*[games[0].rows]; // Spielfeld initialisieren
    for (int i = 0; i < games[0].cols ; ++i )
        games[0].p_field[i] = new Cell[games[0].cols];
    games[0].placeMine();

    int i = 0;
    while (true) {
        Eingabe eingabe;
        string subString = "";

        while (games[0].zug.at(i) != '-') {
            subString +=  games[0].zug.at(i);
            i++;
        }
        i++;

        eingabe.typUmwandlung(subString);

        cout << "Eingabe: ";
        sleep(1);
        if (eingabe.getMarkieren())
            cout <<	"M ";
        else if (eingabe.getMarkeRemove())
            cout << "R ";
        sleep(1);
        cout <<	eingabe.getRow() + 1 << " ";
        sleep(1);
        cout <<	eingabe.getColum() + 1 << endl;
        sleep(1);

        gameOver = games[0].openCell(eingabe);
        games[0].printField();
        sleep(2);

        if (gameOver == true) {
            cout << "Game Over!" << endl;
            break;
        }

        if (winCondition() == true) {
            cout << "You win!" << endl;
            break;
        }
    }
    return false;
}

void MinesweeperGame::set_zug(const Eingabe& eingabe)
{
    if (eingabe.getMarkieren())
        this->zug += 'M';
    if (eingabe.getMarkeRemove())
        this->zug += 'R';

    this->zug += 'r'; // r steht fuer row
    this->zug += (eingabe.getRow() / 10 + '0');
    this->zug += (eingabe.getRow() % 10 + '0');

    this->zug +=  'c'; // c steht fuer colum
    this->zug += (eingabe.getColum() / 10 + '0');
    this->zug += (eingabe.getColum() % 10 + '0');

    this->zug += '-';
}
