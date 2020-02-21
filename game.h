#ifndef GAME_H
#define GAME_H

#include <QMouseEvent>
#include <QMessageBox>
#include <QApplication>
#include <AppConstants.h>
using namespace appConstants;

class Board
{
 public:
    int getCellValue(std::pair<int,int> coords);
    void setCellValue(std::pair<int,int> coords,const int PLAYER);
    bool checkWin();
};

class Game : public QWidget
{
public:
    Game(Board &board_ref, QWidget *parent = nullptr );
    ~Game();

private:
    int actualPlayer;

    int whoseTurn;
    int score;
    void changeTurn();
    QPoint last_point;
    void mousePressEvent(QMouseEvent *event)override;
    bool checkIfExceeds(QPoint point);
    void changePlayer();
    std::pair<int, int> getCoords(QPoint point);
    Board &board;
};

#endif // GAME_H
