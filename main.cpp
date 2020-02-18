#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui gui;
    gui.showMaximized();
    return a.exec();
}
