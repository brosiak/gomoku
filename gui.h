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


private:
    virtual void paintEvent(QPaintEvent *event)override;
    void initWindow();
    void drawBoard();
    void drawBall(const int x, const int y);
    void drawBalls();
    int getCellValue(int x, int y);
    int getCellValue(std::pair<int, int> coords);
    bool checkIfExceeds(QPoint point);
    void changePlayer();
    std::pair<int, int> getCoords(QPoint point);
    bool isClicked;
    Board board;
    int actualPlayer;
    static constexpr int border = 6;
    static constexpr int dimension = 15;
    static constexpr int cellSizePx = 64;
    static constexpr int menuPx = 250;
    static constexpr int boardSizePx = dimension * cellSizePx;
    static constexpr int firstPlayer = 1;
    static constexpr int secondPlayer = 2;
    static constexpr int emptyCell = 0;
    QPoint last_point;
    void mousePressEvent(QMouseEvent *event)override;


};
#endif // GUI_H
