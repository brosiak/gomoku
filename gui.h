#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QPainter>
#include <iostream>
#include <AppConstants.h>
using namespace appConstants;
class Board;


class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(Board *board, QWidget *parent = nullptr);
    ~Gui();


private:
    virtual void paintEvent(QPaintEvent *event)override;
    void initWindow();
    void drawBoard();
    void drawBall(const int x, const int y);
    void drawBalls();
    Board *board;




};
#endif // GUI_H
