#include "board.h"
#include "game.h"
#include "gui.h"
#include <QApplication>
#include "AppConstants.h"
using namespace appConstants;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Board board(dimension);
    Game game(board);
    Gui gui(board);
    gui.showMaximized();
    return a.exec();
}
