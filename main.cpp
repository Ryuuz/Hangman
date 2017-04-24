#include <QApplication>
#include <ctime>
#include "game.h"

//A hangman game made by Camilla Merete Odegaard using Qt

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(nullptr));
    Game *game;

    game = new Game();
    game->show();
    game->start_menu();

    return a.exec();
}
