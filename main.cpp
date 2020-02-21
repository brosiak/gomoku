#include "game.h"
#include "gui.h"
#include "board.h"
#include <QApplication>
#include "AppConstants.h"
using namespace appConstants;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Board *board = new Board(dimension);
    Game game(board);
    Gui gui(board);
    gui.showMaximized();
    return a.exec();
}
