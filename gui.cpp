#include "gui.h"
#include "board.h"
#include <QMouseEvent>
#include <QDebug>
#include <utility>
#include <QMessageBox>
#include <QApplication>
Gui::Gui(Board *board_ref,QWidget *parent )
    : QMainWindow(parent),
      board(board_ref)
{
    initWindow();
}

Gui::~Gui()
{
}

void Gui::initWindow()
{
    setMaximumWidth(boardSizePx + menuPx);
    setMaximumHeight(boardSizePx);
    setMinimumWidth(boardSizePx + menuPx);
    setMinimumHeight(boardSizePx);
}

void Gui::drawBoard()
{
    QPainter painter(this);
    painter.setWindow(0, 0, boardSizePx + menuPx, boardSizePx);
    for(int x=0; x<dimension;x++)
    {
        for(int y=0; y<dimension;y++)
        {
            painter.drawRect(x*cellSizePx, y*cellSizePx, cellSizePx, cellSizePx);
        }
    }
}




void Gui::drawBall(const int x, const int y)
{
    QPainter painter(this);
    if(board->getCellValue(x,y) == firstPlayer)
    {
        painter.setBrush(Qt::red);
    }
    else if(board->getCellValue(x,y) == secondPlayer)
    {
        painter.setBrush(Qt::blue);
    }
    painter.drawEllipse(y*cellSizePx + border/2, x*cellSizePx + border/2,
                         cellSizePx - border, cellSizePx - border);
}

void Gui::drawBalls()
{
    for(int x=0; x<dimension; x++)
    {
        for(int y=0; y<dimension;y++)
        {
            if (board->getCellValue(x,y) == emptyCell)
            {
                continue;
            }
            else
            {
                drawBall(x, y);
            }
        }
    }
}



void Gui::paintEvent(QPaintEvent *event)
{
    drawBoard();
    drawBalls();
}




