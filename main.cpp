#include "field.h"
#include "time.h"

int main() {
    srand(time(0));

    Field field1;
    field1.load_Highscores();

    field1.menu();

    return 0;
}
