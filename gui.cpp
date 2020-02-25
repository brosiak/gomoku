#include "gui.h"
#include <QMouseEvent>
#include <QDebug>
#include <utility>
#include <QMessageBox>
#include <QApplication>
Gui::Gui(QWidget *parent)
    : QMainWindow(parent),
      board(dimension),
      actualPlayer(firstPlayer),
      newGameButton(new QPushButton("New game", this))
{
    initWindow();
    newGameButton->setGeometry(QRect(QPoint(dimension * cellSizePx + menuPx/4, menuPx/4), QSize(menuPx/2,menuPx/4)));
    connect(newGameButton, SIGNAL (released()), this, SLOT (newGame()));
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
    this->setStyleSheet("QMainWindow {background: '#a1887f'}");
}

void Gui::drawBoard()
{
    QPainter painter(this);
    painter.setWindow(0, 0, boardSizePx + menuPx, boardSizePx);
    QPen pen;
    pen.setWidth(3);
    pen.setColor("#725b53");
    for(int x=0; x<dimension;x++)
    {
        for(int y=0; y<dimension;y++)
        {
            painter.setPen(pen);
            painter.drawRect(x*cellSizePx, y*cellSizePx, cellSizePx, cellSizePx);
        }
    }
    QFont serifFont("Times", 20, QFont::Bold);
    painter.setFont(serifFont);
    pen.setColor("#d3b8ae");
    painter.setPen(pen);
    painter.drawText(QPoint(dimension * cellSizePx + menuPx/4, menuPx/8), QString("Actual player: %1").arg(actualPlayer));
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
    QRadialGradient radialGrad(QPointF(y*cellSizePx + border/2, x*cellSizePx + border/2),cellSizePx - border);
    if(board.getCellValue(x,y) == firstPlayer)
    {
        radialGrad.setColorAt(1, Qt::black);
        radialGrad.setColorAt(0.1, Qt::gray);
        painter.setPen(Qt::black);
        //painter.setBrush(Qt::black);
    }
    else if(board.getCellValue(x,y) == secondPlayer)
    {
        radialGrad.setColorAt(1, Qt::white);
        radialGrad.setColorAt(0.1, Qt::gray);
        painter.setPen(Qt::gray);
        //painter.setBrush(Qt::white);
    }
    QBrush brush(radialGrad);
    painter.setBrush(brush);
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

void Gui::newGame()
{
    newGameButton->setText("Game started");
    connect(newGameButton, SIGNAL (released()), this, SLOT (resetGame()));
}
void Gui::resetGame()
{
    newGameButton->setText("New game");
    connect(newGameButton, SIGNAL (released()), this, SLOT (newGame()));
}
