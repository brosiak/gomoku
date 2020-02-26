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
      newGameButton(new QPushButton("New game", this)),
      exitGameButton(new QPushButton("Exit game", this)),
      gameStarted(false)
{
    buttonSheet = "color: %1;"
                  "background-color: %2;"
                  "border-style: %3;"
                  "border-width: %4;"
                  "border-color: %5;"
                  "border-radius: %6";

}

Gui::~Gui()
{
}

void Gui::initWindow()
{
    float dim = 1.0/dimension;
    cellSizePx = dim * height();
    menuPx = width() - (dimension)*height()*dim;
    boardSizePx = cellSizePx * dimension;
    penWidth = width()/(cellSizePx+menuPx);
    newGameButton->setGeometry(QRect(QPoint(dimension * cellSizePx + menuPx/4, menuPx/4), QSize(menuPx/2,menuPx/4)));
    exitGameButton->setGeometry(QRect(QPoint(dimension * cellSizePx + menuPx/4, menuPx/2), QSize(menuPx/2,menuPx/4)));
    newGameButton->setStyleSheet(buttonSheet
                                 .arg(Qt::black)
                                 .arg(itemColor)
                                 .arg("outset")
                                 .arg("2px")
                                 .arg(borderColor)
                                 .arg("30px"));
    connect(newGameButton, SIGNAL (released()), this, SLOT (newGame()));
    connect(exitGameButton, SIGNAL (released()), this, SLOT (exitGame()));
    QString customSheet = "QMainWindow {background: %1}";
    setStyleSheet(customSheet.arg(backgroundColor));

}

void Gui::drawBoard()
{
    QPainter painter(this);
    painter.setWindow(0, 0, boardSizePx + menuPx, boardSizePx);
    QPen pen;
    pen.setWidth(penWidth);
    pen.setColor(borderColor);
    for(int x=0; x<dimension;x++)
    {
        for(int y=0; y<dimension;y++)
        {
            painter.setPen(pen);
            painter.drawRect(x*cellSizePx, y*cellSizePx, cellSizePx, cellSizePx);
        }
    }
}

void Gui::drawInterface()
{
    QPainter painter(this);
    QFont serifFont("Times", 20, QFont::Bold);
    painter.setFont(serifFont);
    QPen pen;
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
    drawInterface();
}


void Gui::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        last_point = event->pos();
        if (checkIfExceeds(last_point))
        {
            if (gameStarted)
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
}

void Gui::newGame()
{
    board.setCellValue(middlePos, middlePos, firstPlayer);
    changePlayer();
    gameStarted = true;
    QWidget::update();
    newGameButton->setText("Reset game");
    connect(newGameButton, SIGNAL (released()), this, SLOT (resetGame()));
}
void Gui::resetGame()
{
    board.resetBoard();
    actualPlayer = firstPlayer;
    gameStarted = false;
    QWidget::update();
    newGameButton->setText("New game");
    connect(newGameButton, SIGNAL (released()), this, SLOT (newGame()));
}
void Gui::exitGame()
{
    delete newGameButton;
    delete exitGameButton;
    QApplication::quit();
}
