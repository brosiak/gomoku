#include "gui.h"
#include <QMouseEvent>
#include <QDebug>
#include <utility>
#include <QMessageBox>
#include <QApplication>
Gui::Gui(QWidget *parent)
    : QMainWindow(parent), board(new Board (dimension))
{
}

Gui::~Gui()
{
}

void Gui::initBoard(QPainter *painter)
{
    painter->setWindow(0, 0, boardSizePx + menuPx, boardSizePx);
    for(int i=0; i<dimension;i++)
    {
        for(int j=0; j<dimension;j++)
        {
            painter->drawRect(i*cellSizePx, j*cellSizePx, cellSizePx, cellSizePx);
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

void Gui::drawBalls(QPainter *painter)
{
    for(int i=0; i<dimension; i++)
    {
        for(int j=0; j<dimension;j++)
        {
            if (board->getCellValue(i,j) == 0)
            {
                continue;
            }
            else if(board->getCellValue(i,j) == 1)
            {
                painter->setBrush(Qt::red);
                painter->drawEllipse(j*cellSizePx + border/2, i*cellSizePx + border/2,
                                     cellSizePx - border, cellSizePx - border);
            }
            else if(board->getCellValue(i,j) == 2)
            {
                painter->setBrush(Qt::blue);
                painter->drawEllipse(j*cellSizePx + border/2, i*cellSizePx + border/2,
                                     cellSizePx - border, cellSizePx - border);
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

void Gui::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    setMaximumWidth(boardSizePx + menuPx);
    setMaximumHeight(boardSizePx);
    initBoard(&painter);
    drawBalls(&painter);
}


void Gui::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        last_point = event->pos();
        isClicked = true;
        //std::pair<int, int> coords = getCoords(last_point);
        if (checkIfExceeds(last_point))
        {
            std::pair<int, int> coords = getCoords(last_point);
            if(board->getCellValue(coords) == 0)
            {
                board->setCellValue(coords, 1);
                QWidget::update();
                if(board->checkWin())
                {
                    QMessageBox::information(
                        this,
                        tr("Gomoku"),
                        tr("You won") );
                    QApplication::quit();
                }
            }
        }


        //std::cout << "coords: "<< coords.first << " "<< coords.second<<std::endl;
    }
}

