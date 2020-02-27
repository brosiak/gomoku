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
      reDoButton(new QPushButton("Redo", this)),
      unDoButton(new QPushButton("Undo", this)),
      visited(),
      popped(),
      gameStarted(false),
      uiFont("Times", 40, QFont::Bold)
{
    reDoButton->setVisible(false);
    unDoButton->setVisible(false);

}
Gui::~Gui()
{
}

void Gui::initWindow()
{
    calcGamePixels();
    drawButtons();
    connectButtons();
    QString customSheet = "QMainWindow {background: %1}";
    setStyleSheet(customSheet.arg(backgroundColor));

}

void Gui::calcGamePixels()
{
    float dim = 1.0/dimension;
    cellSizePx = dim * height();
    menuPx = width() - (dimension)*height()*dim;
    boardSizePx = cellSizePx * dimension;
    penWidth = width()/(cellSizePx+menuPx);
}

void Gui::drawButton(QPushButton *button, const float x, const float y, const int xSize, const int ySize)
{
    button->setGeometry((QRect(QPoint(dimension * cellSizePx + menuPx/x, menuPx/y), QSize(menuPx/xSize, menuPx/ySize))));
    setButtonTimeSheet(button);
}

void Gui::drawButtons()
{
    drawButton(newGameButton, 4, 4, 2, 4);
    drawButton(exitGameButton, 4, 1.1, 2, 4);
    drawButton(unDoButton, 4, 1.7, 4, 8);
    drawButton(reDoButton, 2, 1.7, 4, 8);
}

void Gui::connectButtons()
{
    connect(newGameButton, SIGNAL (released()), this, SLOT (newGame()));
    connect(exitGameButton, SIGNAL (released()), this, SLOT (exitGame()));
    connect(unDoButton, SIGNAL (released()), this, SLOT (unDo()));
    connect(reDoButton, SIGNAL (released()), this, SLOT (reDo()));
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
    painter.setFont(uiFont);
    QPen pen;
    pen.setColor(itemColor);
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
    QRadialGradient radialGrad(QPointF(y*cellSizePx + cellSizePx/1.5, x*cellSizePx + cellSizePx/4),cellSizePx - border);
    if(board.getCellValue(x,y) == firstPlayer)
    {
        radialGrad.setColorAt(0.0, "#a7a7a7");
        radialGrad.setColorAt(0.8, "#000000");
        radialGrad.setColorAt(0.4, "#000000");
        radialGrad.setColorAt(1.0, "#a7a7a7");
    }
    else if(board.getCellValue(x,y) == secondPlayer)
    {
        radialGrad.setColorAt(0.0, "#9a9a9a");
        radialGrad.setColorAt(0.4, "#F0F0F0");
        radialGrad.setColorAt(0.8, "#F0F0F0");
        radialGrad.setColorAt(1.0, "#9a9a9a");
    }
    painter.setPen(Qt::NoPen);
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
                    visited.push_back(coords);
                    QWidget::update();

                    if(board.checkWin(coords))
                    {
                        QMessageBox::information(
                            this,
                            tr("Gomoku"),
                            QString("Player %1 won!" )
                               .arg(actualPlayer) );
                        changePlayer();
                        //QApplication::quit();
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
    unDoButton->setVisible(true);
    reDoButton->setVisible(true);
    QWidget::update();
    newGameButton->setText("Reset game");
    connect(newGameButton, SIGNAL (released()), this, SLOT (resetGame()));
}

void Gui::resetGame()
{
    board.resetBoard();
    actualPlayer = firstPlayer;
    gameStarted = false;
    unDoButton->setVisible(false);
    reDoButton->setVisible(false);
    QWidget::update();
    newGameButton->setText("New game");
    connect(newGameButton, SIGNAL (released()), this, SLOT (newGame()));
}

void Gui::unDo()
{
    if(!visited.isEmpty())
    {
        board.setCellValue(visited.last(), emptyCell);
        popped.push_back(visited.takeLast());
        changePlayer();
        QWidget::update();
    }
}
void Gui::reDo()
{
    if(!popped.isEmpty())
    {
        board.setCellValue(popped.last(), actualPlayer);
        visited.push_back(popped.takeLast());
        changePlayer();
        QWidget::update();
    }
}
void Gui::freeButtons()
{
    delete newGameButton;
    delete exitGameButton;
    delete unDoButton;
    delete reDoButton;
}

void Gui::exitGame()
{
    freeButtons();
    QApplication::quit();
}

void Gui::setButtonTimeSheet(QPushButton *button)
{
    button->setStyleSheet(buttonSheet
                          .arg(Qt::black)
                          .arg(itemColor)
                          .arg("outset")
                          .arg("2px")
                          .arg(borderColor)
                          .arg("30px"));
    button->setFont(uiFont);
}
