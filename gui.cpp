#include "gui.h"
#include <QMouseEvent>
#include <QDebug>
#include <utility>
#include <QMessageBox>
#include <QApplication>
Gui::Gui(QWidget *parent)
    : QMainWindow(parent), board(dimension), actualPlayer(firstPlayer)
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
    this->setStyleSheet("QMainWindow {background: '#632919';}");
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



bool Gui::checkIfExceeds(QPoint point)
{
    if(point.rx() >= boardSizePx || point.ry() >= boardSizePx)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Gui::drawBall(const int x, const int y)
{
    QPainter painter(this);
    if(board.getCellValue(x,y) == firstPlayer)
    {
        painter.setBrush(Qt::black);
    }
    else if(board.getCellValue(x,y) == secondPlayer)
    {
        painter.setBrush(Qt::white);
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
            if (board.getCellValue(x,y) == emptyCell)
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

std::pair<int, int> Gui::getCoords(QPoint point)
{
    int x = point.rx();
    int y = point.ry();
    if (x % cellSizePx == 0)
    {
        x /= cellSizePx -1;
    }
    else
    {
        x = (x - x % cellSizePx) / cellSizePx;
    }
    if (y % cellSizePx == 0)
    {
        y /= cellSizePx - 1;
    }
    else
    {
        y = (y - y % cellSizePx) / cellSizePx;
    }
    return std::make_pair(y, x);
}

void Gui::changePlayer()
{
    if(actualPlayer == firstPlayer)
    {
        actualPlayer = secondPlayer;
    }
    else if(actualPlayer == secondPlayer)
    {
        actualPlayer = firstPlayer;
    }
}

void Gui::paintEvent(QPaintEvent *event)
{
    drawBoard();
    drawBalls();
}


void Gui::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        last_point = event->pos();
        if (checkIfExceeds(last_point))
        {
            std::pair<int, int> coords = getCoords(last_point);
            if(board.getCellValue(coords) == emptyCell)
            {
                board.setCellValue(coords, actualPlayer);

                QWidget::update();

                if(board.checkWin())
                {
                    QMessageBox::information(
                        this,
                        tr("Gomoku"),
                        QString("Player %1 won!" )
                           .arg(actualPlayer) );
                    QApplication::quit();
                }
                else
                {
                    changePlayer();
                }
            }
        }
    }
}

