#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QPainter>
#include "board.h"
#include <iostream>



class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(QWidget *parent = nullptr);
    ~Gui();
    virtual void paintEvent(QPaintEvent *event)override;
    void printBoard();
    void initBoard(QPainter *painter);
    void drawBalls(QPainter *painter);
    int getCellValue(int x, int y);
    int getCellValue(std::pair<int, int> coords);
    std::pair<int, int> getCoords(QPoint point);
    bool isClicked;
    Board *board;

private:
    static constexpr int border = 6;
    static constexpr int dimension = 15;
    static constexpr int cellSizePx = 64;
    static constexpr int boardSizePx = dimension * cellSizePx;
    QPoint last_point;
    void mousePressEvent(QMouseEvent *event)override;


};
#endif // GUI_H
