#include "draw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Draw w;
    w.showMaximized();
    return a.exec();
}
