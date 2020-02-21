#include "game.h"
#include "board.h"
Game::Game(Board *board_ref, QWidget *parent) :
    QWidget(parent),
    board(board_ref)

{

}
bool Game::checkIfExceeds(QPoint point)
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


void Game::changePlayer()
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


std::pair<int, int> Game::getCoords(QPoint point)
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

void Game::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        last_point = event->pos();
        if (checkIfExceeds(last_point))
        {
            std::pair<int, int> coords = getCoords(last_point);
            if(board->getCellValue(coords) == emptyCell)
            {
                board->setCellValue(coords, actualPlayer);

                QWidget::update();

                if(board->checkWin())
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
