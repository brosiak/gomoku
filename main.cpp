#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui gui;
    gui.showMaximized();
    gui.showFullScreen();
    gui.initWindow();
    return a.exec();
}
